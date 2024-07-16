from Controllers.CarController import CarController
from Controllers.PlaneController import PlaneController


class SystemController:
    car: CarController
    plane: PlaneController

    def __init__(self, config: dict):
        self.car = CarController(config["car"])
        self.plane = PlaneController(config["plane"])

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
