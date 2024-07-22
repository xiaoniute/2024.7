from ultralytics import YOLO
from Utils.JsonHelper import JsonHelper

if __name__ == "__main__":
    config = JsonHelper.LoadDictFromFile("../configs/config.json")["train"]
    model = YOLO(config["pretrained-model-path"])
    model.train(
        data=config["dataset-config-path"],
        epochs=config["epoch"],
        batch=config["batch"],
        amp=False,
        val=True
    )
