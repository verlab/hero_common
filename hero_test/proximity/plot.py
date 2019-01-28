#!/usr/bin/env python

import matplotlib.pyplot as plt
import numpy as np

import sys
import math
from mpl_toolkits.mplot3d import Axes3D

import argparse

##### Args Parser #####
print ("Reading files")
data = []

for i in range(0, 41):
  file = "s" + str(i)
  with open(file) as f:
    sample = f.read().splitlines()
    sample = [int(d) for d in sample]
    sample = np.array(sample)
    data.append([i/100.0, np.average(sample), np.std(sample)])

data = np.array(data)
print ("Ok")


data = np.array(data)
np.set_printoptions(formatter={'float': lambda x: "{0:0.3f}".format(x)})
fig = plt.figure()

#plt.figure()
start = 0
plt.errorbar(data[start:,0]*100, np.log(data[start:,1]), yerr=np.log(data[start:,2])/2,  fmt='-o',linewidth=1.0, label='White Object', color='black')
#plt.errorbar(x, y, e, linestyle='None', marker='^')
#plt.plot(velocities[:,0], velocities[:,1],  linewidth=2.0, label='Tangential Velocity (Filtered)', color='r')

plt.rc('font', family='serif')
plt.grid(True)
plt.legend()
#plt.ylim(0, 1024)
plt.xlim(0, 40)
plt.legend(loc=0, prop={'size': 18})
plt.title('Infrared Distance Sensor', size = 22)

plt.xlabel("Distance to the Object (cm)",size = 18)
plt.ylabel('log(Analog Input)',size = 18)



############ Statisticals ############
print('\x1b[0;33;40m Statisticals')
start = 0
end = 41
alpha = np.average(np.power(data[start:end,0],2)*data[start:end,1])
print alpha

plt.show()

fig = plt.figure()
plt.plot(data[start:,0]*100, np.sqrt(4200.0/data[start:,1]),  linewidth=2.0, label='White Object', color='black')
plt.rc('font', family='serif')
plt.grid(True)
plt.legend()
#plt.ylim(0, 1024)
plt.xlim(0, 40)
plt.legend(loc=0, prop={'size': 18})
plt.title('Infrared Range Estimation', size = 22)

plt.xlabel("True distance to the Object (cm)",size = 18)
plt.ylabel('Estimated distance to the Object (cm)',size = 18)

plt.show()

