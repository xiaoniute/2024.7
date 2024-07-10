class RoomData:
    RoomID: str
    GoodManCount: int
    BadManCount: int

    def __init__(self, roomID: str):
        self.RoomID = roomID
        self.GoodManCount = 0
        self.BadManCount = 0


class RoomManager:
    Rooms: dict[str, RoomData]

    def __init__(self):
        self.Rooms = {}

    def SetRoomData(self, roomID: str, goodManCount: int, badManCount: int):
        if roomID not in self.Rooms:
            self.Rooms[roomID] = RoomData(roomID)
        self.Rooms[roomID].GoodManCount = goodManCount
        self.Rooms[roomID].BadManCount = badManCount

    def ToDict(self) -> dict[str, list]:
        """
        将数据转换成适合输出为Excel的格式，格式为 {"房间":["1-1","1-2"],"好人":[1,2],"坏人":[0,1]}
        :return: 转换后的字典
        """
        roomList = [room.RoomID for room in self.Rooms.values()]
        roomList.sort(key=lambda x: tuple(map(int, x.split("-"))))
        goodManList = []
        badManList = []
        for room in roomList:
            goodManList.append(self.Rooms[room].GoodManCount)
            badManList.append(self.Rooms[room].BadManCount)
        return {
            "房间": roomList,
            "好人": goodManList,
            "坏人": badManList
        }
