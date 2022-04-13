#!/usr/bin/env python


import rospy
from std_msgs.msg import Header
from std_msgs.msg import Float64

import numpy as np

current_msg = None
stamp = None

def callback(data):
	global current_msg, stamp
	current_msg = data
	stamp = rospy.Time.now()
	# rospy.loginfo("Getting message.")

def run():
	global current_msg, stamp

	rospy.init_node('delay_measure', anonymous=False)

	rospy.Subscriber("esp2pc", Header, callback)
	pub = rospy.Publisher('pc2esp', Header, queue_size=1)
	pub_delay = rospy.Publisher('delay', Float64, queue_size=1)
	rate = rospy.Rate(1000) # 10hz

	rospy.loginfo("Starting...")

	header = Header()
	header.seq = -1

	sending = False

	max_delay = 0
	min_delay = 100
	sum_delay = 0
	count_msgs = 0

	rate.sleep()

	while not rospy.is_shutdown():
		if not sending:
			# rospy.loginfo("Sending message...")
			header.seq += 1
			header.stamp = rospy.Time.now()
			pub.publish(header)
			sending = True

		if current_msg:
			if current_msg.seq == header.seq:
				delay = (stamp - current_msg.stamp).to_sec()
				# if delay > max_delay:
				# 	max_delay = delay
				# if delay < min_delay:
				# 	min_delay = delay
				# sum_delay += float(delay)
				# count_msgs += 1.0
				# rospy.loginfo("Delay: (delay: {}, avg: {}, min: {}, max: {}) secs".format(delay, sum_delay/count_msgs, min_delay, max_delay))
				pub_delay.publish(delay)
				sending = False

		rate.sleep()


# Main function
if __name__ == '__main__':
	try:
		run()
	except rospy.ROSInterruptException:
		rospy.loginfo("Closed!")
