from Controllers.CarController import CarController
from Controllers.PlaneController import PlaneController
from Entities.RoomManager import RoomManager


class SystemController:
    car: CarController
    plane: PlaneController
    roomManager: RoomManager
    roomIdList: list

    def __init__(self, config: dict):
        self.car = CarController(config["car"])
        self.plane = PlaneController(config["plane"])
        self.roomManager = RoomManager()
        self.roomIdList = [] # This should be modified

    def StartUp(self):
        self.car.StartUp()
        self.plane.StartUp()

    def Shutdown(self):
        self.plane.Shutdown()
        self.car.Shutdown()

    def ExecuteCommand(self, command: str) -> bool:
        try:
            eval(command)
        except Exception as e:
            print(e)
        return True
    
    def Output(self):
        for roomID in self.roomIdList:
            answer = self.plane.GetAnswer()
            self.roomManager.SetRoomData(roomID, answer[0], answer[1])
            result = self.roomManager.ToDict()
            #transform the result to excel form.
