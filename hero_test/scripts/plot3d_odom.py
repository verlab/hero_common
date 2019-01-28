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
parser.add_argument('--dim', type=float, help='Dimentions')
parser.add_argument('--name', type=float, help='Robot')

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
#plt.figure()
#plt.subplot(221)
plt.plot(odom_fix[:,1], odom_fix[:,2],  linewidth=2.0, label='Odometry', color='r', linestyle="--")
plt.plot(ground_fix[:,1], ground_fix[:,2],  linewidth=2.0, label='Groundtruth', color='black')
plt.rc('font', family='serif')
plt.grid(True)
plt.legend()
plt.legend(loc=0, prop={'size': 16})
plt.title(' HeRo - Trajectory Comparison', size = 22)
plt.ylim(-args.dim,args.dim)
plt.xlim(-args.dim,args.dim)

#plt.axis([-0.6,0.6,-0.6,0.6])
plt.xlabel("X (m)",size = 18)
plt.ylabel('Y (m)',size = 18)

############ Plot 2 - X x Time ############
#plt.figure()
##plt.subplot(222)
#plt.plot(odom_fix[:,0], odom_fix[:,1],  linewidth=2.0, label='Odometry', color='r')
#plt.plot(ground_fix[:, 0], ground_fix[:,1],  linewidth=2.0, label='Groudtruth', color='g')
#plt.rc('font', family='serif')
#plt.grid(True)
#plt.legend()
#plt.ylim(-args.dim,args.dim)
#plt.legend(loc=0, prop={'size': 18})
#plt.title('Evolution of X-axis', size = 22)
#
#plt.xlabel("Time (seconds)",size = 18)
#plt.ylabel('X (m)',size = 18)
#
############# Plot 3 - Y x Time ############
#plt.figure()
##plt.subplot(223)
#plt.plot(odom_fix[:,0], odom_fix[:,2],  linewidth=2.0, label='Odometry', color='r')
#plt.plot(ground_fix[:, 0], ground_fix[:,2],  linewidth=2.0, label='Groudtruth', color='g')
#plt.rc('font', family='serif')
#plt.grid(True)
#plt.legend()
#plt.ylim(-args.dim,args.dim)
#plt.legend(loc=0, prop={'size': 18})
#plt.title('Evolution of Y-axis', size = 22)
#plt.xlabel("Time (seconds)",size = 18)
#plt.ylabel('Y (m)',size = 18)
#
############# Plot 4 - Yaw x Time ############
#plt.figure()
##plt.subplot(224)
#plt.plot(odom_fix[:,0], odom_fix[:,3],  linewidth=2.0, label='Odometry', color='r')
#plt.plot(ground_fix[:, 0], ground_fix[:,3],  linewidth=2.0, label='Groudtruth', color='g')
#plt.rc('font', family='serif')
#plt.grid(True)
#plt.legend()
#plt.ylim(-math.pi,math.pi)
#plt.legend(loc=0, prop={'size': 18})
#plt.title('Evolution of Yaw', size = 22)
#plt.xlabel("Time (seconds)",size = 18)
#plt.ylabel('Yaw (radians)',size = 18)
#plt.xticks(fontsize=18, rotation=0)
#plt.yticks(fontsize=18, rotation=0)


error = np.array([[0,0,0]])
for i in range(0, len(odom_fix)-1):
    idx = (np.abs(ground_fix[:,0] - odom_fix[i, 0])).argmin() # find nearest time index
    d = np.sqrt(np.power(ground_fix[:,1] - odom_fix[i, 1], 2) + np.power(ground_fix[:,2] - odom_fix[i, 2], 2))
    idx = (np.abs(d)).argmin() # find nearest time index
    
    e_x = (ground_fix[idx, 1] - odom_fix[i, 1])
    e_y = (ground_fix[idx, 2] - odom_fix[i, 2])
    if ground_fix[idx, 3] > math.pi:
        ground_fix[idx, 3] = ground_fix[idx, 3] - 2*math.pi
    if ground_fix[idx, 3] < -math.pi:
        ground_fix[idx, 3] = ground_fix[idx, 3] + 2*math.pi

    if odom_fix[i, 3] > math.pi:
        odom_fix[i, 3] = odom_fix[i, 3] - 2*math.pi
    if odom_fix[i, 3] < -math.pi:
        odom_fix[i, 3] = odom_fix[i, 3] + 2*math.pi
    if abs(ground_fix[idx, 3] - odom_fix[i, 3]) < math.pi/6:
        e_z = (ground_fix[idx, 3] - odom_fix[i, 3])
        
    error = np.append(error, [[e_x, e_y, e_z]], axis=0)

############ Statisticals ############
print('\33[96m Statiscticals')
true_d = get_distance(ground_fix[:,1], ground_fix[:,2]) * 100
odom_d = get_distance(odom_fix[:,1], odom_fix[:,2]) * 100
print "Groudtruth max distance: ", true_d, "in cm"
print "Odometry max distance: ", odom_d, "in cm"

print "=== Error X (cm) ==="
ex = error[:,0] * 100.0
max_ex = np.max(np.abs(ex))
print "MAX:", max_ex, max_ex/true_d * 100.0
mae_ex = np.average(np.abs(ex))
print "MAE:", mae_ex, mae_ex/true_d * 100.0, np.std(np.abs(ex))
rmse_ex = np.sqrt(np.average(np.power(ex, 2)))
print "RMSE", rmse_ex, rmse_ex/true_d * 100.0, np.sqrt(np.std(np.power(ex, 2)))


print "=== Error Y (cm) ==="
ey = error[:,1] * 100.0
max_ey = np.max(np.abs(ey))
print "MAX:", max_ey, max_ey/true_d * 100.0
mae_ey = np.average(np.abs(ey))
print "MAE:", mae_ey, mae_ey/true_d * 100.0, np.std(np.abs(ey))
rmse_ey = np.sqrt(np.average(np.power(ey, 2)))
print "RMSE", rmse_ey, rmse_ey/true_d * 100.0, np.sqrt(np.std(np.power(ey, 2)))


print "=== Error XY (cm) ==="
max_exy = np.max(np.sqrt(np.power(ex, 2) + np.power(ey, 2)))
print "MAX:", max_exy, max_exy/true_d * 100.0
mae_exy = np.average(np.sqrt(np.power(ex, 2) + np.power(ey, 2)))
print "MAE:", mae_exy, mae_exy/true_d * 100.0, np.std(np.sqrt(np.power(ex, 2) + np.power(ey, 2)))
rmse_exy = np.sqrt(np.average(np.power(np.sqrt(np.power(ex, 2) + np.power(ey, 2)), 2)))
print "RMSE", rmse_exy, rmse_exy/true_d * 100.0, np.std(np.sqrt(np.power(ex, 2) + np.power(ey, 2)))


print "=== Error Yaw (radians) ==="
et = error[:,2]
max_et = np.max(np.abs(et))
print "MAX:", max_et, np.rad2deg(max_et)
mae_et = np.average(np.abs(et))
print "MAE:", mae_et, np.rad2deg(mae_et), np.std(np.abs(et))
rmse_et = np.sqrt(np.average(np.power(et, 2)))
print "RMSE", rmse_et, np.rad2deg(rmse_et), np.std(np.power(et, 2))

print '\33[0m'

plt.figure()
############ Plot 4 Error - X x Time ############
#plt.subplot(221)
plt.plot(odom_fix[:, 0], error[:, 0],  linewidth=2.0, label='Error X', color='black')
plt.rc('font', family='serif')
plt.grid(True)
plt.legend()
plt.ylim(-0.12,0.12)
plt.legend(loc=0, prop={'size': 18})
plt.title('Evolution of the Error in X-axis', size = 22)
plt.xlabel("Time (s)",size = 18)
plt.ylabel('Error (m)',size = 18)
############ Plot 5 Error - Y x Time ############
plt.figure()
#plt.subplot(222)
plt.plot(odom_fix[:, 0], error[:, 1],  linewidth=2.0, label='Error Y', color='black')
plt.rc('font', family='serif')
plt.grid(True)
plt.legend()
plt.ylim(-0.12,0.12)
plt.legend(loc=0, prop={'size': 18})
plt.title('Evolution of the Error in Y-axis', size = 22)
plt.xlabel("Time (s)",size = 18)
plt.ylabel('Error (m)',size = 18)

############ Plot 6 Error - Yaw x Time ############
plt.figure()
#plt.subplot(223)
plt.plot(odom_fix[:, 0], error[:, 2],  linewidth=2.0, label=r'Error $\theta$', color='black')
plt.rc('font', family='serif')
plt.grid(True)
plt.legend()
plt.ylim(-math.pi,math.pi)
plt.legend(loc=0, prop={'size': 18})    
plt.title(r'Evolution of the Error in $\theta$', size = 22)
plt.xlabel("Time (s)",size = 18)
plt.ylabel('Error (radians)',size = 18)

plt.show()