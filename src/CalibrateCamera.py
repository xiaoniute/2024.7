import numpy as np
import cv2
import glob

# 棋盘格的角点数
CHECKERBOARD = (5, 8)
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

# 实际世界中角点的距离，单位是毫米
dist = 27
objp = np.zeros((CHECKERBOARD[0] * CHECKERBOARD[1], 3), np.float32)
objp[:, :2] = np.mgrid[0:CHECKERBOARD[0] * dist:dist, 0:CHECKERBOARD[1] * dist:dist].T.reshape(-1, 2)

objpoints = []
imgpoints = []

# 获取所有棋盘格图像的路径
images = glob.glob('Mark/*.JPG')

if len(images) > 0:
    size = (640, 360)
    for filename in images:
        img = cv2.imread(filename)
        img = cv2.resize(img, dsize=size, fx=1, fy=1, interpolation=cv2.INTER_LINEAR)
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        # 找到棋盘格角点
        ret, corners = cv2.findChessboardCorners(gray, CHECKERBOARD, None)
        print(ret, corners)
        cv2.imshow("img-origin", gray)
        cv2.waitKey(500)

        # 如果找到了角点
        if ret:
            objpoints.append(objp)
            corners2 = cv2.cornerSubPix(gray, corners, (11, 11), (-1, -1), criteria)
            imgpoints.append(corners2)

            # 可选：在图像上绘制并显示角点
            cv2.drawChessboardCorners(img, CHECKERBOARD, corners2, ret)
            cv2.imshow('img-detect', img)
            cv2.waitKey(500)

    cv2.destroyAllWindows()

    ret, mtx, dist, _, _ = cv2.calibrateCamera(objpoints, imgpoints, size[::-1], None, None)

    print("Camera matrix : ")
    print(mtx)
    print("Distortion coefficients : ")
    print(dist)
