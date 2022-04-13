#!/usr/bin/env python
# Potential field to navigate the robot

import rospy
import math
import numpy as np
import tf
import sys

from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import PoseStamped

from std_msgs.msg import ColorRGBA


class RandomWalk(object):
    def __init__(self):
        self.namespace = str(sys.argv[1])
        # self.odom = Odometry()
        self.laser = LaserScan()
        self.cmd_vel = Twist()
        self.color = ColorRGBA()
        self.color.g = 1.0
        self.color.a = 1.0
        # self.goal = PoseStamped()
        # self.att_gain = 1.2
        # self.rep_gain = 0.4
        self.p0 = 0.12  # in meters
        # self.kTheta = 1.4
        # self.threshold = 0.10
        self.max_speed = 0.10
        # self.STATUS = 0
        self.laser_start = False

    def odom_cb(self, msg):
        self.odom = msg

    def laser_cb(self, msg):
        self.laser = msg
        self.laser_start = True

    def goal_cb(self, msg):
        self.goal = msg

    def run(self):
        rospy.init_node("random_walk", anonymous=True)

        self.pub = rospy.Publisher(
            self.namespace + "/velocity_controller/cmd_vel", Twist, queue_size=1)

        self.pub_color = rospy.Publisher(
            self.namespace + "/led", ColorRGBA, queue_size=1)

        rospy.Subscriber(self.namespace + "/laser",
                         LaserScan, self.laser_cb)
        
        self.rate = rospy.Rate(10)  # 20 hz
        self.cmd_vel.linear.x = 0.07
        self.cmd_vel.angular.z = 0.0

        self.state_blocked = True
        self.sent_led = False
        rospy.loginfo("Starting Random Walk Controller for %s", self.namespace)
        self.scale = 2.0
        while not rospy.is_shutdown():
            if not self.laser_start:
                rospy.loginfo("[%s] Laser is not working yet!", self.namespace)
                self.rate.sleep()
                continue
            rospy.loginfo_once("[%s] Laser is working!", self.namespace)

            self.color.g = 1.0
            self.color.r = 0.0

            self.cmd_vel.linear.x = 0.06

            frep_x = 0.0
            frep_y = 0.0
            for i in range(len(self.laser.ranges)-1):
                pq = self.laser.ranges[i]
                if pq < self.p0:
                    alpha = i * self.laser.angle_increment + self.laser.angle_min
                    frep_x += 0.0001 * (1.0/pq - 1.0/self.p0) * math.cos(alpha)/(pq**2)
                    frep_y += 0.0001 * (1.0/pq - 1.0/self.p0) * math.sin(alpha)/(pq**2)
                    self.color.r = 1
                    self.color.g = 0
                    self.cmd_vel.linear.x = 0.04
            fx = frep_x
            fy = frep_y

            # fr = math.sqrt(fx**2 + fy**2)
            # self.cmd_vel.linear.x = min(fr, self.max_speed/2.0)

            if self.color.r:
                self.cmd_vel.angular.z = (math.atan2(fy, fx)) + math.pi
                if self.cmd_vel.angular.z > math.pi:
                    self.cmd_vel.angular.z = - 2 * math.pi + self.cmd_vel.angular.z
                elif self.cmd_vel.angular.z < -math.pi:
                    self.cmd_vel.angular.z = 2 * math.pi + self.cmd_vel.angular.z
                self.cmd_vel.angular.z = max(-4.0, min(4.0, self.cmd_vel.angular.z))
            else:
                self.cmd_vel.angular.z = 0
            
            self.pub.publish(self.cmd_vel)
            self.rate.sleep()

        self.cmd_vel.linear.x = 0.00
        self.cmd_vel.angular.z = 0.00
        self.pub.publish(self.cmd_vel)


# Main function
if __name__ == '__main__':
    try:
        rw = RandomWalk()
        rw.run()
    except rospy.ROSInterruptException:
        rospy.loginfo("[Potential Field Controller]: Closed!")
