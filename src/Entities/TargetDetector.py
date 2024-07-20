import cv2

from ultralytics import YOLO
from ultralytics.engine.results import Results


class TargetDetector:
    showDetect: bool
    model: YOLO
    targetConfidence: float

    def __init__(self, config: dict):
        self.showDetect = config["show"]
        self.model = YOLO(config["model-path"])
        self.targetConfidence = config["confidence"]

    def Detect(self, image: cv2.Mat) -> list[Results]:
        results = self.model.predict(image, verbose=False, conf=self.targetConfidence)
        annotatedFrame = results[0].plot()
        if self.showDetect:
            cv2.imshow("plane-camera-detect-show", annotatedFrame)
            cv2.waitKey(1)
        return results

    def Shutdown(self) -> None:
        if self.showDetect:
            try:
                cv2.destroyWindow("plane-camera-detect-show")
            except Exception as e:
                print(e)
