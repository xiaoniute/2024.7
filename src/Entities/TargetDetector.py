import cv2
from ultralytics import YOLO


class TargetDetector:
    model: YOLO
    showDetect: bool
    targetConfidence: float

    def __init__(self, config: dict):
        self.model = YOLO(config["model-path"])
        self.showDetect = config["show"]
        self.targetConfidence = config["confidence"]

    def Detect(self, image: cv2.Mat):
        results = self.model.predict(image, verbose=False, conf=self.targetConfidence)
        annotatedFrame = results[0].plot()
        if self.showDetect:
            cv2.imshow("plane-camera-detect-show", annotatedFrame)
            cv2.waitKey(1)
        return results

    def Shutdown(self):
        if self.showDetect:
            cv2.destroyWindow("plane-camera-detect-show")
