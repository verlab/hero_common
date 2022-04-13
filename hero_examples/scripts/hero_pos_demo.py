#!/usr/bin/env python
import math
import rospy
import tf
import numpy as np

from std_msgs.msg import ColorRGBA
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
import time


class HeroDemo(object):
    """ docstring for HeRo demo """

    def __init__(self):
        rospy.init_node('hero_demo', anonymous=False)
        topics = [topic[0] for topic in rospy.get_published_topics("/")]
        self.odoms = {}
        namespaces = []
        for topic in topics:
            if "odom" in topic:
                namespaces.append(topic.split("/")[1])

        rospy.loginfo("Founded robots:")
        for namespace in namespaces:
            rospy.loginfo(">> " + namespace)
        self.robots = {}
        for namespace in namespaces:
            pub_cmd = rospy.Publisher(
                '/'+namespace+"/velocity_controller/cmd_vel", Twist, queue_size=1)
            pub_color = rospy.Publisher(
                '/'+namespace+"/led", ColorRGBA, queue_size=1)
            self.robots[namespace] = [pub_cmd, pub_color, np.array([0, 0, 0])]
            rospy.Subscriber('/'+namespace + "/odom",
                             Odometry, self.odom_cb, namespace)

    def odom_cb(self, msg, namespace):
        w = (msg.pose.pose.orientation.x, msg.pose.pose.orientation.y,
             msg.pose.pose.orientation.z, msg.pose.pose.orientation.w)
        euler = tf.transformations.euler_from_quaternion(w)
        row, pitch, yaw = euler
        x = msg.pose.pose.position.x
        y = msg.pose.pose.position.y
        self.robots[namespace][2] = np.array([x, y, yaw])

    def run(self):
        rate = rospy.Rate(5)
        rospy.loginfo("[HeRo Demo]: Running!")
        color = ColorRGBA()
        color.r = 1.0
        color.b = 1.0
        color.a = 1.0

        vel = Twist()

        # goal = np.array([0.1, 0.1, 0.0])
        # waypoints = [np.array([0.3, 0.0, 0.0]), np.array(
        #     [0.3, 0.3, 0.0]), np.array([0.0, 0.3, 0.0]), np.array([0.0, 0.0, 0.0])]
        waypoints = [np.array([-0.50, 0.30, 0.0]), 
        np.array([0.57, 0.30, 0.0]), 
        np.array([0.57, -1.10, 0.0]), 
        np.array([-0.50, -1.10, 0.0])]
        cur_goal = 0

        while not rospy.is_shutdown():
            goal = waypoints[cur_goal]
            for id in self.robots:
                pub_cmd, pub_color, pose = self.robots[id]
                diff = goal - pose
                dist = np.sqrt(diff[0]*diff[0] + diff[1]*diff[1])
                color.a = dist/0.4
                if dist < 0.02:
                    vel.linear.x = 0
                    vel.angular.z = 0
                    cur_goal = (1+cur_goal) % len(waypoints)
                else:
                    vel.linear.x = max(min(0.04, dist), 0.02)
                    vel.angular.z = (math.atan2(
                        goal[1]-pose[1], goal[0]-pose[0]) - pose[2])
                    if vel.angular.z >= math.pi:
                        vel.angular.z = (-2.0 * math.pi + vel.angular.z)
                    elif vel.angular.z < -math.pi:
                        vel.angular.z = (2.0 * math.pi + vel.angular.z)
                    
                    vel.angular.z = 1.0 * vel.angular.z

                    # if vel.angular.z >= 0:
                    #     vel.angular.z = max(min(4.0, vel.angular.z), 1.0)
                    # else:
                    #     vel.angular.z = max(min(-4.0, vel.angular.z), -1.0)

                    # if abs(theta) > 0.4:
                    #     vel.linear.x = 0.0
                    # else:
                    #     vel.angular.z = 0.0

                print("Goal #{} - error: {} - u: [{},{}]".format(
                    cur_goal, dist, vel.linear.x, vel.angular.z))
                pub_cmd.publish(vel)
                pub_color.publish(color)
            rate.sleep()


# Main function
if __name__ == '__main__':
    try:
        demo = HeroDemo()
        demo.run()
    except rospy.ROSInterruptException:
        rospy.loginfo("[HeRo Demo]: Closed!")
