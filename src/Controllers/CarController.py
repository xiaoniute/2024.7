import paramiko
import time
from Utils.JsonHelper import JsonHelper
import json


# noinspection PyTypeChecker
class CarController:
    enabled: bool
    client: paramiko.SSHClient
    sftp: paramiko.SFTPClient
    sshConfig: tuple[str, int, str, str]
    ControlConfig: tuple[str, int]
    route: list[str]
    phase: int
    threadList: list[paramiko.Channel]

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
        self.ControlConfig = (
            config["controller"]["ip"],
            config["controller"]["port"],
            config["controller"]["x-offset"],
            config["controller"]["y-offset"]
        )
        self.threadList = []
        self.phase = 0
        self.route = []
        tmpDict = JsonHelper.LoadDictFromFile(config["route-json"])
        for i in range(1, len(tmpDict) + 1):
            self.route.append(tmpDict[str(i)])
        self.timeout = config["timeout"]
    def StartUp(self):
        if not self.enabled:
            return

        self.client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        self.client.connect(*self.sshConfig)
        self.sftp = self.client.open_sftp()

        # 启动后台进程
        print("[CarController] INFO: ROS Core 启动中...", end='')
        thread, _ = self.CreateThread()
        thread.send("cd /home/tta/catkin_ws/ "
                    "&& source ./devel/setup.bash "
                    "&& roscore \n".encode('utf-8'))       # 进程1: ROS 环境
        t = time.time()
        while True:
            time.sleep(1)
            result = thread.recv(128).decode('utf-8')[-11:-2]
            if result == "[/rosout]":
                break
            if time.time() - t > self.timeout:
                raise RuntimeError("[PlaneController] 启动ROS Core超时.")
        print("完成!")

        print("[CarController] INFO: ROS 雷达节点启动中...", end='')
        thread, _ = self.CreateThread()
        thread.send("cd /home/tta/catkin_ws/ "
                    "&& source ./devel/setup.bash "
                    "&& roslaunch lslidar_driver lslidar_net.launch \n".encode('utf-8'))  # 进程2: ROS 飞机数据节点
        print("完成!")

        print("[CarController] INFO: RobomasterSDK 启动中...", end='')
        thread, _ = self.CreateThread()
        thread.send("cd /home/tta/catkin_ws/src/lidar_pkg/scripts && "
                    "rosrun lidar_pkg CarControlService.py "
                    "{} {} {} {}\n".format(*self.ControlConfig))  # 进程3: 连接车辆控制服务
        print("完成!")

    def Shutdown(self):
        self.threadList[2].send("exit\n")
        if self.sftp:
            self.sftp.close()
        if self.client:
            self.client.close()

    def ExecuteCommand(self, command: str):
        self.threadList[2].send(command)
        result = ""
        while result != '[OK]':
            time.sleep(1)
            result = self.threadList[2].recv(2048).decode('utf-8')[-6:-2]
        return True

    def Move(self, x: float = 0, y: float = 0):
        self.ExecuteCommand(f"{x} {y}\n")

    def NextPoint(self) -> bool:
        if self.phase >= len(self.route):
            return False
        eval(f"self.Move({self.route[self.phase]})")
        self.phase = self.phase + 1
        return True

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

    def CreateThread(self) -> tuple[paramiko.Channel, int]:
        channel = self.client.invoke_shell()
        self.threadList.append(channel)
        return channel, len(self.threadList) - 1
