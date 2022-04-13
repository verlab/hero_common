#!/usr/bin/env python
import rospy

from hero_common.msg import Motor


class MotorDemo(object):
    """ docstring for Motor Teleop """

    def __init__(self):
        rospy.init_node('motor_teleop_demo', anonymous=False)
        self.pub = rospy.Publisher('/hero_5/motor', Motor, queue_size=1)

    def run(self):
        rate = rospy.Rate()
        rospy.loginfo("[Blink Demo]: Running!")
        color = ColorRGBA()
        B = [0.6, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8,0.6]
        i = 0
        while not rospy.is_shutdown():
            c = list(np.random.choice(range(256), size=3))
            color.r = c[0]/256.0
            color.g = c[1]/256.0
            color.b = c[2]/256.0
            color.a = 1.0
            # color.r = 0
            # color.g = 0
            # color.b = 0.8
            # color.a = B[i % (len(B))]
            i += 1            

            self.pub.publish(color)
            
            # wait till 10 hz
            rate.sleep()


# Main function
if __name__ == '__main__':
    try:
        mt = MotorDemo()
        mt.run()
    except rospy.ROSInterruptException:
        rospy.loginfo("[Motor Demo]: Closed!")
