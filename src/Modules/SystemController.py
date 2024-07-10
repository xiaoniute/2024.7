from Modules.CarController import CarController
from Modules.PlaneController import PlaneController
from Modules.ResultWriter import ResultWriter
from Modules.ImageResolver import ImageResolver
import time


class SystemController:
    config: dict
    car: CarController
    plane: PlaneController
    resultWriter: ResultWriter
    imageResolver: ImageResolver

    def __init__(self, config: dict):
        self.car = CarController()
        self.config = config
        self.plane = PlaneController(
            config["plane-ip"],
            config["plane-port"],
            config["plane-username"],
            config["plane-password"],
            config["plane-camera-url"],
            config["timeout"]
        )
        self.resultWriter = ResultWriter()
        self.imageResolver = ImageResolver(config["model-path"])

    def StartUp(self):
        self.car.StartUp()
        self.plane.StartUp()

    def Shutdown(self):
        self.plane.Shutdown()
        self.car.Shutdown()

    def ExecuteCommand(self, command: str) -> bool:
        argv = command.split(" ")
        if argv[0] == "shot":
            if len(argv) != 2:
                print("Usage: shot <filename>")
                return False
            if self.plane.GrabPhoto(self.config["plane-photos-dir"] + argv[1]) \
                    and self.plane.DownloadFile(self.config["plane-photos-dir"] + argv[1], argv[1]):
                print("Shot Success")
                return True
            else:
                print("Shot Failed")
                return False
        elif argv[0] == "takeoff":
            self.plane.TakeOff()
        elif argv[0] == "landing":
            self.plane.Landing()
