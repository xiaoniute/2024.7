from Controllers.CarController import CarController
from Controllers.PlaneController import PlaneController


class SystemController:
    enableCar: bool
    enablePlane: bool
    car: CarController
    plane: PlaneController

    def __init__(self, config: dict):
        self.enableCar = config["car-enabled"]
        self.enablePlane = config["plane-enabled"]
        self.car = CarController(config)
        self.plane = PlaneController(config)

    def StartUp(self):
        if self.enableCar:
            self.car.StartUp()
        if self.enablePlane:
            self.plane.StartUp()

    def Shutdown(self):
        if self.enablePlane:
            self.plane.Shutdown()
        if self.enableCar:
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
        elif argv[0] == 'next':
            self.car.NextPoint()
