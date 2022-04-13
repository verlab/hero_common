#!/usr/bin/env python
import rospy

from std_msgs.msg import ColorRGBA
from geometry_msgs.msg import Twist
import time


class HeroDemo(object):
    """ docstring for HeRo demo """

    def __init__(self):
        rospy.init_node('hero_demo', anonymous=False)
        topics = [topic[0] for topic in rospy.get_published_topics("/")]
        robots = []
        for topic in topics:
            if "odom" in topic:
                robots.append(topic.split("/")[1])

        rospy.loginfo("Founded robots:")
        for robot in robots:
            rospy.loginfo(">> " + robot)
        self.pubs = []
        for robot in robots:
            pub_cmd = rospy.Publisher(
                '/'+robot+"/velocity_controller/cmd_vel", Twist, queue_size=1)
            pub_color = rospy.Publisher(
                '/'+robot+"/led", ColorRGBA, queue_size=1)
            self.pubs.append([pub_cmd, pub_color])

    def run(self):
        rate = rospy.Rate(5)
        rospy.loginfo("[HeRo Demo]: Running!")
        color = ColorRGBA()
        color.r = 1.0
        color.a = 1.0

        vel = Twist()

        timer = 0

        vx = 0.15
        vz = -4.0
        t_f = 2.2
        t_t = 0.99
        actions = [[0.0, 0.0,1,0,0,0,1], [vx,0.0,t_f,0,1,1,1], [0.0, 0.0,1,0,0,0,1], [0.0,vz,t_t,1,0,1,1], [0.0, 0.0,1,0,0,0,1], [vx,0.0,t_f,1,0,0,1], [0.0, 0.0,1,0,0,0,1], [0.0,vz,t_t,0,1,0,1], [0.0, 0.0,1,0,0,0,1], [vx,0.0,t_f,0,1,0,1], [0.0, 0.0,1,0,0,0,1], [0.0,vz,t_t,1,1,0,1], [0.0, 0.0,1,0,0,0,1], [vx,0.0,t_f,1,0,0,1],[0.0, 0.0,1,0,0,0,1], [0.0,vz,t_t,1,1,1,1]]
        actions = actions[0:2]
        cur_action = 0

        while not rospy.is_shutdown():
            vx, vz, t, r, g, b, a = actions[cur_action]
            vel.linear.x = vx
            vel.angular.z = vz
            color.r = r
            color.g = g
            color.b = b
            color.a = a
            if (time.time() - timer) > t:
                rospy.loginfo("[HeRo Demo]: Running step "+str(cur_action))
                # vx, vz, r, g, b, a = actions[cur_action]
                # vel.linear.x = vx
                # vel.angular.z = vz
                # color.r = r
                # color.g = g
                # color.b = b
                # color.a = a
                timer = time.time()
                cur_action = (1+cur_action) % len(actions)
            for pub_cmd, pub_color in self.pubs:
                pub_cmd.publish(vel)
                pub_color.publish(color)
            # wait till 10 hz
            rate.sleep()


# Main function
if __name__ == '__main__':
    try:
        demo = HeroDemo()
        demo.run()
    except rospy.ROSInterruptException:
        rospy.loginfo("[HeRo Demo]: Closed!")
