from Modules.RadarResolver import RadarResolver


class CarController:
    radar: RadarResolver

    def __init__(self):
        self.radar = RadarResolver()

    def StartUp(self):
        pass

    def Shutdown(self):
        pass
