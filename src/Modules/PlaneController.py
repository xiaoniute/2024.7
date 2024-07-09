import time
import subprocess

import paramiko

from Modules.CarSeeker import CarSeeker


# noinspection PyTypeChecker
class PlaneController:
    carSeeker: CarSeeker
    client: paramiko.SSHClient
    sftp: paramiko.SFTPClient
    sshConfig: dict
    threadList: list[paramiko.Channel]
    cameraUrl: str

    def __init__(self, ip: str, port: int, username: str, password: str, cameraUrl: str):
        self.carSeeker = CarSeeker()
        self.client = paramiko.SSHClient()
        self.sftp = None
        self.sshConfig = {"hostname": ip, "port": port, "username": username, "password": password}
        self.threadList = []
        self.cameraUrl = cameraUrl

    def StartUp(self):
        self.client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        self.client.connect(
            self.sshConfig["hostname"],
            self.sshConfig["port"],
            self.sshConfig["username"],
            self.sshConfig["password"]
        )
        self.sftp = self.client.open_sftp()

        # 启动后台进程
        print("[PlaneController] INFO: PSDK 启动中...")
        thread, _ = self.CreateThread()
        thread.send("cd /root/tta_ros && ./dji_sdk_demo_linux_cxx \n")  # 进程1: PSDK 图传相关

        print("[PlaneController] INFO: ROS Core 启动中...")
        thread, _ = self.CreateThread()
        thread.send("cd /root/catkin_ws/ "
                    "&& source ./devel/setup.bash "
                    "&& roscore \n")  # 进程2: ROS 环境
        result = ""
        while result != "[/rosout]":
            time.sleep(5)
            result = thread.recv(1024).decode('utf-8')[-11:-2]

        print("[PlaneController] INFO: ROS 数据节点启动中...")
        thread, _ = self.CreateThread()
        thread.send("cd /root/catkin_ws/ "
                    "&& source ./devel/setup.bash "
                    "&& rosrun ttauav_node uavdata \n")  # 进程3: ROS 飞机数据节点

        print("[PlaneController] INFO: ROS 飞控服务启动中...")
        thread, _ = self.CreateThread()
        thread.send("cd /root/catkin_ws/ "
                    "&& source ./devel/setup.bash "
                    "&& rosrun ttauav_node service \n")  # 进程4: ROS 飞行控制服务

        print("[PlaneController] INFO: RTSP 视频流连接中...")
        thread, _ = self.CreateThread()
        thread.send("cd /mnt "
                    "&& ./venv/bin/python3 ./PlaneCameraService.py " + self.cameraUrl + "\n")  # 进程5: RTSP 视频流

    def Shutdown(self):
        self.threadList[4].send("exit\n")
        if self.sftp:
            self.sftp.close()
        if self.client:
            self.client.close()

    def TakeOff(self) -> bool:
        raise NotImplementedError

    def Landing(self) -> bool:
        raise NotImplementedError

    def Move(self, way: tuple[int, int, int]) -> bool:
        raise NotImplementedError

    def GrabPhoto(self, filePath: str) -> bool:
        self.threadList[4].send("grab " + filePath + "\n")

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
        try:
            channel = self.client.invoke_shell()
            self.threadList.append(channel)
            return channel, len(self.threadList) - 1
        except Exception as e:
            print(e)
            raise e
