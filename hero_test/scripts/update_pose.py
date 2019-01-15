#!/usr/bin/env python
import rospy

from hero_driver.srv import SetOdom
from geometry_msgs.msg import Pose2D
import numpy as np
import sys


class UpdatePose(object):
    """ docstring for Blink """

    def __init__(self):
        rospy.init_node('update_pose', anonymous=False)

        rospy.loginfo(
            '[Update Pose]: Waiting for hero set pose service')
        self.serviceName = "/hero_1/set_odom"
        rospy.wait_for_service(self.serviceName)
        self.hero_set_odom = rospy.ServiceProxy(
            self.serviceName, SetOdom)
        rospy.Subscriber("/hero_1/ground_pose",
                         Pose2D, self.global_pose_cb)

        self.mocal_pose = Pose2D()

    def global_pose_cb(self, msg): # update hero odometry
        self.mocal_pose.x = msg.x
        self.mocal_pose.y = msg.y
        self.mocal_pose.theta = msg.theta

    def run(self):
        rate = rospy.Rate(0.2)
        rospy.loginfo("[Updating Odometry with Mocap]: Running!")

        while not rospy.is_shutdown():
            try:
                rospy.loginfo("[Updating Odometry with Mocap] Updating...")
                print self.mocal_pose
                resp1 = self.hero_set_odom(self.mocal_pose.x, self.mocal_pose.y, self.mocal_pose.theta)
            except rospy.ServiceException as exc:
                pass
                #print(
                #    "[Hero Set Odom]: Service did not process request " + str(exc))

            # wait till 10 hz
            rate.sleep()


# Main function
if __name__ == '__main__':
    try:
        up = UpdatePose()
        up.run()
    except rospy.ROSInterruptException:
        rospy.loginfo("[Update Pose]: Closed!")
