import numpy
from Modules.CarSeeker import CarSeeker


class PlaneController:
    carSeeker: CarSeeker

    def __init__(self):
        self.carSeeker = CarSeeker()

    def StartUp(self):
        raise NotImplementedError

    def Shutdown(self):
        raise NotImplementedError

    def TakeOff(self) -> bool:
        raise NotImplementedError

    def Landing(self) -> bool:
        raise NotImplementedError

    def Move(self, way: tuple[int, int, int]) -> bool:
        raise NotImplementedError

    def FetchPhoto(self) -> numpy.ndarray:
        raise NotImplementedError
