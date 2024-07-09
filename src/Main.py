import os
import sys
from Modules.SystemController import SystemController
from Modules.ConfigHelper import ConfigHelper

if __name__ == '__main__':
    sys.stderr = open(os.devnull, 'w')
    config = ConfigHelper.LoadDictFromFile("config.json")
    systemController = SystemController(config)
    systemController.StartUp()
    while True:
        command = input("> ")
        if command == "exit":
            break
        systemController.ExecuteCommand(command)
    systemController.Shutdown()
