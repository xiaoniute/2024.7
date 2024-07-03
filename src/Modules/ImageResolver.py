from ultralytics import YOLO


class ImageResolver:
    model: YOLO

    def __init__(self, modelPath: str):
        pass

    def ResolveTargetInfo(self, imagePath: str) -> dict:
        raise NotImplementedError
