from Controllers.CarController import CarController
from Controllers.PlaneController import PlaneController
import datetime


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
        if argv[0] == "takephoto":
            if len(argv) == 1:
                argv.append(datetime.datetime.now().strftime("%Y%m%d%H%M%S") + ".jpg")
            if (
                    self.plane.TakePhoto(self.config["plane-photos-dir"] + argv[1]) and
                    self.plane.DownloadFile(self.config["plane-photos-dir"] + argv[1], argv[1])
            ):
                print("Taking photo succeeded.")
                return True
            else:
                print("Taking photo failed.")
                return False
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
            self.plane.threadList[4].send("record\n")
