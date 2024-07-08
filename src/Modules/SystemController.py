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
        self.carController = CarController()
        self.plane = PlaneController()
        self.resultWriter = ResultWriter()
        self.imageResolver = ImageResolver(config["model-path"])

    def StartUp(self):
        raise NotImplementedError

    def Shutdown(self):
        raise NotImplementedError
