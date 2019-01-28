#!/usr/bin/env python

"""
python plot3d_odom.py --file test2_2018-10-21-11-40-37.bag --time_min 2 --time_max 8
"""
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
parser.add_argument('--time_min', type=float, help='Minimal time to cut')
parser.add_argument('--time_max', type=float, help='Maximal time to cut')

args = parser.parse_args()

print ("Plot Velocity Control")
print ("Loading bag file " + args.file)
bag = rosbag.Bag(args.file)

time_min = float(args.time_min)
time_max = float(args.time_max)

topic_ = '/hero_1/odom'

velocities = [[int(str(t)), msg.twist.twist.linear.y, msg.twist.twist.linear.z, msg.twist.twist.angular.x, msg.twist.twist.angular.y] for topic, msg, t in bag.read_messages(topics=[topic_])]
velocities = np.array(velocities)

velocities[:,0] = (velocities[:,0] - velocities[0,0])*1e-9 # nanoseconds to seconds
velocities = velocities[velocities[:,0] < time_max,:]
velocities = velocities[time_min < velocities[:,0],:]

bag.close();
print("Closing bag: All data was loaded.")

fig = plt.figure()

#plt.figure()

plt.plot([0, 2.7, 2.7, time_max], [0, 0, 0.0675425858836, 0.0675425858836],  linewidth=1.0, label='Setpoint', color='black')
#plt.plot(velocities[:,0], velocities[:,3],  linewidth=0.5, label='Tangential Velocity (Encoder)', color='r', linestyle='--')
#plt.plot(velocities[:,0], velocities[:,1],  linewidth=2.0, label='Tangential Velocity (Filtered)', color='r')
plt.plot(velocities[:, 0], velocities[:,4],  linewidth=0.5, label='Tangential Velocity (Encoder)', color='b', linestyle='--')
plt.plot(velocities[:, 0], velocities[:,2],  linewidth=2.0, label='Tangential Velocity (Filtered)', color='b')
plt.rc('font', family='serif')
plt.grid(True)
plt.legend()
plt.xlim(time_min, time_max)
plt.ylim(0, 0.20)
plt.legend(loc=0, prop={'size': 18})
plt.title('Right Wheel Velocity Control', size = 22)

plt.xlabel("Time (seconds)",size = 18)
plt.ylabel('Tangential Velocity (m/s)',size = 18)
plt.savefig(args.file + ".png")


############ Statisticals ############
print('\x1b[0;33;40m Statisticals')
#print "Groudtruth max distance: ", get_distance(ground_fix[:,1], ground_fix[:,2]), "in meters"
#print "Odometry max distance: ", get_distance(odom_fix[:,1], odom_fix[:,2]), "in meters"

#print "=== Error X (cm) ==="
velocities = velocities[velocities[:,0] > 4,:]
print "mean velocity left", np.average(velocities[:,1]), np.std(velocities[:,1])
print "mean velocity error", np.average(np.abs(0.0675425858836-velocities[:,1])), np.std(np.abs(0.0675425858836-velocities[:,1]))

print "mean velocity right", np.average(velocities[:,2]), np.std(velocities[:,2])
print "mean velocity error", np.average(np.abs(0.0675425858836-velocities[:,2])), np.std(np.abs(0.0675425858836-velocities[:,2]))

#print "RMSE", np.sqrt(np.average(np.power(error[:,0], 2)))*100.0, np.sqrt(np.std(np.power(error[:,0], 2)))*100.0

#print "=== Error Y (cm) ==="
#print "MAX:", np.max(np.abs(error[:,1]))*100.0
#print "MAE:", np.average(np.abs(error[:,1]))*100.0, np.std(np.abs(error[:,1]))*100.0
#print "RMSE", np.sqrt(np.average(np.power(error[:,1], 2)))*100.0, np.sqrt(np.std(np.power(error[:,1], 2)))*100.0

#print "=== Error XY (cm) ==="
#print "MAX:", np.max(np.sqrt(np.power(error[:,0], 2) + np.power(error[:,1], 2)))*100.0
#print "MAE:", np.average(np.sqrt(np.power(error[:,0], 2) + np.power(error[:,1], 2)))*100.0, np.std(np.sqrt(np.power(error[:,0], 2) + np.power(error[:,1], 2)))*100.0
#print "RMSE", np.sqrt(np.average(np.power(error[:,0], 2) + np.power(error[:,1], 2)))*100.0, np.sqrt(np.std(np.power(error[:,0], 2) + np.power(error[:,1], 2)))*100.0

#print "=== Error Yaw (radians) ==="
#print "MAX:", np.max(np.abs(error[:,2]))
#print "MAE:", np.average(np.abs(error[:,2])), np.std(np.abs(error[:,2]))
#print "RMSE", np.sqrt(np.average(np.power(error[:,2], 2))), np.sqrt(np.std(np.power(error[:,2], 2)))
#print '\x1b[0m'

plt.show()