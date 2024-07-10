import pandas


class ResultWriter:
    @staticmethod
    def WriteDictToFile(value: dict, filePath: str) -> bool:
        """
        :param value: 被用来转换为Excel文件的字典
        :param filePath: 输出到的Excel文件路径
        :return: 是否成功输出
        """
        try:
            df = pandas.DataFrame(value)
            df.to_excel(filePath, index=False)
            return True
        except Exception as e:
            print(e)
            return False
