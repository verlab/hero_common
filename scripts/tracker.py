#!/usr/bin/env python
# Controller to navigate the robot

import rospy
import math
import tf
from ar_track_alvar_msgs.msg import AlvarMarkers
from geometry_msgs.msg import Twist

poseMsg = None
goalMsg = None

threshold = 0.025

def MarkersCallback(markers):
	global poseMsg
	for marker in markers:
		if marker.id == 2:
			poseMsg = marker.pose


def GoalCallback(goal):
	global goalMsg
	for marker in markers:
		if marker.id == 6:
			goalMsg = marker.pose


def run():
	rospy.init_node('/tracker', anonymous=True)

	pub = rospy.Publisher('/hero_2/cmd_vel', Twist, queue_size=10)

	rospy.Subscriber("/ar_pose_marker", AlvarMarkers, MarkersCallback)

	rate = rospy.Rate(50) # 50hz

	global odomMsg
	global goalMsg

	cmd_vel = Twist()

	while not rospy.is_shutdown():
		if goalMsg == None:
			rate.sleep()
			continue

		dx = goalMsg.pose.position.x - odomMsg.pose.position.x
		dy = goalMsg.pose.position.y - odomMsg.pose.position.y

		if abs(dx) <= threshold and abs(dy) <= threshold:
			cmd_vel.linear.x = 0.0
			cmd_vel.angular.z = 0.0
			pub.publish(cmd_vel)
			rate.sleep()
			continue

		theta = math.atan2(dy, dx)
		w = (odomMsg.pose.orientation.x, odomMsg.pose.orientation.y,
			 odomMsg.pose.orientation.z, odomMsg.pose.orientation.w)
		euler = tf.transformations.euler_from_quaternion(w)
		yaw = euler[2]
		ang = (theta - yaw)

		if ang > math.pi:
			ang -= 2*math.pi

		if ang < -math.pi:
			ang -= 2*math.pi

		cmd_vel.angular.z = ang
		cmd_vel.linear.x = 1.4
		cmd_vel.linear.x = 0.5 * (1 - abs(ang)/2*math.pi)
		pub.publish(cmd_vel)
		rate.sleep()


if __name__ == '__main__':
	try:
		run()
	except rospy.ROSInterruptException:
		pass

