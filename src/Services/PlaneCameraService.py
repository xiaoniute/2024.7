import cv2
import sys
import queue
import datetime
from threading import Thread


class PlaneCamera:
    url: str
    thread: Thread
    recordThread: Thread
    capture: cv2.VideoCapture
    video: cv2.VideoWriter
    status: bool
    isClosing: bool
    isRecording: bool
    que: queue.Queue[cv2.Mat]

    def __init__(self, url: str):
        self.url = url
        self.thread = Thread(target=self.Run, daemon=True)
        self.recordThread = Thread(target=self.Record, daemon=True)
        self.capture = None
        self.status = False
        self.isClosing = False
        self.isRecording = False
        self.que = queue.Queue()

    def StartUp(self):
        self.capture = cv2.VideoCapture(self.url)
        self.thread.start()

    def Record(self):
        while self.isRecording:
            st, fr = self.GetFrame()
            if st:
                cv2.imwrite(f"{datetime.datetime.now().strftime('%Y-%m-%d-%H-%M-%S')}.jpg", fr)

    def Run(self):
        while not self.isClosing:
            self.status, fr = self.capture.read()
            if not self.que.empty():
                try:
                    self.que.get_nowait()
                except queue.Empty:
                    pass
            self.que.put(fr)

    def Shutdown(self):
        self.isClosing = True
        self.isRecording = False
        self.status = False
        self.recordThread.join()
        self.thread.join()
        if self.capture:
            self.capture.release()

    def GetFrame(self) -> tuple[bool, cv2.Mat]:
        return self.status, self.que.get()

    def StartRecord(self):
        self.isRecording = True
        self.recordThread.start()

    def StopRecord(self):
        self.isRecording = False


if __name__ == "__main__":
    camera = PlaneCamera(sys.argv[1])
    camera.StartUp()
    command = ""
    while command != "exit":
        command = input()
        commands = command.split(" ")
        if commands[0] == "takephoto":
            if len(commands) != 2:
                print("[ER]")
                continue
            status, frame = camera.GetFrame()
            if status and cv2.imwrite(commands[1], frame):
                print("[OK]")
            else:
                print("[ER]")
        elif commands[0] == "record":
            if camera.isRecording:
                camera.StopRecord()
            else:
                camera.StartRecord()

    camera.Shutdown()
