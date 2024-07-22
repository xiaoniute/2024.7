import time

from threading import Thread
from typing import Union
from Controllers.CarController import CarController
from Controllers.PlaneController import PlaneController
from Entities.RoomManager import RoomManager
from Utils.JsonHelper import JsonHelper
from Utils.ResultWriter import ResultWriter


class SystemController:
    commandConfig: str
    resultPath: str
    car: CarController
    plane: PlaneController
    roomManager: RoomManager
    commands: dict[str, list[list[str]]]
    positionX: float
    positionY: float

    def __init__(self, config: dict):
        self.commandConfig = config["command-config"]
        self.resultPath = config["result-path"]
        self.car = CarController(config["car"])
        self.plane = PlaneController(config["plane"])
        self.roomManager = RoomManager()
        self.commands = JsonHelper.LoadDictFromFile(config["command-config"])
        self.positionX = self.positionY = 0.

    def StartUp(self) -> None:
        self.car.StartUp()
        self.plane.StartUp()

    def Shutdown(self) -> None:
        self.plane.Shutdown()
        self.car.Shutdown()

    def StartSystem(self, x: Union[float, None] = None, y: Union[float, None] = None) -> None:
        if x is not None:
            self.car.Move(x=x)
            self.positionX = x
        if y is not None:
            self.car.Move(y=y)
            self.positionY = y

    def ExecuteCommand(self, command: str) -> None:
        try:
            eval(command)
        except Exception as e:
            print(e)

    @staticmethod
    def Delay(sleepTime: float) -> None:
        time.sleep(sleepTime)

    def MoveSystem(self,
                   x: Union[float, None] = None,
                   y: Union[float, None] = None,
                   z: Union[float, None] = None) -> None:
        carParam = {}
        planeParam = {}
        if x is not None:
            deltaX = self.positionX - x
            deltaX = deltaX * 0.9
            carParam["x"] = x
            planeParam["y"] = -deltaX
            self.positionX = x
        if y is not None:
            deltaY = self.positionY - y
            deltaY = deltaY * 0.9
            carParam["y"] = y
            planeParam["x"] = deltaY
            self.positionY = y
        if z is not None:
            planeParam["z"] = z * 0.9
        task1 = Thread(target=self.plane.Move, kwargs=planeParam, daemon=True)
        task1.start()
        task2 = Thread(target=self.car.Move, kwargs=carParam, daemon=True)
        task2.start()
        task1.join()
        task2.join()

    def WriteAnswer(self) -> None:
        answer = self.roomManager.ToDict()
        # print(answer)
        ResultWriter.WriteDictToFile(answer, "./answer.xlsx")
        while not (self.plane.UploadFile("./answer.xlsx", self.resultPath)
                   and self.car.UploadFile("./answer.xlsx", self.resultPath)):
            print("[SystemController:Warning] : 答案上传失败，正在重试...")
        print("[SystemController:INFO] : 答案上传成功!")

    def RunStep(self, isFinalRound: bool, step: int) -> None:
        for cmd in self.commands[str(step)]:
            if cmd[0] != '#':
                if cmd[0] == '$':
                    if not isFinalRound:
                        continue
                    cmd = cmd[2:]
                try:
                    print(f"[SystemController:INFO] : self.{cmd}")
                    eval(f"self.{cmd}")
                except Exception as e:
                    print(e)

    def RunBatch(self, isFinalRound: bool, steps: list[int]) -> None:
        for i in steps:
            self.RunStep(isFinalRound, i)

    def RunAll(self, isFinalRound: bool):
        steps = list(map(int, self.commands.keys()))
        steps.sort()
        self.RunBatch(isFinalRound, steps)

    def Reload(self) -> None:
        print("[SystemController:INFO] : 正在重载参数...")
        self.commands = JsonHelper.LoadDictFromFile(self.commandConfig)

    def GetAnswer(self, roomID: str, answer: tuple[int, int]) -> None:
        print(f"Room:{roomID},Answer:{answer}")
        self.roomManager.SetRoomData(roomID, answer[0], answer[1])
