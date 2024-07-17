import cv2
from ultralytics import YOLO
import queue
from collections import Counter

def GetAnswer():
    size = 60
    good_num = 0
    bad_num = 0
    FrameQueue = queue.Queue()
    RecordQueue = queue.Queue()
    RecordList = []
    model = YOLO("./model.pt")
    image = cv2.imread("example2.jpg")    
    confidence = 0.8
    

    while(FrameQueue.qsize() < size):
        bad_num = 0
        good_num = 0
        FrameQueue.put(image)
    
        if 1:
            result = model.predict(image, verbose=False, conf=0.88)
            res = result[0].summary()
            for target in res:
                if target['class'] == 1:
                    bad_num += 1
                if target['class'] == 0:
                    good_num += 1
            recorder = (good_num,bad_num)
            if good_num + bad_num <= 4:
                RecordQueue.put(recorder)
    
    for _ in range(size):
        record = RecordQueue.get()
        RecordList.append(record)
    element_counts =Counter(RecordList)
    max_key = max(element_counts, key=element_counts.get)
    rate = element_counts[max_key] / len(RecordList)
    print(rate)
    if rate >= confidence:
        return max_key
    else:
        FrameQueue.get()
        return GetAnswer()

    

print(GetAnswer())