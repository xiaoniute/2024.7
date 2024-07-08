from Modules.CarController import CarController
from Modules.PlaneController import PlaneController
from Modules.ResultWriter import ResultWriter
from Modules.ImageResolver import ImageResolver


class SystemController:
    car: CarController
    plane: PlaneController
    resultWriter: ResultWriter
    imageResolver: ImageResolver

    def __init__(self, config: dict):
        self.car = CarController()
        self.plane = PlaneController(
            config["plane-ip"],
            config["plane-port"],
            config["plane-username"],
            config["plane-password"]
        )
        self.resultWriter = ResultWriter()
        self.imageResolver = ImageResolver(config["model-path"])

    def StartUp(self):
        self.car.StartUp()
        self.plane.StartUp()

    def Shutdown(self):
        self.plane.Shutdown()
        self.car.Shutdown()
