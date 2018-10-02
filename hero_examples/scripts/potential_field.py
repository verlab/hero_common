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

# Status debug
from gazebo_msgs.srv import SetLightProperties
from std_msgs.msg import ColorRGBA


class PotentialField(object):
    def __init__(self):
        self.namespace = str(sys.argv[1])
        self.odom = Odometry()
        self.laser = LaserScan()
        self.cmd_vel = Twist()
        self.goal = PoseStamped()
        self.att_gain = 1.2
        self.rep_gain = 0.4
        self.p0 = 0.20  # in meters
        self.kTheta = 1.4
        self.threshold = 0.10
        self.max_speed = 0.25
        self.STATUS = 0

    def odom_cb(self, msg):
        self.odom = msg

    def laser_cb(self, msg):
        self.laser = msg

    def goal_cb(self, msg):
        self.goal = msg

    def status_cb(self, event):
        try:
            if self.STATUS == 0:  # Reach Goal
                resp1 = self.model_color("", ColorRGBA(
                    0.0, 0.9, 0.1, 1.0), 0.0, 0.0, 0.0)
            elif self.STATUS == 1:  # Searching Goal
                resp1 = self.model_color("", ColorRGBA(
                    1.0, 0.6, 0.0, 1.0), 0.0, 0.0, 0.0)
            elif self.STATUS == 2:  # Collision detected
                resp1 = self.model_color("", ColorRGBA(
                    0.9, 0.0, 0.0, 1.0), 0.0, 0.0, 0.0)
        except rospy.ServiceException as exc:
            rospy.logwarn(
                "[Blink Controller]: Service did not process request " + str(exc))

    def run(self):
        rospy.init_node("potential_field", anonymous=False)
        self.pub = rospy.Publisher(
            self.namespace + "/cmd_vel", Twist, queue_size=1)
        rospy.Subscriber(self.namespace + "/laser_scan",
                         LaserScan, self.laser_cb)
        rospy.Subscriber(self.namespace + "/odom", Odometry, self.odom_cb)
        rospy.Subscriber(self.namespace + "/goal", PoseStamped, self.goal_cb)

        # Wait for color service
        rospy.wait_for_service(self.namespace + "/hat_color")
        self.model_color = rospy.ServiceProxy(
            self.namespace + "/hat_color", SetLightProperties)
        rospy.Timer(rospy.Duration(0.6), self.status_cb)

        self.rate = rospy.Rate(20)  # 20 hz

        while not rospy.is_shutdown():
            w = (self.odom.pose.pose.orientation.x, self.odom.pose.pose.orientation.y,
                 self.odom.pose.pose.orientation.z, self.odom.pose.pose.orientation.w)
            euler = tf.transformations.euler_from_quaternion(w)
            yaw = euler[2]

            dx = self.goal.pose.position.x - self.odom.pose.pose.position.x
            dy = self.goal.pose.position.y - self.odom.pose.pose.position.y
            d = math.sqrt(dx ** 2 + dy ** 2)

            if abs(d) <= self.threshold:
                self.STATUS = 0
                self.cmd_vel.linear.x = 0.0
                self.cmd_vel.angular.z = 0.0
            else:
                self.STATUS = 1
                theta = math.atan2(dy, dx)
                d = min(d, self.laser.range_max)
                fatt_x = self.att_gain * math.cos(theta - yaw) * d
                fatt_y = self.att_gain * math.sin(theta - yaw) * d
                frep_x = 0.0
                frep_y = 0.0
                for i in range(len(self.laser.ranges)-1):
                    pq = self.laser.ranges[i]
                    if pq <= self.p0:
                        self.STATUS = 2
                        alpha = i * self.laser.angle_increment + self.laser.angle_min
                        frep_x += self.rep_gain * \
                            (1.0/pq - 1.0/self.p0) * \
                            math.cos(alpha)/(pq**2)
                        frep_y += self.rep_gain * \
                            (1.0/pq - 1.0/self.p0) * \
                            math.sin(alpha)/(pq**2)
                fx = fatt_x - frep_x
                fy = fatt_y - frep_y
                fr = math.sqrt(fx**2 + fy**2)
                self.cmd_vel.linear.x = min(fr, self.max_speed/2.0)

                self.cmd_vel.angular.z = (math.atan2(fy, fx))
                if self.cmd_vel.angular.z > math.pi:
                    self.cmd_vel.angular.z = - 2 * math.pi + self.cmd_vel.angular.z
                elif self.cmd_vel.angular.z < -math.pi:
                    self.cmd_vel.angular.z = 2 * math.pi + self.cmd_vel.angular.z

            self.pub.publish(self.cmd_vel)
            self.rate.sleep()


# Main function
if __name__ == '__main__':
    try:
        pf = PotentialField()
        pf.run()
    except rospy.ROSInterruptException:
        rospy.loginfo("[Potential Field Controller]: Closed!")
