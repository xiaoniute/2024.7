from typing import Union, Any

import cv2
import numpy as np


class ArucoDetector:
    cameraMatrix: np.array
    distortion: np.array
    detector: cv2.aruco.ArucoDetector
    coefficients: list[float]
    targetID: int
    showResult: bool
    markerSize: float

    def __init__(self, config: dict, cameraMatrix: np.array, distortion: np.array):
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

    @staticmethod
    def GetAngle(corners: np.array) -> float:
        x1, y1 = corners[0]
        x2, y2 = corners[1]
        x3, y3 = corners[2]
        x4, y4 = corners[3]
        if y1 - y4 == 0:
            angle1 = np.pi / 2 if x1 > x4 else -np.pi / 2
        else:
            angle1 = -np.arctan((x1 - x4) / (y1 - y4))
        if y2 - y3 == 0:
            angle2 = np.pi / 2 if x2 > x3 else -np.pi / 2
        else:
            angle2 = -np.arctan((x2 - x3) / (y2 - y3))
        angle = (angle1 + angle2) / 2
        if y2 > y3:
            angle = angle + np.pi
        if angle > np.pi:
            angle = angle - 2 * np.pi
        return np.degrees(angle)

    def Detect(self, image: cv2.Mat) -> Union[tuple[Union[np.ndarray, Any], Union[np.ndarray, Any]], tuple[None, None]]:
        """
        :param image: 需要检测的图像
        :return: 检测到的图像旋转向量，平移向量（单位:m）
        """
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        corners, ids, _ = self.detector.detectMarkers(gray)
        if ids is not None and len(ids) > 0:
            for i in range(len(ids)):
                if ids[i][0] != self.targetID:
                    continue
                rotationAngle = self.GetAngle(corners[i][0])
                success, _, translationVector = cv2.solvePnP(
                    np.array(
                        [[-self.markerSize / 2, self.markerSize / 2, 0],
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
                if success:
                    if self.showResult:
                        img = cv2.aruco.drawDetectedMarkers(image, corners)
                        cv2.imshow("plane-aruco-show", img)
                        cv2.waitKey(1)
                    print(f"INFO: ArucoDetector:{rotationAngle},{translationVector}")
                    return rotationAngle, translationVector
                else:
                    return None, None

    def Shutdown(self):
        if self.showResult:
            cv2.destroyWindow("plane-aruco-show")
