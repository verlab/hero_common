#!/usr/bin/env python

import matplotlib.pyplot as plt
import numpy as np
import rosbag
import sys
import math

print ("Plot Odometry Comparision")
print ("Loading bag file " + sys.argv[1])
bag = rosbag.Bag(sys.argv[1])
odom_t = '/hero_1/odom'
odom_t = '/robot_real_0/odom'
hero_odometry = [[int(str(t)), msg.pose.pose.position.x, msg.pose.pose.position.y, msg.pose.pose.position.z] for topic, msg, t in bag.read_messages(topics=[odom_t])]
hero_odometry = np.array(hero_odometry)

ground_t = '/hero_1/ground_pose'
ground_t = '/epuck_1/ground_pose'
hero_groundtruth = [[int(str(t)), msg.x, msg.y, msg.theta] for topic, msg, t in bag.read_messages(topics=[ground_t])]
hero_groundtruth = np.array(hero_groundtruth)

bag.close();
print("Closing bag: All data was loaded.")

plt.subplot(221)
plt.plot(hero_odometry[:,1], hero_odometry[:,2],  linewidth=2.0, label='Odometry', color='g')
plt.plot(hero_groundtruth[:, 1], hero_groundtruth[:,2],  linewidth=2.0, label='Groudtruth', color='b')
plt.rc('font', family='serif')
plt.grid(True)
plt.legend()
plt.legend(loc=0, prop={'size': 14})
plt.title('Odometry Comparison - XY Plot', size = 16)
plt.ylim(-1.2,1.2)
plt.xlim(-1.2,1.2)
plt.xlabel("X (m)",size = 14)
plt.ylabel('Y (m)',size = 14)

plt.subplot(222)
plt.plot(hero_odometry[:,0], hero_odometry[:,1],  linewidth=2.0, label='Odometry X', color='g')
plt.plot(hero_groundtruth[:, 0], hero_groundtruth[:,1],  linewidth=2.0, label='Groudtruth X', color='b')
plt.rc('font', family='serif')
plt.grid(True)
plt.legend()
plt.ylim(-1.2,1.2)
plt.legend(loc=0, prop={'size': 14})
plt.title('Odometry Comparison X over Time', size = 16)
plt.xlabel("Time (seconds)",size = 14)
plt.ylabel('X (m)',size = 14)

plt.subplot(223)
plt.plot(hero_odometry[:,0], hero_odometry[:,2],  linewidth=2.0, label='Odometry Y', color='g')
plt.plot(hero_groundtruth[:, 0], hero_groundtruth[:,2],  linewidth=2.0, label='Groudtruth Y', color='b')
plt.rc('font', family='serif')
plt.grid(True)
plt.legend()
plt.ylim(-1.2,1.2)
plt.legend(loc=0, prop={'size': 14})
plt.title('Odometry Comparison Y over Time', size = 16)
plt.xlabel("Time (seconds)",size = 14)
plt.ylabel('Y (m)',size = 14)

plt.subplot(224)
plt.plot(hero_odometry[:,0], hero_odometry[:,3],  linewidth=2.0, label='Odometry Theta', color='g')
plt.plot(hero_groundtruth[:, 0], hero_groundtruth[:,3],  linewidth=2.0, label='Groudtruth Theta', color='b')
plt.rc('font', family='serif')
plt.grid(True)
plt.legend()
plt.ylim(-math.pi,math.pi)
plt.legend(loc=0, prop={'size': 14})
plt.title('Odometry Comparison Theta over Time', size = 16)
plt.xlabel("Time (seconds)",size = 14)
plt.ylabel('Theta (radians)',size = 14)


d_odometry = 0.0
for i in range(1, len(hero_odometry[:,1])-1):
    dx = hero_odometry[i,1] - hero_odometry[i-1,1]
    dy = hero_odometry[i,2] - hero_odometry[i-1,2]
    d_odometry += np.sqrt(dx*dx + dy*dy)

d_ground = 0.0
for i in range(1, len(hero_groundtruth[:,1])-1):
    dx = hero_groundtruth[i,1] - hero_groundtruth[i-1,1]
    dy = hero_groundtruth[i,2] - hero_groundtruth[i-1,2]
    d_ground += np.sqrt(dx*dx + dy*dy)

print ("Distance Odometry:" + str(d_odometry) + " meters")
print ("Distance Groundtruth:" + str(d_ground) + " meters")

plt.show()