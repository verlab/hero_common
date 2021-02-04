#!/usr/bin/env python
import rospy

from std_msgs.msg import ColorRGBA
import numpy as np
import sys


class BlinkDemo(object):
    """ docstring for Blink """

    def __init__(self):
        rospy.init_node('blink_demo', anonymous=False)

        self.topic_name = str(sys.argv[1]) + '/led'
        self.pub = rospy.Publisher(self.topic_name, ColorRGBA, queue_size=1)
        rospy.loginfo(self.topic_name)
        self.rate = rospy.Rate(1) # 10hz

    def run(self):
        rospy.loginfo("[Blink Demo]: Running!")
        color = ColorRGBA()

        while not rospy.is_shutdown():
            c = list(np.random.choice(range(256), size=3))
            color.r = c[0]/256.0
            color.g = c[1]/256.0
            color.b = c[2]/256.0
            color.a = 0.5
            self.pub.publish(color)
            # wait till 10 hz
            self.rate.sleep()


# Main function
if __name__ == '__main__':
    try:
        bc = BlinkDemo()
        bc.run()
    except rospy.ROSInterruptException:
        rospy.loginfo("[Blink Demo]: Closed!")
        


        
