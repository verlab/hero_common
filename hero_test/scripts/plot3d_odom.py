#!/usr/bin/env python

import matplotlib.pyplot as plt
import numpy as np
import rosbag
import sys
import math
from mpl_toolkits.mplot3d import Axes3D
import tf
import argparse

##### Args Parser #####
parser = argparse.ArgumentParser(description='Plot Odometry Comparison.')
parser.add_argument('--file', type=str, help='bagfile with odometry and groundtruth pose;')
parser.add_argument('--robot', type=str, help='Choise the robot (hero or epuck)')
parser.add_argument('--time_min', type=float, help='Minimal time to cut')
parser.add_argument('--time_max', type=float, help='Maximal time to cut')
parser.add_argument('--align', type=float, help='Alignment for odometry yaw')

args = parser.parse_args()

# Get max distance 
def get_distance(x, y):
    distance = 0.0
    for i in range(1, len(x)):
        dx = x[i] - x[i-1]
        dy = y[i] - y[i-1]
        d = dx * dx + dy * dy
        d = np.sqrt(d)
        if d > 0.0005: # min error from mocap
            distance += d
    return distance

print ("Plot Odometry Comparision")
print ("Loading bag file " + args.file)
bag = rosbag.Bag(args.file)

time_min = float(args.time_min)
time_max = float(args.time_max)

ground_t = '/hero_1/pose'
if args.robot == "epuck":
    ground_t = '/epuck_1/pose'
hero_groundtruth = [[int(str(t)), msg.pose.position.x, msg.pose.position.y, msg.pose.position.z, tf.transformations.euler_from_quaternion([msg.pose.orientation.x, msg.pose.orientation.y, msg.pose.orientation.z, msg.pose.orientation.w])[2], 0.0 ] for topic, msg, t in bag.read_messages(topics=[ground_t])]
hero_groundtruth = np.array(hero_groundtruth)
hero_groundtruth[:,0] = (hero_groundtruth[:,0] - hero_groundtruth[0,0])*1e-9 # nanoseconds to seconds
hero_groundtruth = hero_groundtruth[hero_groundtruth[:,0] < time_max,:]
hero_groundtruth = hero_groundtruth[time_min < hero_groundtruth[:,0],:]

odom_t = '/hero_1/odom'
if args.robot == "epuck":
    odom_t = '/robot_real_0/odom'
hero_odometry = [[int(str(t)), msg.pose.pose.position.x, msg.pose.pose.position.y, msg.pose.pose.position.z] for topic, msg, t in bag.read_messages(topics=[odom_t])]
hero_odometry = np.array(hero_odometry)
hero_odometry[:,0] = (hero_odometry[:,0] - hero_odometry[0,0])*1e-9 # nanoseconds to seconds
hero_odometry = hero_odometry[hero_odometry[:,0] < time_max,:]
hero_odometry = hero_odometry[time_min < hero_odometry[:,0],:]

bag.close();
print("Closing bag: All data was loaded.")

fig = plt.figure()

align = args.align # yaw align for odometry

############ Fixing groundtruth ############
ground_fix = np.array([[hero_groundtruth[0,0], hero_groundtruth[0,1], hero_groundtruth[0,2], hero_groundtruth[0,4]]])
for i in range(1, len(hero_groundtruth)):
    dx = hero_groundtruth[i, 1] - hero_groundtruth[i - 1, 1]
    dy = hero_groundtruth[i, 2] - hero_groundtruth[i - 1, 2]
    dz = hero_groundtruth[i, 3] - hero_groundtruth[i - 1, 3]
    d = dx*dx + dy*dy + dz*dz
    d = np.sqrt(d)
    yaw = math.atan2(dy, dx)
    fix = [hero_groundtruth[i,0], ground_fix[i-1,1] + d * np.cos(yaw), ground_fix[i-1,2] + d * np.sin(yaw), hero_groundtruth[i,4]]
    ground_fix = np.append(ground_fix, [fix], axis = 0)

############ Fixing odom ############
odom_fix = np.array([[hero_odometry[0,0], hero_odometry[0,1], hero_odometry[0,2], hero_odometry[0, 3]]])
for i in range(1, len(hero_odometry)):
    dx = hero_odometry[i, 1] - hero_odometry[i - 1, 1]
    dy = hero_odometry[i, 2] - hero_odometry[i - 1, 2]
    d = dx*dx + dy*dy
    d = np.sqrt(d)
    yaw = math.atan2(dy, dx) 
    yaw = math.atan2(dy, dx) + align
    fix = [hero_odometry[i,0], odom_fix[i-1,1] + d * np.cos(yaw), odom_fix[i-1,2] + d * np.sin(yaw), yaw]
    odom_fix = np.append(odom_fix, [fix], axis = 0)

############ Plot 1 - X x Y ############
plt.subplot(221)
plt.plot(odom_fix[:,1], odom_fix[:,2],  linewidth=2.0, label='Odom', color='r')
plt.plot(ground_fix[:,1], ground_fix[:,2],  linewidth=2.0, label='Groundtruth', color='g')
plt.rc('font', family='serif')
plt.grid(True)
plt.legend()
plt.legend(loc=0, prop={'size': 16})
plt.title('Odometry Comparison - XY Plot', size = 16)

#plt.axis([-0.6,0.6,-0.6,0.6])
plt.xlabel("X (m)",size = 14)
plt.ylabel('Y (m)',size = 14)

############ Plot 2 - X x Time ############
plt.subplot(222)
plt.plot(odom_fix[:,0], odom_fix[:,1],  linewidth=2.0, label='Odometry', color='r')
plt.plot(ground_fix[:, 0], ground_fix[:,1],  linewidth=2.0, label='Groudtruth', color='g')
plt.rc('font', family='serif')
plt.grid(True)
plt.legend()
#plt.ylim(-1.2,1.2)
plt.legend(loc=0, prop={'size': 14})
plt.title('Odometry Comparison X over Time', size = 16)
plt.xlabel("Time (seconds)",size = 14)
plt.ylabel('X (m)',size = 14)

############ Plot 3 - Y x Time ############
plt.subplot(223)
plt.plot(odom_fix[:,0], odom_fix[:,2],  linewidth=2.0, label='Odometry', color='r')
plt.plot(ground_fix[:, 0], ground_fix[:,2],  linewidth=2.0, label='Groudtruth', color='g')
plt.rc('font', family='serif')
plt.grid(True)
plt.legend()
#plt.ylim(-1.2,1.2)
plt.legend(loc=0, prop={'size': 14})
plt.title('Odometry Comparison Y over Time', size = 16)
plt.xlabel("Time (seconds)",size = 14)
plt.ylabel('Y (m)',size = 14)

############ Plot 4 - Yaw x Time ############
plt.subplot(224)
plt.plot(odom_fix[:,0], odom_fix[:,3],  linewidth=2.0, label='Odometry', color='r')
plt.plot(ground_fix[:, 0], ground_fix[:,3],  linewidth=2.0, label='Groudtruth', color='g')
plt.rc('font', family='serif')
plt.grid(True)
plt.legend()
#plt.ylim(-math.pi,math.pi)
plt.legend(loc=0, prop={'size': 14})
plt.title('Odometry Comparison Yaw over Time', size = 16)
plt.xlabel("Time (seconds)",size = 14)
plt.ylabel('Yaw (radians)',size = 14)


error = np.array([[0,0,0]])
for i in range(0, len(odom_fix)-1):
    idx = (np.abs(ground_fix[:,0] - odom_fix[i, 0])).argmin() # find nearest time index
    e_x = (ground_fix[idx, 1] - odom_fix[i, 1])
    e_y = (ground_fix[idx, 2] - odom_fix[i, 2])
    e_z = (ground_fix[idx, 3] - odom_fix[i, 3])
    error = np.append(error, [[e_x, e_y, e_z]], axis=0)

############ Statisticals ############
print('\x1b[0;33;40m Statiscticals')
print "Groudtruth max distance: ", get_distance(ground_fix[:,1], ground_fix[:,2]), "in meters"
print "Odometry max distance: ", get_distance(odom_fix[:,1], odom_fix[:,2]), "in meters"

print "=== Error X (meters) ==="
print "MAX:", np.max(np.abs(error[:,0]))
print "MAE:", np.average(np.abs(error[:,0])), np.std(np.abs(error[:,0]))
print "RMSE", np.sqrt(np.average(np.power(error[:,0], 2))), np.sqrt(np.std(np.power(error[:,0], 2)))

print "=== Error Y (meters) ==="
print "MAX:", np.max(np.abs(error[:,1]))
print "MAE:", np.average(np.abs(error[:,1])), np.std(np.abs(error[:,0]))
print "RMSE", np.sqrt(np.average(np.power(error[:,1], 2))), np.sqrt(np.std(np.power(error[:,1], 2)))

print "=== Error XY (meters) ==="
print "MAX:", np.max(np.sqrt(np.power(error[:,0], 2) + np.power(error[:,1], 2)))
print "MAE:", np.average(np.sqrt(np.power(error[:,0], 2) + np.power(error[:,1], 2))), np.std(np.sqrt(np.power(error[:,0], 2) + np.power(error[:,1], 2)))
print "RMSE", np.sqrt(np.average(np.power(error[:,0], 2) + np.power(error[:,1], 2))), np.sqrt(np.std(np.power(error[:,0], 2) + np.power(error[:,1], 2)))

print "=== Error Yaw (radians) ==="
print "MAX:", np.max(np.abs(error[:,2]))
print "MAE:", np.average(np.abs(error[:,2])), np.std(np.abs(error[:,0]))
print "RMSE", np.sqrt(np.average(np.power(error[:,2], 2))), np.sqrt(np.std(np.power(error[:,2], 2)))
print '\x1b[0m'

plt.figure()
############ Plot 4 Error - X x Time ############
plt.subplot(221)
plt.plot(odom_fix[:, 0], error[:, 0],  linewidth=2.0, label='Error X', color='black')
plt.rc('font', family='serif')
plt.grid(True)
plt.legend()
plt.legend(loc=0, prop={'size': 14})
plt.title('Error in X over Time', size = 16)
plt.xlabel("Time (seconds)",size = 14)
plt.ylabel('Error (meters)',size = 14)
############ Plot 5 Error - Y x Time ############
plt.subplot(222)
plt.plot(odom_fix[:, 0], error[:, 1],  linewidth=2.0, label='Error Y', color='black')
plt.rc('font', family='serif')
plt.grid(True)
plt.legend()
plt.legend(loc=0, prop={'size': 14})
plt.title('Error in Y over Time', size = 16)
plt.xlabel("Time (seconds)",size = 14)
plt.ylabel('Error (meters)',size = 14)
############ Plot 6 Error - Yaw x Time ############
plt.subplot(223)
plt.plot(odom_fix[:, 0], error[:, 2],  linewidth=2.0, label='Error Yaw', color='black')
plt.rc('font', family='serif')
plt.grid(True)
plt.legend()
plt.legend(loc=0, prop={'size': 14})
plt.title('Error in Yaw over Time', size = 16)
plt.xlabel("Time (seconds)",size = 14)
plt.ylabel('Error (radians)',size = 14)

plt.show()