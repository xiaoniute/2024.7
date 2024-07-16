import time
from typing import Union

import numpy as np
import math
import paramiko
from Services.PlaneCameraService import PlaneCamera
from Entities.ArucoDetector import ArucoDetector
from Entities.TargetDetector import TargetDetector


class PlaneController:
    enabled: bool
    client: paramiko.SSHClient
    sftp: Union[paramiko.SFTPClient, None]
    sshConfig: tuple[str, int, str, str]
    threadList: list[paramiko.Channel]
    timeout: int
    threshold: dict[str, float]
    curYaw: float
    moveFactor: float
    delay: float
    camera: PlaneCamera
    arucoDetector: ArucoDetector
    targetDetector: TargetDetector

    def __init__(self, config: dict):
        self.enabled = config["enabled"]
        self.client = paramiko.SSHClient()
        self.sftp = None
        self.sshConfig = (
            config["ip"],
            config["port"],
            config["username"],
            config["password"]
        )
        self.threadList = []
        self.timeout = config["timeout"]
        self.threshold = config["threshold"]
        self.curYaw = 0.
        self.moveFactor = config["move-factor"]
        self.delay = config["delay"]
        self.camera = PlaneCamera(config["camera"])
        self.arucoDetector = ArucoDetector(
            config["aruco"],
            np.array(config["camera"]["matrix"]),
            np.array(config["camera"]["distortion"])
        )
        self.targetDetector = TargetDetector(config["target"])

    def StartUp(self):
        if not self.enabled:
            return

        self.client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        self.client.connect(*self.sshConfig)
        self.sftp = self.client.open_sftp()

        # 启动后台进程
        print("[PlaneController] INFO: PSDK 启动中...", end='')
        thread, _ = self.CreateThread()
        thread.send("cd /root/tta_ros && ./dji_sdk_demo_linux_cxx \n".encode('utf-8'))  # 进程1: PSDK 图传相关
        print("完成!")

        print("[PlaneController] INFO: ROS Core 启动中...", end='')
        thread, _ = self.CreateThread()
        thread.send("cd /root/catkin_ws/ "
                    "&& source ./devel/setup.bash "
                    "&& roscore \n".encode('utf-8'))  # 进程2: ROS 环境
        t = time.time()
        while True:
            time.sleep(1)
            result = thread.recv(128).decode('utf-8')
            if "[/rosout]" in result:
                break
            if time.time() - t > self.timeout:
                raise RuntimeError("[PlaneController] 启动ROS Core超时.")
        print("完成!")

        print("[PlaneController] INFO: ROS 数据节点启动中...", end='')
        thread, _ = self.CreateThread()
        thread.send("cd /root/catkin_ws/ "
                    "&& source ./devel/setup.bash "
                    "&& rosrun ttauav_node uavdata \n".encode('utf-8'))  # 进程3: ROS 飞机数据节点
        print("完成!")

        print("[PlaneController] INFO: ROS 飞控服务启动中...", end='')
        thread, _ = self.CreateThread()
        thread.send("cd /root/catkin_ws/ "
                    "&& source ./devel/setup.bash "
                    "&& rosrun ttauav_node service \n".encode('utf-8'))  # 进程4: ROS 飞行控制服务
        t = time.time()
        while True:
            time.sleep(1)
            result = thread.recv(1024).decode('utf-8')
            if "gimbalControl server" in result:
                break
            if time.time() - t > self.timeout:
                raise RuntimeError("[PlaneController] 启动飞行控制服务超时.")
        print("完成!")

        print("[PlaneController] INFO: 视频流连接中...", end='')
        self.camera.StartUp()
        print("完成!")

        print("[PlaneController] INFO: 飞控执行服务启动中...", end='')
        thread, _ = self.CreateThread()
        thread.send("cd /root/catkin_ws/ && source ./devel/setup.bash \n".encode('utf-8'))  # 进程6: 飞控执行服务
        print("完成!")

        print("[PlaneController] INFO: 服务启动完成.")

    def Shutdown(self):
        if not self.enabled:
            return

        self.targetDetector.Shutdown()
        self.arucoDetector.Shutdown()
        self.camera.Shutdown()
        if self.sftp:
            self.sftp.close()
        if self.client:
            self.client.close()

    def ControlPlane(self, command: str):
        print(f"rosrun ttauav_node service_client {command}")
        self.threadList[4].send(f"rosrun ttauav_node service_client {command} \n".encode('utf-8'))
        result = ""
        t = time.time()
        while "result" not in result:
            time.sleep(1)
            result = self.threadList[4].recv(2048).decode('utf-8')
            if time.time() - t > self.timeout:
                raise RuntimeError("[PlaneController] 获取飞机执行命令回执超时.")
        time.sleep(self.delay)
        return True

    def Takeoff(self):
        self.ControlPlane("1")
        self.Rotate(0)

    def Landing(self):
        return self.ControlPlane("2")

    def Rotate(self, degree: float = 0):
        yawThreshold = self.threshold["yaw"]
        posThreshold = self.threshold["pos"]
        self.curYaw = degree
        self.ControlPlane(f"3 {degree} 0 0 0 {yawThreshold} {posThreshold}")

    def MoveOneStep(self, way: str, tim: float):
        print(f"[MoveOneStep] way={way} tim={tim}")
        speed = self.moveFactor
        if tim < 0:
            tim = -tim
            speed = -speed
        tim = int(tim)
        if way == "x":
            self.ControlPlane(f"4 0 {speed} 0 0 {tim}")
        elif way == "y":
            self.ControlPlane(f"4 0 0 {speed} 0 {tim}")
        elif way == "z":
            self.ControlPlane(f"4 0 0 0 {speed} {tim}")
        time.sleep(tim / 1000)

    def Move(self, x: float = 0, y: float = 0, z: float = 0):
        # 单位：m
        if False:
            x, y, z = x / self.moveFactor, y / self.moveFactor, z * self.moveFactor
        deg = math.radians(self.curYaw)
        print(f"[Move] x'={x} y'={y}")
        if abs(x) > 1e-3:
            x_, y_ = x * math.cos(deg), x * math.sin(deg)
            print(f"[Move] x = {x_} y={y_}")
            self.MoveOneStep("x", x_ / self.moveFactor * 1000)
            self.MoveOneStep("y", y_ / self.moveFactor * 1000)
        if abs(y) > 1e-3:
            x_, y_ = -y * math.sin(deg), y * math.cos(deg)
            print(f"[Move] x = {x_} y={y_}")
            self.MoveOneStep("x", x_ / self.moveFactor * 1000)
            self.MoveOneStep("y", y_ / self.moveFactor * 1000)
        if abs(z) > 1e-3:
            self.MoveOneStep("z", z / self.moveFactor * 1000)

    def RotateCamera(self, pitch: int = 0, roll: int = 0, yaw: int = 0):
        return self.ControlPlane(f"5 {pitch} {roll} {yaw}")

    def DownloadFile(self, remoteFilePath: str, localFilePath: str) -> bool:
        try:
            self.sftp.get(remoteFilePath, localFilePath)
            return True
        except Exception as e:
            print(e)
            return False

    def UploadFile(self, localFilePath: str, remoteFilePath: str) -> bool:
        try:
            self.sftp.put(localFilePath, remoteFilePath)
            return True
        except Exception as e:
            print(e)
            return False

    def ExecuteCommand(self, command: str) -> str:
        try:
            stdin, stdout, stderr = self.client.exec_command(command)
            return stdout.read().decode()
        except Exception as e:
            print(e)
            return ""

    def CreateThread(self) -> tuple[paramiko.Channel, int]:
        channel = self.client.invoke_shell()
        self.threadList.append(channel)
        return channel, len(self.threadList) - 1

    def FollowCar(self, targetHeight: float = 0):
        # 单位 : m
        self.RotateCamera(-90, 0, 0)
        status, frame = self.camera.GetFrame()
        if status:
            rotationAngle, translationVector = self.arucoDetector.Detect(frame)
            x, y, _ = translationVector
            x, y = -y, x
            self.curYaw = self.curYaw + rotationAngle
            if self.curYaw > 180:
                self.curYaw = self.curYaw - 360
            if self.curYaw <= -180:
                self.curYaw = self.curYaw + 360
            self.Rotate(self.curYaw)
            while abs(x) > self.threshold["relative"] or abs(y) > self.threshold["relative"]:
                while abs(x) > self.threshold["relative"]:
                    self.Move(x=x)
                    status, frame = self.camera.GetFrame()
                    _, translationVector = self.arucoDetector.Detect(frame)
                    x, y, _ = translationVector
                    x, y = -y, x
                while abs(y) > self.threshold["relative"]:
                    self.Move(y=y)
                    status, frame = self.camera.GetFrame()
                    _, translationVector = self.arucoDetector.Detect(frame)
                    x, y, _ = translationVector
                    x, y = -y, x

            if abs(targetHeight) > 1e-3:
                _, translationVector = self.arucoDetector.Detect(frame)
                _, _, z = translationVector
                while abs(z - targetHeight) > self.threshold["relative"]:
                    status, frame = self.camera.GetFrame()
                    _, translationVector = self.arucoDetector.Detect(frame)
                    _, _, z = translationVector
                    self.Move(z=z - targetHeight)

            self.RotateCamera(90, 0, 0)
