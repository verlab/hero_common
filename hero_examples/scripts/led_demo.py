#!/usr/bin/env python
import rospy

from std_msgs.msg import ColorRGBA
import numpy as np
import sys


class LEDDemo(object):
    """ docstring for Blink """

    def __init__(self):
        rospy.init_node('led_demo', anonymous=False)
        self.pubs = []
        self.num_heros = 5
        for i in range(self.num_heros):
            pub_ = rospy.Publisher('/hero_{}/led'.format(i), ColorRGBA, queue_size=0)
            self.pubs.append(pub_)

    def colorID(self, idx):
        color = ColorRGBA()
        color.a = 1.0
        if idx == 0:
            color.r, color.g, color.b = 1.0, 0.0, 0.0
        elif idx == 1:
            color.r, color.g, color.b = 0.0, 1.0, 0.0
        elif idx == 2:
            color.r, color.g, color.b = 0.0, 0.0, 1.0
        elif idx == 3:
            color.r, color.g, color.b = 1.0, 0.0, 1.0
        elif idx == 4:
            color.r, color.g, color.b = 0.0, 1.0, 1.0
        elif idx == 5:
            color.r, color.g, color.b = 1.0, 1.0, 0.0
        elif idx == 6:
            color.r, color.g, color.b = 0.5, 1.0, 0.5
        elif idx == 7:
            color.r, color.g, color.b = 1.0, 0.5, 1.0
        elif idx == 8:
            color.r, color.g, color.b = 1.0, 1.0, 0.5
        elif idx == 9:
            color.r, color.g, color.b = 0.5, 1.0, 1.0
        return color


    def run(self):
        rospy.loginfo("[LED Demo]: Running!")
        rate_ = rospy.Rate(1)
        while not rospy.is_shutdown():
            for i in range(self.num_heros):
                # rospy.loginfo("hero_{}: {}".format(i, self.colorID(i)))
                self.pubs[i].publish(self.colorID(i))
            rate_.sleep()


# Main function
if __name__ == '__main__':
    try:
        bc = LEDDemo()
        bc.run()
    except rospy.ROSInterruptException:
        rospy.loginfo("[LED Demo]: Closed!")
