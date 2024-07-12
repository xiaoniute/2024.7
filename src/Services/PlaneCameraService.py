import cv2
import queue
from threading import Thread


class PlaneCamera:
    config: dict
    thread: Thread
    capture: cv2.VideoCapture
    status: bool
    isClosing: bool
    delay: int
    que: queue.Queue[cv2.Mat]

    def __init__(self, config: dict):
        self.config = config
        self.thread = Thread(target=self.Run, daemon=True)
        self.capture = None
        self.status = False
        self.isClosing = False
        self.delay = 800 // config["plane-camera-fps"]
        self.que = queue.Queue()

    def StartUp(self):
        self.capture = cv2.VideoCapture(self.config["plane-camera-device-id"], cv2.CAP_DSHOW)
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
                opt = cv2.resize(fr,
                                 dsize=(self.config["plane-camera-height"], self.config["plane-camera-width"]),
                                 fx=1,
                                 fy=1,
                                 interpolation=cv2.INTER_LINEAR
                                 )
                self.que.put(opt)
                if self.config["plane-camera-show"]:
                    cv2.imshow("plane-camera-show", opt)
                    cv2.resizeWindow(
                        "plane-camera-show",
                        self.config["plane-camera-height"],
                        self.config["plane-camera-width"]
                    )
                    cv2.waitKey(self.delay)

    def Shutdown(self):
        self.isClosing = True
        self.status = False
        self.thread.join()
        if self.config["plane-camera-show"]:
            cv2.destroyWindow("plane-camera-show")
        if self.capture:
            self.capture.release()

    def GetFrame(self) -> tuple[bool, cv2.Mat]:
        try:
            return True, self.que.get()
        except queue.Empty:
            return False, None
