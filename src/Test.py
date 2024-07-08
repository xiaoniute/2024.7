def RoomManagerAndResultWriterTest():
    from Modules.Entity.RoomManager import RoomManager
    from Modules.ResultWriter import ResultWriter
    roomManager = RoomManager()
    for i in range(1, 4 + 1):
        for j in range(1, 4 + 1):
            roomManager.SetRoomData(f"{i}-{j}", i, j)

    dt = roomManager.ToDict()
    print(dt)
    assert ResultWriter.WriteDictToFile(dt, "test.xlsx")


def ConfigHelperTest():
    from Modules.ConfigHelper import ConfigHelper
    print(ConfigHelper.LoadDictFromFile("config.json"))


def PlaneControllerTest():
    from Modules.PlaneController import PlaneController
    from Modules.ConfigHelper import ConfigHelper
    import time
    config = ConfigHelper.LoadDictFromFile("config.json")
    planeController = PlaneController(
        config["plane-ip"],
        config["plane-port"],
        config["plane-username"],
        config["plane-password"]
    )
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


if __name__ == "__main__":
    RoomManagerAndResultWriterTest()
    ConfigHelperTest()
    PlaneControllerTest()
