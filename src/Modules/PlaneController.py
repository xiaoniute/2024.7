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
    timeout: int

    def __init__(self, ip: str, port: int, username: str, password: str, cameraUrl: str, timeout: int):
        self.carSeeker = CarSeeker()
        self.client = paramiko.SSHClient()
        self.sftp = None
        self.sshConfig = {"hostname": ip, "port": port, "username": username, "password": password}
        self.threadList = []
        self.cameraUrl = cameraUrl
        self.timeout = timeout

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
        t = time.time()
        while True:
            time.sleep(5)
            result = thread.recv(1024).decode('utf-8')[-11:-2]
            if result == "[/rosout]":
                break
            if time.time() - t > self.timeout:
                print("Timeout!")
                return False

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
                    "&& ./venv/bin/python3 ./PlaneCameraService.py " + self.cameraUrl + " 2> /dev/null \n")  # 进程5: RTSP 视频流

        return True

    def Shutdown(self):
        self.threadList[4].send("exit\n")
        if self.sftp:
            self.sftp.close()
        if self.client:
            self.client.close()

    def PlaneCommand(self, command: str):
        self.ExecuteCommand("cd /root/catkin_ws/ "
                            "&& source ./devel/setup.bash "
                            "&& rosrun ttauav_node service_client " + command)

    def TakeOff(self) -> bool:
        self.PlaneCommand("1")

    def Landing(self) -> bool:
        self.PlaneCommand("2")

    def Move(self, way: tuple[int, int, int]) -> bool:
        # self.PlaneCommand("3")
        pass

    def GrabPhoto(self, filePath: str) -> bool:
        self.threadList[4].send("grab " + filePath + "\n")
        t = time.time()
        while True:
            time.sleep(0.2)
            result = self.threadList[4].recv(64).decode('utf-8')[-6:-2]
            print(result)
            if result == "[OK]":
                return True
            if result == "[ER]":
                return False
            if time.time() - t > self.timeout / 6:
                print("Timeout!")
                return False

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
