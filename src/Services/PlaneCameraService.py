import cv2
import queue
from typing import Union
from threading import Thread


class PlaneCamera:
    showCamera: bool
    deviceID: int
    size: tuple[int, int]
    delay: int
    thread: Thread
    capture: Union[cv2.VideoCapture, None]
    status: bool
    isClosing: bool
    que: queue.Queue[cv2.Mat]

    def __init__(self, config: dict):
        self.showCamera = config["show"]
        self.deviceID = config["device-id"]
        self.size = (config["height"], config["width"])
        self.delay = 800 // config["fps"]
        self.thread = Thread(target=self.Run, daemon=True)
        self.capture = None
        self.status = self.isClosing = False
        self.que = queue.Queue()

    def StartUp(self) -> None:
        self.capture = cv2.VideoCapture(self.deviceID, cv2.CAP_DSHOW)
        self.thread.start()

    def Run(self) -> None:
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

    def Shutdown(self) -> None:
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
