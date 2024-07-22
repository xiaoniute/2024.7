#!/usr/bin/env python3
# coding=utf-8

import socket
import sys
import time

import rospy
import numpy as np
from sensor_msgs.msg import LaserScan

lidarx = 0
lidary = 0


def getx():
    data = rospy.wait_for_message("scan", LaserScan)
    number = len(data.ranges)
    middle = number // 2
    lidarx = data.ranges[middle]
    while lidarx == np.inf:
        data = rospy.wait_for_message("scan", LaserScan)
        number = len(data.ranges)
        middle = number // 2
        lidarx = data.ranges[middle]
    return lidarx


def gety():
    data = rospy.wait_for_message("scan", LaserScan)
    number = len(data.ranges)
    qur = number // 4
    lidary = data.ranges[qur]
    while lidary == np.inf:
        data = rospy.wait_for_message("scan", LaserScan)
        number = len(data.ranges)
        qur = number // 4
        lidary = data.ranges[qur]
    return lidary


def getsum():
    data = rospy.wait_for_message("scan", LaserScan)
    number = len(data.ranges)
    middle = number // 2
    lidarx = data.ranges[middle]
    lidarx_ = data.ranges[number-2]
    while lidarx_ == np.inf or lidarx== np.inf:
        data = rospy.wait_for_message("scan", LaserScan)
        number = len(data.ranges)
        middle = number // 2
        lidarx = data.ranges[middle]
        lidarx_ = data.ranges[number-2]
    return lidarx+lidarx_


def adjust_angle():
    s = getsum()
    print(s)
    theat = (-1)*np.arccos(9.0/s)
    print(theat)
    cmd = f"chassis move x 0 y 0 z {theat};"
    car.ExecuteCommand(cmd)
    print('[OK]')

class CarService:
    channel: socket.socket
    address: tuple

    def __init__(self, ip: str, port: int, x_offset: float, y_offset: float):
        self.channel = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.address = (ip, port)
        self.x_offset = x_offset
        self.y_offset = y_offset

    def StartUp(self):
        self.channel.connect(self.address)
        self.channel.send("command;".encode('utf-8'))
        self.channel.recv(1024).decode('utf-8').split(' ')
        self.channel.settimeout(3)
        rospy.init_node("lidar_data")
        # 订阅激光雷达的数据话题
        data = rospy.wait_for_message("scan", LaserScan)
        self.distance = getsum()
        # rospy.spin()

    def Shutdown(self):
        self.channel.shutdown(socket.SHUT_WR)
        self.channel.close()

    def ExecuteCommand(self, cmd: str):
        if not cmd.endswith(';'):
            cmd = cmd + ';'
        self.channel.send(cmd.encode('utf-8'))
        while True:
            try:
                self.channel.recv(4096)
                break
            except socket.timeout:
                break
        time.sleep(1)
        while True:
            self.channel.send("chassis speed ?;".encode('utf-8'))
            try:
                result = self.channel.recv(1024).decode('utf-8').split(' ')
                try:
                    a, b, c, d = map(float, result[3:7])
                    if a < 6 and b < 6 and c < 6 and d < 6:
                        break
                except Exception:
                    pass
            except Exception:
                pass

    def SyncYaw(self):
        while True: 
            self.channel.send("chassis position ?;".encode("utf-8"))
            result = self.channel.recv(1024).decode('utf-8').split(' ')
            print(result)
            try:
                _,_,yaw = map(float,result[:3])
                theat = self.return_theat()
                if theat > 3 and abs(yaw) > 1 or theat > 5:
                    
                    if yaw > 0 :
                        theat = theat * (-1)
                    self.channel.send(f"chassis move z {theat};".encode('utf-8'))
                    time.sleep(0.5)
                    try:
                        self.channel.recv(1024)
                        break
                    except Exception:
                        pass
                else:
                    break
            except Exception:
                pass

    def return_theat(self):
        s = getsum()
        print(s)
        t = self.distance /s
        theat = np.arccos(self.distance/s)*180/3.1415926
        print(theat)
        return theat


if __name__ == "__main__":
    car = CarService(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]), float(sys.argv[4]))
    car.StartUp()
    # print('ok')
    rospy.init_node("lidar_data")  # 订阅激光雷达的数据话题
    rospy.sleep(0.1)
    while True:
        command = input()
        if command == 'exit':
            break
        # if command.endswith(';'):
        #     location = command.rstip(';').split(" ")
        #elif command == 'adjust':
        #    adjust_angle()
        elif command != ' ':
            car.SyncYaw() 
            location = command.split(' ')
            if abs(float(location[0])) > 1e-5:
                move_x = float(location[0]) - (getx() - car.x_offset)
                move_y = 0
            else:
                move_x = 0
                move_y = float(location[1]) - (gety() - car.y_offset)
            cmd = f"chassis move x {move_x} y {move_y} z 0;"
            car.ExecuteCommand(cmd)
            if abs(float(location[0])) > 1e-5:
                move_x = float(location[0]) - (getx() - car.x_offset)
                move_y = 0
            else:
                move_x = 0
                move_y = float(location[1]) - (gety() - car.y_offset)
            cmd = f"chassis move x {move_x} y {move_y} z 0;"
            car.ExecuteCommand(cmd)
            if abs(float(location[0])) > 1e-5:
                move_x = float(location[0]) - (getx() - car.x_offset)
                move_y = 0
            else:
                move_x = 0
                move_y = float(location[1]) - (gety() - car.y_offset)
            cmd = f"chassis move x {move_x} y {move_y} z 0;"
            car.ExecuteCommand(cmd)

            print('[OK]')


    car.Shutdown()
