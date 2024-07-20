from typing import Union, Any
from Utils.MathHelper import MathHelper

import math
import cv2
import numpy as np


class ArucoDetector:
    showResult: bool
    detector: cv2.aruco.ArucoDetector
    markerSize: float
    coefficients: list[float]
    targetID: int
    cameraMatrix: np.array
    distortion: np.array

    def __init__(self, config: dict, cameraMatrix: np.array, distortion: np.array):
        self.showResult = config["show"]
        self.detector = cv2.aruco.ArucoDetector(
            cv2.aruco.getPredefinedDictionary(eval(f"cv2.aruco.{config['dictionary']}")),
            cv2.aruco.DetectorParameters()
        )
        self.markerSize = config["size"]
        self.coefficients = config["coefficients"]
        self.targetID = config["id"]
        self.cameraMatrix = cameraMatrix
        self.distortion = distortion

    def Detect(self, image: cv2.Mat) -> Union[tuple[Union[np.ndarray, Any], Union[np.ndarray, Any]], tuple[None, None]]:
        """
        :param image: 需要检测的图像
        :return: 检测到的图像旋转角度（单位：度），平移向量（单位:m）
        """
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        corners, ids, _ = self.detector.detectMarkers(gray)
        if ids is not None and len(ids) > 0:
            for i in range(len(ids)):
                if ids[i][0] != self.targetID:
                    continue
                rotationAngle = MathHelper.CalculateRotation(corners[i][0])
                rotationAngle = math.degrees(rotationAngle)
                success, _, translationVector = cv2.solvePnP(
                    np.array([
                        [-self.markerSize / 2, self.markerSize / 2, 0],
                        [self.markerSize / 2, self.markerSize / 2, 0],
                        [self.markerSize / 2, -self.markerSize / 2, 0],
                        [-self.markerSize / 2, -self.markerSize / 2, 0]],
                        dtype=np.float32
                    ),
                    corners[i],
                    self.cameraMatrix,
                    self.distortion,
                    flags=cv2.SOLVEPNP_IPPE_SQUARE
                )
                translationVector = [
                    (translationVector[i] * self.coefficients[i] * 0.01)[0] for i in range(len(translationVector))
                ]
                # print(corners[i][0])
                if success:
                    if self.showResult:
                        img = cv2.aruco.drawDetectedMarkers(image, corners)
                        cv2.imshow("plane-aruco-show", img)
                        cv2.waitKey(1)
                    # print(f"INFO: ArucoDetector:{rotationAngle},{translationVector}")
                    return rotationAngle, translationVector
                else:
                    return None, None
        return None, None

    def Shutdown(self) -> None:
        if self.showResult:
            try:
                cv2.destroyWindow("plane-aruco-show")
            except Exception as e:
                print(e)
