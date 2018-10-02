#!/usr/bin/env python
import rospy

from gazebo_msgs.srv import SetLightProperties
from std_msgs.msg import ColorRGBA
import numpy as np
import sys


class BlinkController(object):
    """ docstring for Blink """

    def __init__(self):
        rospy.init_node('blink_controller', anonymous=False)

        rospy.loginfo(
            '[Blink Controller]: Waiting for gazebo color plugin service')
        self.serviceName = str(sys.argv[1]) + '/hat_color'
        rospy.loginfo(self.serviceName)
        rospy.wait_for_service(self.serviceName)
        self.model_color = rospy.ServiceProxy(
            self.serviceName, SetLightProperties)

    def run(self):
        rate = rospy.Rate(0.5)
        rospy.loginfo("[Blink Controller]: Running!")
        color = ColorRGBA()

        while not rospy.is_shutdown():
            c = list(np.random.choice(range(256), size=3))
            color.r = c[0]/256.0
            color.g = c[1]/256.0
            color.b = c[2]/256.0
            color.a = 1.0

            try:
                resp1 = self.model_color("", color, 0.0, 0.0, 0.0)
            except rospy.ServiceException as exc:
                print(
                    "[Blink Controller]: Service did not process request " + str(exc))

            # wait till 10 hz
            rate.sleep()


# Main function
if __name__ == '__main__':
    try:
        bc = BlinkController()
        bc.run()
    except rospy.ROSInterruptException:
        rospy.loginfo("[Blink Controller]: Closed!")
