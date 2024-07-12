import time
import paramiko
from Services.PlaneCameraService import PlaneCamera


# noinspection PyTypeChecker
class PlaneController:
    client: paramiko.SSHClient
    sftp: paramiko.SFTPClient
    config: dict
    threadList: list[paramiko.Channel]
    camera: PlaneCamera

    def __init__(self, config: dict):
        self.client = paramiko.SSHClient()
        self.sftp = None
        self.config = config
        self.threadList = []
        self.camera = PlaneCamera(config)

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
        print("[PlaneController] INFO: PSDK 启动中...", end='')
        thread, _ = self.CreateThread()
        thread.send("cd /root/tta_ros && ./dji_sdk_demo_linux_cxx \n")  # 进程1: PSDK 图传相关
        print("完成!")

        print("[PlaneController] INFO: ROS Core 启动中...", end='')
        thread, _ = self.CreateThread()
        thread.send("cd /root/catkin_ws/ "
                    "&& source ./devel/setup.bash "
                    "&& roscore \n")  # 进程2: ROS 环境
        t = time.time()
        while True:
            time.sleep(1)
            result = thread.recv(128).decode('utf-8')[-11:-2]
            if result == "[/rosout]":
                break
            if time.time() - t > self.config["timeout"]:
                raise RuntimeError("[PlaneController] 启动ROS Core超时.")
        print("完成!")

        print("[PlaneController] INFO: ROS 数据节点启动中...", end='')
        thread, _ = self.CreateThread()
        thread.send("cd /root/catkin_ws/ "
                    "&& source ./devel/setup.bash "
                    "&& rosrun ttauav_node uavdata \n")  # 进程3: ROS 飞机数据节点
        print("完成!")

        print("[PlaneController] INFO: ROS 飞控服务启动中...", end='')
        thread, _ = self.CreateThread()
        thread.send("cd /root/catkin_ws/ "
                    "&& source ./devel/setup.bash "
                    "&& rosrun ttauav_node service \n")  # 进程4: ROS 飞行控制服务
        t = time.time()
        while True:
            time.sleep(1)
            result = thread.recv(1024).decode('utf-8')[-26:-6]
            if result == "gimbalControl server":
                break
            if time.time() - t > self.config["timeout"]:
                raise RuntimeError("[PlaneController] 启动飞行控制服务超时.")
        print("完成!")

        print("[PlaneController] INFO: 视频流连接中...", end='')
        self.camera.StartUp()
        print("完成!")

        print("[PlaneController] INFO: 飞控执行服务启动中...", end='')
        thread, _ = self.CreateThread()
        thread.send("cd /root/catkin_ws/ && source ./devel/setup.bash \n")  # 进程6: 飞控执行服务
        print("完成!")

        print("[PlaneController] INFO: 服务启动完成.")

    def Shutdown(self):
        self.threadList[4].send("exit\n")
        self.camera.Shutdown()
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
