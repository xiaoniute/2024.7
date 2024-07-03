from Modules.SystemController import SystemController

config = {
    "modelPath": "../Models/best.pt"
}

if __name__ == '__main__':
    systemController = SystemController(config)
    systemController.StartUp()
