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
    data = rospy.wait_for_message("scan",LaserScan)
    number = len(data.ranges)
    middle = number//2
    lidarx = data.ranges[middle]
    while lidarx == np.inf:
        data = rospy.wait_for_message("scan",LaserScan)
        number = len(data.ranges)
        middle = number//2
        lidarx = data.ranges[middle]
    return lidarx

def gety():
    data = rospy.wait_for_message("scan",LaserScan)
    number = len(data.ranges)
    qur = number//4
    lidary = data.ranges[qur]
    while lidary == np.inf:
        data = rospy.wait_for_message("scan",LaserScan)
        number = len(data.ranges)
        qur = number//4
        lidary = data.ranges[qur]
    return lidary

class CarService:
    channel: socket.socket
    address: tuple

    def __init__(self, ip: str, port: int, x_offset :float, y_offset : float):
        self.channel = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.address = (ip, port)
        self.x_offset = x_offset
        self.y_offset = y_offset

    def StartUp(self):
        self.channel.connect(self.address)
        self.channel.send("command;".encode('utf-8'))
        self.channel.recv(1024).decode('utf-8').split(' ')
        rospy.init_node("lidar_data")
        # 订阅激光雷达的数据话题
        data = rospy.wait_for_message("scan",LaserScan)
        #rospy.spin()

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
    car = CarService(sys.argv[1], int(sys.argv[2]),float(sys.argv[3]),float(sys.argv[4]))
    car.StartUp()
    #print('ok')
    rospy.init_node("lidar_data") # 订阅激光雷达的数据话题
    rospy.sleep(0.1)
    while True:
        command = input()
        if command == 'exit':
           break
        # if command.endswith(';'):
        #     location = command.rstip(';').split(" ")
        elif command != ' ':
            location = command.split(' ')
            if abs(float(location[0])) > 1e-5:
                move_x = float(location[0])-(getx()-car.x_offset)
                move_y = 0
            else:
                move_x = 0
                move_y = float(location[1])-(gety()-car.y_offset)
            cmd = f"chassis move x {move_x} y {move_y};"
            car.ExecuteCommand(cmd)
            if abs(float(location[0])) > 1e-5:
                move_x = float(location[0])-(getx()-car.x_offset)
                move_y = 0
            else:
                move_x = 0
                move_y = float(location[1])-(gety()-car.y_offset)
            cmd = f"chassis move x {move_x} y {move_y};"
            car.ExecuteCommand(cmd)
            print('[OK]')
        
    car.Shutdown()

