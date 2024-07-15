import cv2
import numpy


class ArucoDetector:
    cameraMatrix: numpy.array
    distortion: numpy.array
    detector: cv2.aruco.ArucoDetector
    targetID: int
    showResult: bool
    delay: int
    markerSize: float

    def __init__(self, config: dict):
        self.cameraMatrix = numpy.array(config["plane-camera-matrix"])
        self.distortion = numpy.array(config["plane-camera-dist-coefficients"])
        self.detector = cv2.aruco.ArucoDetector(
            cv2.aruco.getPredefinedDictionary(eval(f"cv2.aruco.{config['plane-aruco-dictionary']}")),
            cv2.aruco.DetectorParameters()
        )
        self.markerSize = config["plane-aruco-size"]
        self.targetID = config["plane-aruco-id"]
        self.showResult = config["plane-aruco-show"]
        self.delay = 800 // config["plane-camera-fps"]

    def Detect(self, image: cv2.Mat):
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        corners, ids, _ = self.detector.detectMarkers(gray)
        if ids is not None and len(ids) > 0:
            for i in range(len(ids)):
                if ids[i][0] != self.targetID:
                    continue
                success, rotationVector, translationVector = cv2.solvePnP(
                    numpy.array([[-self.markerSize / 2, self.markerSize / 2, 0],
                                 [self.markerSize / 2, self.markerSize / 2, 0],
                                 [self.markerSize / 2, -self.markerSize / 2, 0],
                                 [-self.markerSize / 2, -self.markerSize / 2, 0]], dtype=numpy.float32),
                    corners[i],
                    self.cameraMatrix,
                    self.distortion,
                    flags=cv2.SOLVEPNP_IPPE_SQUARE)
                if success:
                    if self.showResult:
                        img = cv2.aruco.drawDetectedMarkers(image, corners)
                        cv2.imshow("plane-aruco-show", img)
                        cv2.waitKey(self.delay)
                    return rotationVector, translationVector
                else:
                    return None, None

    def Shutdown(self):
        if self.showResult:
            cv2.destroyWindow("plane-aruco-show")
