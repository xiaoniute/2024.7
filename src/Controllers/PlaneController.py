import time
import paramiko


# noinspection PyTypeChecker
class PlaneController:
    client: paramiko.SSHClient
    sftp: paramiko.SFTPClient
    config: dict
    threadList: list[paramiko.Channel]

    def __init__(self, config: dict):
        self.client = paramiko.SSHClient()
        self.sftp = None
        self.config = config
        self.threadList = []

    def StartUp(self):
        self.client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        self.client.connect(
            self.config["plane-ip"],
            self.config["plane-port"],
            self.config["plane-username"],
            self.config["plane-password"]
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
            if time.time() - t > self.config["timeout"]:
                raise RuntimeError("[PlaneController] 启动ROS Core超时.")

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
        print("注意：ROS飞行服务启动需要时间，目前闭环检测暂未完成.")

        print("[PlaneController] INFO: RTSP 视频流连接中...")
        thread, _ = self.CreateThread()
        thread.send("cd /mnt "
                    "&& ./venv/bin/python3 ./PlaneCameraService.py " +
                    self.config["plane-camera-url-format"].format("127.0.0.1") +
                    " 2> /dev/null \n")  # 进程5: RTSP 视频流

        print("[PlaneController] INFO: 飞控执行服务启动中...")
        thread, _ = self.CreateThread()
        thread.send("cd /mnt && source ./devel/setup.bash \n")  # 进程6: 飞控执行服务

        print("[PlaneController] INFO: 服务启动完成.")

    def Shutdown(self):
        self.threadList[4].send("exit\n")
        if self.sftp:
            self.sftp.close()
        if self.client:
            self.client.close()

    def ControlPlane(self, command: str):
        self.threadList[5].send("rosrun ttauav_node service_client " + command + "\n")
        print("注意：未检查飞机是否正确执行指令")
        return True

    def Takeoff(self):
        return self.ControlPlane("1")

    def Landing(self):
        return self.ControlPlane("2")

    def TakePhoto(self, filePath: str) -> bool:
        self.threadList[4].send("takephoto " + filePath + "\n")
        t = time.time()
        while True:
            time.sleep(0.2)
            result = self.threadList[4].recv(64).decode('utf-8')[-6:-2]
            if result == "[OK]":
                return True
            if result == "[ER]":
                return False
            if time.time() - t > self.config["timeout"] / 6:
                raise RuntimeError("[PlaneController] 获取照片超时.")

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
