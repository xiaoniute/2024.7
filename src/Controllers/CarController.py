import paramiko
import time
from Utils.JsonHelper import JsonHelper


# noinspection PyTypeChecker
class CarController:
    client: paramiko.SSHClient
    config: dict
    sftp: paramiko.SFTPClient
    route: list[str]
    phase: int
    threadList: list[paramiko.Channel]

    def __init__(self, config: dict):
        self.client = paramiko.SSHClient()
        self.config = config
        self.sftp = None
        self.threadList = []
        self.phase = 0
        self.route = []
        tmpDict = JsonHelper.LoadDictFromFile(config["car-route-json"])
        for i in range(1, len(tmpDict) + 1):
            self.route.append(tmpDict[str(i)])

    def StartUp(self):
        self.client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        self.client.connect(
            self.config["car-ip"],
            self.config["car-port"],
            self.config["car-username"],
            self.config["car-password"]
        )
        self.sftp = self.client.open_sftp()

        # 启动后台进程
        print("[CarController] INFO: RobomasterSDK 启动中...", end='')
        thread, _ = self.CreateThread()
        thread.send("cd /home/tta/Documents/ && "
                    "python ./CarControlService.py "
                    f"{self.config['car-control-ip']} {self.config['car-control-port']} \n")  # 进程1: 连接车辆控制服务
        print("完成!")

    def Shutdown(self):
        self.threadList[0].send("exit\n")
        if self.sftp:
            self.sftp.close()
        if self.client:
            self.client.close()

    def ExecuteCommand(self, command: str):
        self.threadList[0].send(command)
        result = ""
        while result != '[OK]':
            time.sleep(1)
            result = self.threadList[0].recv(2048).decode('utf-8')[-6:-2]
        return True

    def Move(self, x: float = 0, y: float = 0, z: float = 0):
        self.ExecuteCommand(f"chassis move x {x} y {y} z {z};\n")

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
