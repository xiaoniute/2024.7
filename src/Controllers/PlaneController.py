import socket
import cv2
import queue
import numpy as np
import math
import paramiko
import time

from threading import Thread
from typing import Union
from Services.PlaneCameraService import PlaneCamera
from Entities.ArucoDetector import ArucoDetector
from Entities.TargetDetector import TargetDetector
from Utils.MathHelper import MathHelper
from collections import Counter


class PlaneController:
    enabled: bool
    sshConfig: tuple[str, int, str, str]
    threshold: dict[str, float]
    speed: dict[str, float]
    delay: float
    answerSize: int
    answerConfidence: float
    camera: PlaneCamera
    arucoDetector: ArucoDetector
    targetDetector: TargetDetector
    client: paramiko.SSHClient
    sftp: Union[paramiko.SFTPClient, None]
    threadList: list[paramiko.Channel]
    readerThread: Thread
    curTasks: int
    readTasks: int
    isClosing: bool

    def __init__(self, config: dict):
        self.enabled = config["enabled"]
        self.sshConfig = (
            config["ip"],
            config["port"],
            config["username"],
            config["password"]
        )
        self.threshold = config["threshold"]
        self.speed = config["speed"]
        self.delay = config["delay"]
        self.answerSize = config["answer-size"]
        self.answerConfidence = config["answer-confidence"]
        self.camera = PlaneCamera(config["camera"])
        self.arucoDetector = ArucoDetector(
            config["aruco"],
            np.array(config["camera"]["matrix"]),
            np.array(config["camera"]["distortion"])
        )
        self.targetDetector = TargetDetector(config["target"])
        self.client = paramiko.SSHClient()
        self.sftp = None
        self.threadList = []
        self.readerThread = Thread(target=self.Read, daemon=True)
        self.curTasks = self.readTasks = 0
        self.isClosing = False

    def Read(self) -> None:
        self.threadList[0].settimeout(10)
        while not self.isClosing:
            try:
                result = self.threadList[0].recv(1024).decode('utf-8')
                if "[OK]" in result:
                    self.readTasks = self.readTasks + 1
                    # print("Do One Command!")
                time.sleep(0.1)
            except socket.timeout:
                time.sleep(1)

    def StartUp(self) -> None:
        if not self.enabled:
            return

        self.client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        self.client.connect(*self.sshConfig)
        self.sftp = self.client.open_sftp()

        # 启动后台进程
        print("[PlaneController:INFO] : PSDK 启动中...", end='')
        thread, _ = self.CreateThread()
        thread.send("cd /root/tta_ros "
                    "&& ./dji_sdk_demo_linux_cxx \n".encode("utf-8"))  # 进程1: PSDK 相关
        print("完成!")

        print("[PlaneController:INFO] : ROS Core 启动中...", end='')
        thread, _ = self.CreateThread()
        thread.send("cd /root/catkin_ws/ "
                    "&& source ./devel/setup.bash "
                    "&& roscore \n".encode('utf-8'))  # 进程2: ROS 环境
        while True:
            time.sleep(1)
            result = thread.recv(128).decode('utf-8')
            if "[/rosout]" in result:
                break
        print("完成!")

        print("[PlaneController:INFO] : ROS 飞控服务启动中...", end='')
        thread, _ = self.CreateThread()
        thread.send("cd /root/catkin_ws/ "
                    "&& source ./devel/setup.bash "
                    "&& rosrun ttauav_node service \n".encode('utf-8'))  # 进程4: ROS 飞行控制服务
        while True:
            time.sleep(1)
            result = thread.recv(4096).decode('utf-8')
            if "gimbalControl server" in result:
                break
        print("完成!")

        print("[PlaneController:INFO] : 视频流连接中...", end='')
        self.camera.StartUp()
        print("完成!")

        print("[PlaneController:INFO] : 飞控执行服务启动中...", end='')
        thread, _ = self.CreateThread()
        thread.send("cd /root/catkin_ws/ && "
                    "source ./devel/setup.bash && "
                    "rosrun ttauav_node service_client\n".encode('utf-8'))  # 进程6: 飞控执行服务
        thread.settimeout(10)
        print("完成!")

        print("[PlaneController:INFO] : 服务启动完成.")
        self.readerThread.start()

    def Shutdown(self) -> None:
        if not self.enabled:
            return
        self.threadList[3].send("6 \n".encode("utf-8"))
        self.isClosing = True
        self.readerThread.join()
        self.targetDetector.Shutdown()
        self.arucoDetector.Shutdown()
        self.camera.Shutdown()
        if self.sftp:
            self.sftp.close()
        if self.client:
            self.client.close()

    def ControlPlane(self, command: str, isRetry=False) -> None:
        if self.enabled:
            # print(f"rosrun ttauav_node service_client {command}")
            result = ""
            if not isRetry:
                self.curTasks = self.curTasks + 1

            thread = self.threadList[3]
            thread.send(f"{command} \n".encode("utf-8"))
            while "success" not in result:
                try:
                    result = thread.recv(4096).decode('utf-8')
                    time.sleep(1)
                except socket.timeout:
                    self.ControlPlane(command, isRetry=True)
            time.sleep(self.delay)
            if self.readTasks < self.curTasks:
                self.ControlPlane(command, isRetry=True)

    def Takeoff(self) -> None:
        self.ControlPlane("1")
        time.sleep(5)

    def Landing(self, syncWithCar: bool = True) -> None:
        time.sleep(2)
        if syncWithCar:
            self.SyncWithCar(syncTime=2, syncYaw=True, syncHeight=1)
            self.SyncWithCar(syncYaw=False, syncHeight=0.5)
        self.ControlPlane("2")
        time.sleep(5)

    def Rotate(self, degree: float = 0) -> None:
        if abs(degree) < self.threshold["rotation"]:
            return
        value = MathHelper.SignOf(degree) * (abs(degree) - 3)
        rotateSpeed = MathHelper.SignOf(value) * self.speed["rotate"]
        rotateTime = abs(value / rotateSpeed * 1000)
        while rotateTime < 1000:
            rotateSpeed, rotateTime = rotateSpeed / 8, rotateTime * 8
        rotateTime = int(rotateTime)
        self.ControlPlane(f"4 {rotateSpeed} 0 0 0 {rotateTime}")
        time.sleep(rotateTime / 1000)

    def Move(self, speed: float = -1, x: float = 0, y: float = 0, z: float = 0) -> None:
        # 单位：m
        if self.enabled:
            if speed < 0:
                speed = self.speed["move"]
            # deg = math.radians(self.curYaw)
            # x, y = MathHelper.RotateAxis(x, y, deg)
            speedX, speedY, speedZ, distance = MathHelper.Standardize(x, y, z, speed)
            moveTime = distance / speed * 1000
            while moveTime < 1000:
                speedX, speedY, speedZ, moveTime = speedX / 8, speedY / 8, speedZ / 8, moveTime * 8
            self.ControlPlane(f"4 0 {speedX:.2f} {speedY:.2f} {speedZ:.2f} {moveTime:.0f}")
            time.sleep(moveTime / 1000)

    def RotateCamera(self, pitch: int = 0) -> None:
        self.ControlPlane(f"5 {pitch}")

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
            stdin, stdout, stderr = self.client.exec_command(command, get_pty=True)
            return stdout.read().decode()
        except Exception as e:
            print(e)
            return ""

    def CreateThread(self) -> tuple[paramiko.Channel, int]:
        channel = self.client.invoke_shell()
        self.threadList.append(channel)
        return channel, len(self.threadList) - 1

    def SyncWithCar(self, syncTime: int = 1, syncYaw: bool = True, syncHeight: float = -1) -> None:
        # 单位 : m
        def SyncPos(thresholdLocal: float, speedLocal: float) -> None:
            # 同步位置
            while True:
                frame = self.GetFrame()
                _, translationVector = self.arucoDetector.Detect(frame)
                while translationVector is None:
                    self.TryFindCar()
                    frame = self.GetFrame()
                    _, translationVector = self.arucoDetector.Detect(frame)
                x, y, z = translationVector
                x, y = MathHelper.RotateAxis(x, y, math.pi / 2)
                if syncHeight < 0:
                    #  不同步高度
                    if MathHelper.CalculateDistance(x, y, 0, 0) < thresholdLocal:
                        print("[PlaneController:INFO] : 位置同步完成.")
                        return
                    self.Move(speedLocal, x=x, y=y)
                else:
                    if MathHelper.CalculateDistance(x, y, 0, 0) < thresholdLocal and abs(
                            syncHeight - z) < thresholdLocal:
                        print("[PlaneController:INFO] : 位置及高度同步完成.")
                        return
                    self.Move(speedLocal, x=x, y=y, z=syncHeight - z)

        def SyncYaw() -> None:
            # 同步角度
            while True:
                frame = self.GetFrame()
                rotationYaw, _ = self.arucoDetector.Detect(frame)
                while rotationYaw is None:
                    self.TryFindCar()
                    frame = self.GetFrame()
                    rotationYaw, _ = self.arucoDetector.Detect(frame)
                self.curYaw = self.curYaw + rotationYaw
                if self.curYaw > 180:
                    self.curYaw = self.curYaw - 360
                if self.curYaw <= -180:
                    self.curYaw = self.curYaw + 360
                if abs(rotationYaw) < self.threshold["rotation"]:
                    print("[PlaneController:INFO] : 角度同步完成.")
                    return
                self.Rotate(rotationYaw)

        if self.enabled:
            speed, threshold = self.speed["move"], self.threshold["move"]
            for i in range(syncTime):
                print(f"[PlaneController:INFO] : 正在进行第 {i + 1} 次校准")
                SyncPos(threshold, speed)
                if syncYaw:
                    SyncYaw()
                speed, threshold = speed / 2, threshold / 2

    def TryFindCar(self) -> None:
        print("[PlaneController:Warning] 出现异常，正在尝试寻找小车...")
        self.RotateCamera(pitch=-90)
        self.Move(z=0.5)

    def GetFrame(self) -> cv2.Mat:
        status, frame = self.camera.GetFrame()
        while not status:
            time.sleep(1)
            status, frame = self.camera.GetFrame()
        return frame

    def GetAnswer(self) -> tuple[int, int]:
        """
        The function returns a tuple
        whose first element is number of good person and the second is number of bad person.
        :return:
        """
        if self.enabled:
            recordQueue = queue.Queue()
            while recordQueue.qsize() < self.answerSize:
                bad_num = 0
                good_num = 0
                frame = self.GetFrame()
                result = self.targetDetector.Detect(frame)
                res = result[0].summary()
                for target in res:
                    if target['class'] == 1:
                        bad_num += 1
                    if target['class'] == 0:
                        good_num += 1
                recorder = (good_num, bad_num)
                if good_num + bad_num <= 4:
                    recordQueue.put(recorder)

            recordList = []

            for _ in range(self.answerSize):
                record = recordQueue.get()
                recordList.append(record)

            element_counts = Counter(recordList)
            max_key = max(element_counts, key=element_counts.get)
            rate = element_counts[max_key] / len(recordList)

            if rate >= self.answerConfidence:
                return max_key
            else:
                return self.GetAnswer()
