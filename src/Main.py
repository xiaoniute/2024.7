from Controllers.SystemController import SystemController
from Utils.JsonHelper import JsonHelper

if __name__ == '__main__':
    config = JsonHelper.LoadDictFromFile("../configs/config.json")
    systemController = SystemController(config)
    systemController.StartUp()
    while True:
        command = input("> ")
        if command == "exit":
            break
        systemController.ExecuteCommand(command)
    systemController.Shutdown()
