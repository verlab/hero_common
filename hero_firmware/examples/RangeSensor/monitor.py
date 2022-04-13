import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import sys
import time
import datetime

import serial #pyserial
import struct #struct

import numpy as np


print('+-----------------------------------------------+')
print("|        HeRo Range Sensor Monitor - v0.8       |")
print('+-----------------------------------------------+')
print(">> Starting software...")
timestr = time.strftime("%Y%m%d-%H%M%S")

# Serial setup
port_ = sys.argv[1]	
prefix = port_.split('/')[-1]
ser = serial.Serial(port=port_, baudrate=115200)

print(">> Connected to: " + ser.portstr)
print(">> Waiting for data transmission...")


def handle_close(evt):
    print("Closing serial port.")
    ser.close()


fig, ax = plt.subplots()
fig.suptitle('Range Sensor Monitor - v0.8')
fig.canvas.mpl_connect('close_event', handle_close)

x_ = ['S0','S1','S2','S3','S4','S5','S6','S7']
data_ = [0,0,0,0,0,0,0,0]
start_time = time.time()


def init():
    ax.set_ylim(0, 1050)
    return

def autolabel(rects):
    """
    Attach a text label above each bar displaying its height
    """
    for rect in rects:
        height = rect.get_height()
        ax.text(rect.get_x() + rect.get_width()/2., 1.05*height,
                '%d' % int(height),
                ha='center', va='bottom')

def update(x):
    now = time.time()
    while(ser.inWaiting() < 16):
        if (time.time() - now) > 0.2: 
            break
    if ser.inWaiting() >= 16:
        data = ser.read(16)
        data = struct.unpack('<HHHHHHHH', bytearray(data))
        conversion = str(datetime.timedelta(seconds=time.time() - start_time)).split('.')[0]
        for i in range(8):
        	if data[i] > 1025:
        		data_[i] = data_[i]
        	else:
        		data_[i] = data[i]
        print(">>[{}] {}: {}".format(prefix, conversion, data_))
    ax.cla()
    rect = ax.bar(x_, data_)
    autolabel(rect)
    ax.set_ylim(0, 1150)
    return



# ani = FuncAnimation(fig, update, frames=None,
#                     init_func=init, blit=False)
ani = FuncAnimation(fig, update, interval=1)
plt.show()
