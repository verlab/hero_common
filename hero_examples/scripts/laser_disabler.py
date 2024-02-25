#!/usr/bin/env python3

import rospy
from std_msgs.msg import Bool

def main():
    rospy.init_node('laser_disabler')

    rate = rospy.Rate(0.1)  # 0.1 Hz

    publishers = {}

    while not rospy.is_shutdown():
        # Get the list of topics
        topics = rospy.get_published_topics()

        # Iterate through topics to find those with the prefix /hero_$ID
        for topic, msg_type in topics:
            if topic.startswith('/hero_'):
                hero_id = topic.split('/')[1].replace("hero_", "")
                laser_topic = '/hero_{}/laser_enable'.format(hero_id)
                if laser_topic in publishers:
                    publishers[laser_topic].publish(Bool(False))
                else:
                    rospy.loginfo("Found Hero {}".format(hero_id))
                    publishers[laser_topic] = rospy.Publisher(laser_topic, Bool, queue_size=1)
        rate.sleep()

if __name__ == '__main__':
    main()
