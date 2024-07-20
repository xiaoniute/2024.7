import math

import numpy as np


class MathHelper:
    @staticmethod
    def CalculateDistance(x1: float, y1: float, x2: float, y2: float) -> float:
        """
        计算两点间的距离
        :param x1: 第一个点的x坐标
        :param y1: 第一个点的y坐标
        :param x2: 第二个点的x坐标
        :param y2: 第二个点的y坐标
        :return: 两点间的距离
        """
        return ((x1 - x2) ** 2 + (y1 - y2) ** 2) ** 0.5

    @staticmethod
    def CalculateRotation(corners: np.array) -> float:
        """
        计算以左上角为为0号点，顺时针标号的四个点的矩形相对于y轴转过的角度
        :param corners: 矩形的四个角（左上角为0号点，顺时针）
        :return: 矩形旋过的角度(弧度制，顺时针为正).
        """
        x1, y1 = corners[0]
        x2, y2 = corners[1]
        x3, y3 = corners[2]
        x4, y4 = corners[3]
        y1, y2, y3, y4 = -y1, -y2, -y3, -y4
        angle1 = -math.atan2(x4 - x1, y1 - y4)
        angle2 = -math.atan2(x3 - x2, y2 - y3)
        angle3 = -math.atan2(y2 - y1, x2 - x1)
        angle4 = -math.atan2(y3 - y4, x3 - x4)
        return (angle1 + angle2 + angle3 + angle4) / 4

    @staticmethod
    def RotateAxis(x: float, y: float, angle: float) -> tuple[float, float]:
        """
        旋转坐标系
        :param x: 原坐标系中的x坐标
        :param y: 原坐标系中的y坐标
        :param angle: 将坐标系转过的角度（弧度制，逆时针为正）
        :return: 旋转后的坐标
        """
        x_new = x * math.cos(angle) - y * math.sin(angle)
        y_new = x * math.sin(angle) + y * math.cos(angle)
        return x_new, y_new

    @staticmethod
    def SignOf(x: float) -> int:
        """
        返回x的符号
        :param x:
        :return: 如果x为正返回1，负数返回-1，0返回0
        """
        if x > 0:
            return 1
        elif x < 0:
            return -1
        return 0

    @staticmethod
    def Standardize(x: float, y: float, z: float, standard: float = 1) -> tuple[float, float, float, float]:
        lth = (x ** 2 + y ** 2 + z ** 2) ** 0.5
        if abs(standard) < 1e-7:
            return 0, 0, 0, lth
        if lth < 1e-7:
            return 0, 0, 0, 0
        rate = standard / lth
        return x * rate, y * rate, z * rate, lth
