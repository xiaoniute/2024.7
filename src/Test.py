def RoomManagerAndResultWriterTest():
    from Entities.RoomManager import RoomManager
    from Utils.ResultWriter import ResultWriter
    roomManager = RoomManager()
    for i in range(1, 4 + 1):
        for j in range(1, 4 + 1):
            roomManager.SetRoomData(f"{i}-{j}", i, j)

    dt = roomManager.ToDict()
    print(dt)
    assert ResultWriter.WriteDictToFile(dt, "test.xlsx")


def ConfigHelperTest():
    from Utils.JsonHelper import JsonHelper
    print(JsonHelper.LoadDictFromFile("../configs/config.json"))


def PlaneControllerTest():
    from Controllers.PlaneController import PlaneController
    from Utils.JsonHelper import JsonHelper
    import time
    config = JsonHelper.LoadDictFromFile("../configs/config.json")
    planeController = PlaneController(config)
    planeController.StartUp()

    # 测试执行命令功能
    assert planeController.ExecuteCommand("echo Hello") == "Hello\n"  # 测试执行普通命令
    assert planeController.ExecuteCommand("114514") == ""  # 测试执行不存在的命令

    # 准备测试文件传输功能
    planeController.ExecuteCommand("rm /mnt/10M.file")
    planeController.ExecuteCommand("rm /mnt/5M.file")
    planeController.ExecuteCommand("dd if=/dev/zero of=/mnt/10M.file bs=10MB count=1")

    # 测试下载文件功能及用时
    t = time.perf_counter()
    assert planeController.DownloadFile("/mnt/10M.file", "10M.file")
    duration = time.perf_counter() - t
    print(f"下载 10MB 文件用时：{duration :.2f}s, 平均速度: {10 / duration :.2f} MB/s")

    # 测试上传文件功能及用时
    t = time.perf_counter()
    assert planeController.UploadFile("5M.file", "/mnt/5M.file")
    duration = time.perf_counter() - t
    print(f"上传 5MB 文件用时：{duration :.2f}s, 平均速度: {5 / duration :.2f} MB/s")

    planeController.Shutdown()


def ModelTest():
    import cv2
    from ultralytics import YOLO
    from Utils.JsonHelper import JsonHelper
    config = JsonHelper.LoadDictFromFile("../configs/config.json")
    model = YOLO(config["model-path"])
    video_path = "test.mp4"
    cap = cv2.VideoCapture(video_path)
    frameRate = cap.get(cv2.CAP_PROP_FPS)
    frameWidth = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    frameHeight = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    out = cv2.VideoWriter(
        'test-result.mp4',
        cv2.VideoWriter_fourcc(*'mp4v'),
        frameRate,
        (frameWidth, frameHeight)
    )
    while cap.isOpened():
        success, frame = cap.read()
        if success:
            results = model.predict(frame)
            annotatedFrame = results[0].plot()
            cv2.imshow("frame", annotatedFrame)
            out.write(annotatedFrame)
        else:
            break
    cap.release()
    out.release()


def CarControllerTest():
    from Controllers.CarController import CarController
    import json

    with open(r"D:\2024.7\src\config.json", "r") as f:
        config = json.load(f)
    carController = CarController(config)
    carController.StartUp()


if __name__ == "__main__":
    # RoomManagerAndResultWriterTest()
    # ConfigHelperTest()
    # PlaneControllerTest()
    # CarControllerTest()
    ModelTest()
