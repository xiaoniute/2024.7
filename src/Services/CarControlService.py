import socket
import sys
import time


class CarService:
    channel: socket.socket
    address: tuple

    def __init__(self, ip: str, port: int):
        self.channel = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.address = (ip, port)

    def StartUp(self):
        self.channel.connect(self.address)
        self.channel.send("command;".encode('utf-8'))
        self.channel.recv(1024).decode('utf-8').split(' ')

    def Shutdown(self):
        self.channel.shutdown(socket.SHUT_WR)
        self.channel.close()

    def ExecuteCommand(self, cmd: str):
        if not cmd.endswith(';'):
            cmd = cmd + ';'
        self.channel.send(cmd.encode('utf-8'))
        result = self.channel.recv(1024).decode('utf-8').split(' ')
        while result[0] != '1':
            time.sleep(1)
            self.channel.send("chassis status ?;".encode('utf-8'))
            result = self.channel.recv(1024).decode('utf-8').split(' ')


if __name__ == "__main__":
    car = CarService(sys.argv[1], int(sys.argv[2]))
    car.StartUp()
    while True:
        command = input()
        if command == 'exit':
            break
        car.ExecuteCommand(command)
        print('[OK]')
    car.Shutdown()
