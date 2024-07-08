import json


class ConfigHelper:
    @staticmethod
    def LoadDictFromFile(filePath: str) -> dict:
        with open(filePath, "r") as f:
            return json.load(f)
