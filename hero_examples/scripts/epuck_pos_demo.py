#!/usr/bin/env python
import math
import rospy
import tf
import numpy as np

from std_msgs.msg import ColorRGBA
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Pose2D
import time


class HeroDemo(object):
    """ docstring for HeRo demo """

    def __init__(self):
        rospy.init_node('hero_demo', anonymous=False)

        # self.pub_cmd = rospy.Publisher("/hero_1/velocity_controller/cmd_vel", Twist, queue_size=1)
        # rospy.Subscriber("/hero_1/ground_pose", Pose2D, self.gt_pose_cb)
        self.pub_cmd = rospy.Publisher("/epuck_robot_4/mobile_base/cmd_vel", Twist, queue_size=1)
        rospy.Subscriber("/epuck_robot_0/ground_pose", Pose2D, self.gt_pose_cb)
        self.pose = None

    def gt_pose_cb(self, msg):
        self.pose = np.array([msg.x, msg.y, msg.theta])

    def run(self):
        rate = rospy.Rate(5)
        rospy.loginfo("[Epuck Demo]: Running!")

        vel = Twist()

        # goal = np.array([0.1, 0.1, 0.0])
        waypoints = [np.array([-0.50, 0.30, 0.0]), 
        np.array([0.57, 0.30, 0.0]), 
        np.array([0.57, -1.10, 0.0]), 
        np.array([-0.50, -1.10, 0.0])]

        cur_goal = 0

        while not rospy.is_shutdown():
            if np.any(self.pose) == None:
                rate.sleep()
                continue
            goal = waypoints[cur_goal]
            diff = goal - self.pose
            dist = np.sqrt(diff[0]*diff[0] + diff[1]*diff[1])
            if dist < 0.02:
                vel.linear.x = 0
                vel.angular.z = 0
                cur_goal = (1+cur_goal) % len(waypoints)
            else:
                # vel.linear.x = max(min(0.08, dist), 0.04) #hero
                vel.linear.x = max(min(12, dist), 7) #epuck
                vel.angular.z = (math.atan2(
                    goal[1]-self.pose[1], goal[0]-self.pose[0]) - self.pose[2])
                if vel.angular.z >= math.pi:
                    vel.angular.z = (-2.0 * math.pi + vel.angular.z)
                elif vel.angular.z < -math.pi:
                    vel.angular.z = (2.0 * math.pi + vel.angular.z)
                
                vel.angular.z = 1.0 * vel.angular.z
                vel.linear.x = vel.linear.x

                print("Goal #{} - error: {} - u: [{},{}]".format(
                    cur_goal, dist, vel.linear.x, vel.angular.z))
                self.pub_cmd.publish(vel)
            rate.sleep()


# Main function
if __name__ == '__main__':
    try:
        demo = HeroDemo()
        demo.run()
    except rospy.ROSInterruptException:
        rospy.loginfo("[HeRo Demo]: Closed!")
