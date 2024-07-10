import cv2
import sys
import queue
from threading import Thread


class PlaneCamera:
    url: str
    thread: Thread
    capture: cv2.VideoCapture
    status: bool
    isClosing: bool
    que: queue.Queue[cv2.Mat]

    def __init__(self, url: str):
        self.url = url
        self.thread = Thread(target=self.Run, daemon=True)
        self.capture = None
        self.status = False
        self.isClosing = False
        self.que = queue.Queue()

    def StartUp(self):
        self.capture = cv2.VideoCapture(self.url)
        self.thread.start()

    def Run(self):
        while not self.isClosing:
            self.status, frame = self.capture.read()
            if not self.que.empty():
                try:
                    self.que.get_nowait()
                except queue.Empty:
                    pass
            self.que.put(frame)

    def Shutdown(self):
        self.isClosing = True
        self.status = False
        self.thread.join()
        if self.capture:
            self.capture.release()

    def GetFrame(self) -> tuple[bool, cv2.Mat]:
        return self.status, self.que.get()


if __name__ == "__main__":
    camera = PlaneCamera(sys.argv[1])
    camera.StartUp()
    command = ""
    while command != "exit":
        command = input()
        commands = command.split(" ")
        if commands[0] == "grab":
            if len(commands) != 2:
                print("[ER]")
                continue
            status, frame = camera.GetFrame()
            if status and cv2.imwrite(commands[1], frame):
                print("[OK]")
            else:
                print("[ER]")

    camera.Shutdown()
