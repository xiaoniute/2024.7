from typing import Union
from Services.PlaneCameraService import PlaneCamera
from Entities.ArucoDetector import ArucoDetector
from Entities.TargetDetector import TargetDetector
from Utils.MathHelper import MathHelper
import queue
from collections import Counter

import numpy as np
import math
import paramiko
import time


class PlaneController:
    enabled: bool
    client: paramiko.SSHClient
    sftp: Union[paramiko.SFTPClient, None]
    sshConfig: tuple[str, int, str, str]
    threadList: list[paramiko.Channel]
    timeout: int
    threshold: dict[str, float]
    move: dict[str, float]
    rotate: dict[str, float]
    curYaw: float
    delay: float
    eps: float
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
        self.move = config["move"]
        self.rotate = config["rotate"]
        self.curYaw = 0.
        self.delay = config["delay"]
        self.eps = config["eps"]
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
        self.confidence = config["confidence"]

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

    def Takeoff(self):
        self.ControlPlane("1")
        self.ResetAngle()

    def Landing(self):
        self.ControlPlane("2")

    def Rotate(self, degree: float = 0):
        if abs(degree) < self.threshold["rotation"]:
            return
        value = MathHelper.SignOf(degree) * (abs(degree) - self.rotate["b"])
        rotateSpeed = MathHelper.SignOf(value) * self.rotate["speed"]
        rotateTime = abs(value / rotateSpeed * 1000)
        rotateTime = int(rotateTime)
        self.ControlPlane(f"4 {rotateSpeed} 0 0 0 {rotateTime}")
        time.sleep(rotateTime / 1000)

    def ResetAngle(self):
        self.ControlPlane(f"3 0 0 0 0 0 0")
        self.curYaw = 0

    def Move(self, speed: float, x: float = 0, y: float = 0):
        # 单位：m
        deg = math.radians(self.curYaw)
        x, y = MathHelper.RotateAxis(x, y, deg)
        x, y = round(x, 2), round(y, 2)
        if MathHelper.CalculateDistance(x, y, 0, 0) < self.eps:
            return
        if abs(x) < self.eps:
            # 只移动 y 方向
            speedX = 0
            speedY = speed * MathHelper.SignOf(y)
            moveTime = y / speedY * 1000
        elif abs(y) < self.eps:
            # 只移动 x 方向
            speedX = speed * MathHelper.SignOf(x)
            speedY = 0
            moveTime = x / speedX * 1000
        else:
            radio = y / x
            if abs(radio) > 1:
                # y 方向最高速度
                speedY = speed * MathHelper.SignOf(y)
                speedX = speedY / radio
                moveTime = y / speedY * 1000
            else:
                speedX = speed * MathHelper.SignOf(x)
                speedY = speedX * radio
                moveTime = x / speedX * 1000
        speedX, speedY, moveTime = round(speedX, 2), round(speedY, 2), int(moveTime)
        self.ControlPlane(f"4 0 {speedX:.2f} {speedY:.2f} 0 {moveTime}")
        time.sleep(moveTime / 1000)

    def MoveHeight(self, speed: float, z: float):
        if z < 0:
            speed = -speed
        moveTime = int(z / speed * 1000)
        self.ControlPlane(f"4 0 0 0 {speed} {moveTime}")
        time.sleep(moveTime / 1000)

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

    def SyncWithCar(self, isLanding: bool):
        # 单位 : m
        def SyncPos(threshold: float, speed: float, failTime: int = 60) -> bool:
            # 同步位置
            while True:
                status, frame = self.camera.GetFrame()
                if not status:
                    failTime -= 1
                    if failTime <= 0:
                        print("[PlaneController][ERROR] 与小车同步位置失败.")
                        return False
                    continue
                _, translationVector = self.arucoDetector.Detect(frame)
                x, y, _ = translationVector
                x, y = MathHelper.RotateAxis(x, y, math.pi / 2)
                if MathHelper.CalculateDistance(x, y, 0, 0) < threshold:
                    print("[PlaneController] 位置同步完成.")
                    return True
                self.Move(speed, x=x, y=y)

        def SyncYaw(failTime: int = 60) -> bool:
            # 同步角度
            while True:
                status, frame = self.camera.GetFrame()
                if status:
                    break
                failTime -= 1
                if failTime <= 0:
                    print("[PlaneController][ERROR] 与小车同步角度失败.")
                    return False
            rotationYaw, _ = self.arucoDetector.Detect(frame)
            self.Rotate(rotationYaw)
            self.curYaw = self.curYaw + rotationYaw
            if self.curYaw > 180:
                self.curYaw = self.curYaw - 360
            if self.curYaw <= -180:
                self.curYaw = self.curYaw + 360
            print("[PlaneController] 角度同步完成.")
            return True

        self.RotateCamera(-90)
        SyncPos(self.threshold["relative"], self.move["speed"])
        SyncYaw()
        if isLanding:
            SyncPos(self.threshold["landing"], self.move["slow-speed"])
            self.Landing()

    def SyncHeight(self, targetHeight: float):
        self.RotateCamera(-90)
        failTime = 60
        while True:
            status, frame = self.camera.GetFrame()
            if not status:
                failTime -= 1
                if failTime <= 0:
                    print("[PlaneController][ERROR] 与小车同步高度失败.")
                    return False
                continue
            _, translationVector = self.arucoDetector.Detect(frame)
            _, _, z = translationVector
            if abs(targetHeight - z) < self.threshold["height"]:
                print("[PlaneController] 高度同步完成.")
                return True
            self.MoveHeight(self.move["speed"], targetHeight - z)

    def GetAnswer(self) -> tuple[int, int]:
        """
        The function returns a tuple whose first element is number of good person and the second is number of bad person.
        :return:
        """
        while self.FrameQueue.qsize() < self.size:
            bad_num = 0
            good_num = 0
            flag, frame = PlaneCamera.GetFrame()

            if flag:
                result = TargetDetector.Detect(frame)
                res = result[0].summary()
                for target in res:
                    if target['class'] == 1:
                        bad_num += 1
                    if target['class'] == 0:
                        good_num += 1
                recorder = (good_num, bad_num)
                if good_num + bad_num <= 4:
                    self.FrameQueue.put(frame)
                    self.RecordQueue.put(recorder)
            else:
                print("Can't correctly get frames. Retrying...")

        for _ in range(self.size):
            record = self.RecordQueue.get()
            self.RecordList.append(record)

        element_counts = Counter(self.RecordList)
        max_key = max(element_counts, key=element_counts.get)
        rate = element_counts[max_key] / len(self.RecordList)

        if rate >= self.confidence:
            return max_key
        else:
            self.FrameQueue.get()
            self.RecordList = []
            self.RecordQueue.get()
            return self.GetAnswer()
