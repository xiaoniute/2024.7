import time
from threading import Thread
from typing import Union

import cv2
from ultralytics import YOLO

import paramiko
from Services.PlaneCameraService import PlaneCamera


class PlaneController:
    client: paramiko.SSHClient
    sftp: Union[paramiko.SFTPClient, None]
    sshConfig: tuple[str, int, str, str]
    controlThread: Thread
    isClosing: bool
    threadList: list[paramiko.Channel]
    camera: PlaneCamera
    model: YOLO
    timeout: int
    delay: int
    showDetect: bool
    size: tuple[int, int]
    targetConfidence: float

    def __init__(self, config: dict):
        self.client = paramiko.SSHClient()
        self.sftp = None
        self.sshConfig = (
            config["plane-ip"],
            config["plane-port"],
            config["plane-username"],
            config["plane-password"]
        )
        self.controlThread = Thread(target=self.Run, daemon=True)
        self.isClosing = False
        self.threadList = []
        self.camera = PlaneCamera(config)
        self.model = YOLO(config["target-detect-model-path"])
        self.timeout = config["timeout"]
        self.delay = 800 // config["plane-camera-fps"]
        self.showDetect = config["plane-camera-detect-show"]
        self.size = (config["plane-camera-height"], config["plane-camera-width"])
        self.targetConfidence = config["target-detect-confidence"]

    def StartUp(self):
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
        self.isClosing = True
        self.camera.Shutdown()
        self.controlThread.join()
        if self.sftp:
            self.sftp.close()
        if self.client:
            self.client.close()

    def ControlPlane(self, command: str):
        self.threadList[4].send(f"rosrun ttauav_node service_client {command} \n".encode('utf-8'))
        result = ""
        while result != "result":
            time.sleep(1)
            result = self.threadList[4].recv(2048).decode('utf-8')[-37:-31]
        return True

    def Takeoff(self):
        return self.ControlPlane("1")

    def Landing(self):
        return self.ControlPlane("2")

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

    def Work(self):
        self.controlThread.start()

    def Run(self):
        while not self.isClosing:
            status, frame = self.camera.GetFrame()
            if status:
                results = self.model.predict(frame, verbose=False, conf=self.targetConfidence)
                annotatedFrame = results[0].plot()
                if self.showDetect:
                    cv2.imshow("plane-camera-detect-show", annotatedFrame)
                    cv2.resizeWindow("plane-camera-detect-show", *self.size)
                    cv2.waitKey(self.delay)
