#!/usr/bin/env python3
import imp
import rospy

from std_msgs.msg import ColorRGBA
import time
import numpy as np
import sys


class BlinkDemo(object):
    """ docstring for Blink """

    def __init__(self):
        rospy.init_node('blink_demo1', anonymous=False)
        self.pub = rospy.Publisher('/hero_4/led', ColorRGBA, queue_size=10)

    def run(self):
        # rate = rospy.Rate(5)
        rospy.loginfo("[Blink Demo]: Running!")
        color = ColorRGBA()
        B = [0.6, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8,0.6]
        i = 0
        while not rospy.is_shutdown():
            # c = list(np.random.choice(range(256), size=3))
            self.pub.publish(color)
            print("color.r: ")
            s = input("")
            color.r = float(s)
            print("color.g: ")
            s = input("")
            color.g  = float(s)
            print("color.b: ")
            s = input("")
            color.b = float(s)
            color.a = 1.0
            print(color)
            input("Press any key to send the color...")
            # color.r = 0
            # color.g = 0
            # color.b = 0.8
            # color.a = B[i % (len(B))]
            # i += 1            

            # self.pub.publish(color)
            
            # wait till 2 sec
            time.sleep(2)


# Main function
if __name__ == '__main__':
    try:
        bc = BlinkDemo()
        bc.run()
    except rospy.ROSInterruptException:
        rospy.loginfo("[Blink Demo]: Closed!")
