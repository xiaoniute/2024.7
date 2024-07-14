import paramiko
from threading import Thread
import time

class CarController:
    config: dict

    def __init__(self, config: dict):
        self.client = paramiko.SSHClient()
        self.config = config
        self.sftp = None
        self.controlThread = Thread(target=self.Run, daemon=True)
        self.threadList = []
        self.isClosing = False
        pass

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
        thread.send("cd Documents/ && ./te.sh \n")  # 进程1: 
        print("完成!")
        while True:
            time.sleep(10)
            result = thread.recv(1024).decode('utf-8')
            if result != "":
                break
            if result != "":
                break
        #result = thread.recv(128).decode('utf-8')

        print(result)


        pass

    def Shutdown(self):
        self.isClosing = True

        self.controlThread.join()
        if self.sftp:
            self.sftp.close()
        if self.client:
            self.client.close()



        pass
    def Run(self):

        pass

    def CreateThread(self) -> tuple[paramiko.Channel, int]:
        channel = self.client.invoke_shell()
        self.threadList.append(channel)
        return channel, len(self.threadList) - 1