from typing import Union, Any

import cv2
import numpy
from numpy import ndarray


class ArucoDetector:
    cameraMatrix: numpy.array
    distortion: numpy.array
    detector: cv2.aruco.ArucoDetector
    coefficients: list[float]
    targetID: int
    showResult: bool
    markerSize: float

    def __init__(self, config: dict, cameraMatrix: numpy.array, distortion: numpy.array):
        self.cameraMatrix = cameraMatrix
        self.distortion = distortion
        self.detector = cv2.aruco.ArucoDetector(
            cv2.aruco.getPredefinedDictionary(eval(f"cv2.aruco.{config['dictionary']}")),
            cv2.aruco.DetectorParameters()
        )
        self.markerSize = config["size"]
        self.targetID = config["id"]
        self.showResult = config["show"]
        self.coefficients = config["coefficients"]

    def Detect(self, image: cv2.Mat) -> Union[tuple[Union[ndarray, Any], Union[ndarray, Any]], tuple[None, None]]:
        """
        :param image: 需要检测的图像
        :return: 检测到的图像旋转向量，平移向量（单位:cm）
        """
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        corners, ids, _ = self.detector.detectMarkers(gray)
        if ids is not None and len(ids) > 0:
            for i in range(len(ids)):
                if ids[i][0] != self.targetID:
                    continue
                success, rotationVector, translationVector = cv2.solvePnP(
                    numpy.array(
                        [[-self.markerSize / 2, self.markerSize / 2, 0],
                         [self.markerSize / 2, self.markerSize / 2, 0],
                         [self.markerSize / 2, -self.markerSize / 2, 0],
                         [-self.markerSize / 2, -self.markerSize / 2, 0]],
                        dtype=numpy.float32
                    ),
                    corners[i],
                    self.cameraMatrix,
                    self.distortion,
                    flags=cv2.SOLVEPNP_IPPE_SQUARE
                )
                translationVector = [translationVector[i] * self.coefficients[i] for i in range(len(translationVector))]
                if success:
                    if self.showResult:
                        img = cv2.aruco.drawDetectedMarkers(image, corners)
                        cv2.imshow("plane-aruco-show", img)
                        cv2.waitKey(1)
                    return rotationVector, translationVector
                else:
                    return None, None

    def Shutdown(self):
        if self.showResult:
            cv2.destroyWindow("plane-aruco-show")
