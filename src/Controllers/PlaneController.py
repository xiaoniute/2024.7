import time
from typing import Union

import numpy
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
    threshold: float
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
        self.camera = PlaneCamera(config["camera"])
        self.arucoDetector = ArucoDetector(
            config["aruco"],
            numpy.array(config["camera"]["matrix"]),
            numpy.array(config["camera"]["distortion"])
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
            result = thread.recv(128).decode('utf-8')[-11:-2]
            if result == "[/rosout]":
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
            result = thread.recv(1024).decode('utf-8')[-26:-6]
            if result == "gimbalControl server":
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
        self.threadList[4].send(f"rosrun ttauav_node service_client {command} \n".encode('utf-8'))
        result = ""
        t = time.time()
        while result != "result":
            time.sleep(1)
            result = self.threadList[4].recv(2048).decode('utf-8')[-37:-31]
            if time.time() - t > self.timeout:
                raise RuntimeError("[PlaneController] 获取飞机执行命令回执超时.")
        return True

    def Takeoff(self):
        return self.ControlPlane("1")

    def Landing(self):
        return self.ControlPlane("2")

    def Move(self, x: float = 0, y: float = 0, z: float = 0):
        # 单位：m
        if x != 0.0:
            self.ControlPlane(f"4 {x / 3} 0 0")
        if y != 0.0:
            self.ControlPlane(f"4 0 {y / 3} 0")
        # if z != 0.0:
        #     self.ControlPlane(f"4 0 0 {z / 3}")

    def RotateCamera(self, degree: int):
        return self.ControlPlane(f"5 {degree}")

    def SyncWithCar(self):
        self.RotateCamera(-90)
        x, y = (self.threshold + 10, self.threshold + 10)
        while abs(x) > self.threshold or abs(y) > self.threshold:
            status, frame = self.camera.GetFrame()
            _, translationVector = self.arucoDetector.Detect(frame)
            x, y, _ = translationVector
            print(x, y, _)
            self.Move(-y / 100, x / 100)

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
