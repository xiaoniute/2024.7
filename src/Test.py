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


if __name__ == "__main__":
    RoomManagerAndResultWriterTest()
    ConfigHelperTest()
