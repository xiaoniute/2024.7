import paramiko
import time

from typing import Union


class CarController:
    enabled: bool
    sshConfig: tuple[str, int, str, str]
    ControlConfig: tuple[str, int, float, float]
    client: paramiko.SSHClient
    sftp: Union[paramiko.SFTPClient, None]
    threadList: list[paramiko.Channel]

    def __init__(self, config: dict):
        self.enabled = config["enabled"]
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
        self.client = paramiko.SSHClient()
        self.sftp = None
        self.threadList = []

    def StartUp(self) -> None:
        if not self.enabled:
            return

        self.client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        self.client.connect(*self.sshConfig)
        self.sftp = self.client.open_sftp()

        # 启动后台进程
        print("[CarController:INFO] : ROS Core 启动中...", end='')
        thread, _ = self.CreateThread()
        thread.send("cd /home/tta/catkin_ws/ "
                    "&& source ./devel/setup.bash "
                    "&& roscore \n".encode('utf-8'))  # 进程1: ROS 环境
        while True:
            time.sleep(1)
            result = thread.recv(128).decode('utf-8')
            if "[/rosout]" in result:
                break
        print("完成!")

        print("[CarController:INFO] : ROS 雷达节点启动中...", end='')
        thread, _ = self.CreateThread()
        thread.send("cd /home/tta/catkin_ws/ "
                    "&& source ./devel/setup.bash "
                    "&& roslaunch lslidar_driver lslidar_net.launch \n".encode('utf-8'))  # 进程2: ROS 雷达数据节点
        print("完成!")

        print("[CarController:INFO] : RobomasterSDK 启动中...", end='')
        thread, _ = self.CreateThread()
        thread.send("cd /home/tta/catkin_ws/src/lidar_pkg/scripts && "
                    "rosrun lidar_pkg CarControlService.py "
                    "{} {} {} {}\n".format(*self.ControlConfig).encode("utf-8"))  # 进程3: 连接车辆控制服务
        print("完成!")

    def Shutdown(self) -> None:
        if self.enabled:
            self.threadList[2].send("exit\n".encode("utf-8"))
            if self.sftp:
                self.sftp.close()
            if self.client:
                self.client.close()

    def ExecuteCommand(self, command: str) -> None:
        # print(f"[CarController:INFO]:{command}", end='')
        self.threadList[2].send(command.encode("utf-8"))
        result = ""
        while '[OK]' not in result:
            time.sleep(1)
            result = self.threadList[2].recv(2048).decode('utf-8')
            # print(result)

    def Move(self, x: float = 0, y: float = 0) -> None:
        self.ExecuteCommand(f"{x} {y}\n")

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
