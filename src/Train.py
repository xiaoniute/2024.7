from ultralytics import YOLO
from Utils.JsonHelper import JsonHelper

if __name__ == "__main__":
    config = JsonHelper.LoadDictFromFile("config.json")
    print(config["pretraining-model-path"])
    model = YOLO(model=config["pretraining-model-path"])
    model.train(data=config["dataset-config-path"],
                epochs=config["training-epoch"],
                batch=config["training-batch"],
                amp=False
                )
