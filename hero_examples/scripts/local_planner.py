#!/usr/bin/env python
# Go to position - Position Controller

import rospy
import math
import numpy as np
import tf
import sys

from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from geometry_msgs.msg import PoseStamped, Pose2D


class PositionController(object):
    def __init__(self):
        self.namespace = str(sys.argv[1])
        self.odom = Odometry()
        self.cmd_vel = Twist()
        self.goal = Pose2D()
        self.threshold = 0.01
        self.max_speed = 0.30
        self.new_goal = False

    def odom_cb(self, msg):
        self.odom = msg

    def goal_cb(self, msg):
        self.goal = msg
        self.new_goal = True
        rospy.loginfo("Getting new goal -> ({},{})".format(self.goal.x, self.goal.y))


    def run(self):
        rospy.init_node("local_controller", anonymous=True)
        rospy.loginfo("[{}] Starting local planner...".format(self.namespace))
        self.pub = rospy.Publisher("cmd_vel", Twist, queue_size=1)
        rospy.Subscriber("odom", Odometry, self.odom_cb)
        rospy.Subscriber("goal", Pose2D, self.goal_cb)

        self.rate = rospy.Rate(20)  # 20 hz

        while not rospy.is_shutdown():
            if (self.new_goal == False):
                continue
            w = (self.odom.pose.pose.orientation.x, self.odom.pose.pose.orientation.y,
                 self.odom.pose.pose.orientation.z, self.odom.pose.pose.orientation.w)
            euler = tf.transformations.euler_from_quaternion(w)
            yaw = euler[2]

            dx = self.goal.x - self.odom.pose.pose.position.x
            dy = self.goal.y - self.odom.pose.pose.position.y
            d = math.sqrt(dx ** 2 + dy ** 2)

            if abs(d) <= self.threshold:
                rospy.loginfo("Reaching the goal -> R({},{}) ~ G({},{})".format(self.odom.pose.pose.position.x, self.odom.pose.pose.position.y, self.goal.x, self.goal.y))
                self.cmd_vel.linear.x = 0.0
                self.cmd_vel.angular.z = 0.0
                self.new_goal = False
            else:
                self.cmd_vel.linear.x = min(d, self.max_speed)
                theta = math.atan2(dy, dx)
                diff_theta = (theta - yaw)
                              
                if diff_theta > math.pi:
                    diff_theta = - 2 * math.pi + diff_theta
                elif diff_theta < -math.pi:
                    diff_theta = 2 * math.pi + diff_theta

                self.cmd_vel.angular.z =  diff_theta
                if abs(diff_theta) > math.pi/2.0:
                    if diff_theta > 0:
                        diff_theta = diff_theta -  math.pi  
                    elif diff_theta < 0:
                        diff_theta = math.pi + diff_theta
                    self.cmd_vel.linear.x = -self.cmd_vel.linear.x
                    self.cmd_vel.angular.z =  diff_theta
                self.cmd_vel.angular.z = self.cmd_vel.angular.z*2.0
  

            self.pub.publish(self.cmd_vel)
            self.rate.sleep()


# Main function
if __name__ == '__main__':
    try:
        controller = PositionController()
        controller.run()
    except rospy.ROSInterruptException:
        rospy.loginfo("[{}]: Halt!".format(controller.namespace))
