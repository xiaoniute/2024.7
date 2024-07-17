import time
from typing import Union
import queue
from collections import Counter

import numpy as np
import math
import paramiko
from Services.PlaneCameraService import PlaneCamera
from Entities.ArucoDetector import ArucoDetector
from Entities.TargetDetector import TargetDetector
from Entities.RoomManager import RoomManager

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
        # the parameter below is newly added
        self.RecordList = []
        self.FrameQueue = queue.Queue()
        self.RecordQueue = queue.Queue()
        # the para below should be written into config
        self.size = 60 
        self.confidence = 0.88


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
    
    def GetAnswer(self) -> tuple[int,int]:
        # The function returns a tuple whose first element is number of good person and the second is number of bad person.
        while(self.FrameQueue.qsize() < self.size):
            bad_num = 0
            good_num = 0
            flag,frame = PlaneCamera.GetFrame()
        
            if flag:
                result = TargetDetector.Detect(frame)
                res = result[0].summary()
                for target in res:
                    if target['class'] == 1:
                        bad_num += 1
                    if target['class'] == 0:
                        good_num += 1
                recorder = (good_num,bad_num)
                if good_num + bad_num <= 4:
                    self.FrameQueue.put(frame)
                    self.RecordQueue.put(recorder)
            else:
                print("Can't correctly get frames. Retrying...")
        
        for _ in range(self.size):
            record = self.RecordQueue.get()
            self.RecordList.append(record)

        element_counts =Counter(self.RecordList)
        max_key = max(element_counts, key=element_counts.get)
        rate = element_counts[max_key] / len(self.RecordList)
        
        if rate >= self.confidence:
            return max_key
        else:
            self.FrameQueue.get()
            self.RecordList = []
            self.RecordQueue.get()
            return self.GetAnswer()
            


        
            
