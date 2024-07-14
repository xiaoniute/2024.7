from Controllers.CarController import CarController
from Controllers.PlaneController import PlaneController


class SystemController:
    config: dict
    car: CarController
    plane: PlaneController

    def __init__(self, config: dict):
        self.config = config
        self.car = CarController(config)
        self.plane = PlaneController(config)

    def StartUp(self):
        if self.config["car-enabled"]:
            self.car.StartUp()
        if self.config["plane-enabled"]:
            self.plane.StartUp()

    def Shutdown(self):
        if self.config["plane-enabled"]:
            self.plane.Shutdown()
        if self.config["car-enabled"]:
            self.car.Shutdown()

    def ExecuteCommand(self, command: str) -> bool:
        argv = command.split(" ")
        if argv[0] == "work":
            self.plane.Work()
        elif argv[0] == "takeoff":
            if self.plane.Takeoff():
                print("Takeoff succeeded.")
                return True
            else:
                print("Takeoff failed.")
                return False
        elif argv[0] == "landing":
            if self.plane.Landing():
                print("Landing succeeded.")
                return True
            else:
                print("Landing failed.")
                return False
        elif argv[0] == "record":
            self.plane.threadList[4].send(f"record {self.config['plane-photos-dir']}\n")
        elif argv[0] == 'next':
            self.car.NextPoint()
