#!/usr/bin/env python
# Potential field to navigate the robot

import rospy
import numpy as np

from sensor_msgs.msg import Imu

class Cov(object):
    def __init__(self):
        self.ax = []
        self.ay = []
        self.az = []

        self.gx = []
        self.gy = []
        self.gz = []

    def imu_cb(self, msg):
        self.gx.append(msg.angular_velocity.x)
        self.gy.append(msg.angular_velocity.y)
        self.gz.append(msg.angular_velocity.z)
        self.ax.append(msg.linear_acceleration.x)
        self.ay.append(msg.linear_acceleration.y)
        self.az.append(msg.linear_acceleration.z)
        aX = np.vstack((self.ax,self.ay, self.az))
        gX = np.vstack((self.gx,self.gy, self.gz))
        print "Gy Cov:", np.cov(gX)
        print "Acc Cov:", np.cov(aX)

    def run(self):
        rospy.init_node("cov", anonymous=False)
        rospy.Subscriber("hero_1/imu", Imu, self.imu_cb)
        rospy.spin()


# Main function
if __name__ == '__main__':
    try:
        pf = Cov()
        pf.run()
    except rospy.ROSInterruptException:
        rospy.loginfo("[Potential Field Controller]: Closed!")
