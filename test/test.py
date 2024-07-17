import cv2
from ultralytics import YOLO

def GetAnswer():
    good_num = 0
    bad_num = 0
    FrameQueue = []
    model = YOLO("./model.pt")
    image = cv2.imread("example1.jpg")    
    result = model.predict(image, verbose=False, conf=0.88)
    if True:
        res = result[0].summary()
        for target in res:
            if target['class'] == 1:
                bad_num+=1
            if target['class'] == 0:
                good_num+=1
        recorder = (good_num,bad_num)
        print(recorder)

    

GetAnswer()