import cv2
import queue
from typing import Union
from threading import Thread


class PlaneCamera:
    thread: Thread
    size: tuple[int, int]
    deviceID: int
    capture: Union[cv2.VideoCapture, None]
    status: bool
    isClosing: bool
    delay: int
    showCamera: bool
    que: queue.Queue[cv2.Mat]

    def __init__(self, config: dict):
        self.thread = Thread(target=self.Run, daemon=True)
        self.size = (config["height"], config["width"])
        self.deviceID = config["device-id"]
        self.capture = None
        self.status = False
        self.isClosing = False
        self.delay = 800 // config["fps"]
        self.showCamera = config["show"]
        self.que = queue.Queue()

    def StartUp(self):
        self.capture = cv2.VideoCapture(self.deviceID, cv2.CAP_DSHOW)
        self.thread.start()

    def Run(self):
        while not self.isClosing:
            self.status, fr = self.capture.read()
            if not self.que.empty():
                try:
                    self.que.get_nowait()
                except queue.Empty:
                    pass
            if self.status:
                opt = cv2.resize(fr, dsize=self.size, fx=1, fy=1, interpolation=cv2.INTER_LINEAR)
                self.que.put(opt)
                if self.showCamera:
                    cv2.imshow("plane-camera-show", opt)
                    cv2.resizeWindow("plane-camera-show", *self.size)
                    cv2.waitKey(self.delay)

    def Shutdown(self):
        self.isClosing = True
        self.status = False
        self.thread.join()
        if self.showCamera:
            cv2.destroyWindow("plane-camera-show")
        if self.capture:
            self.capture.release()

    def GetFrame(self) -> tuple[bool, Union[cv2.Mat, None]]:
        try:
            return True, self.que.get()
        except queue.Empty:
            return False, None
