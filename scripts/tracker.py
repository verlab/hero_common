#!/usr/bin/env python
# Controller to navigate the robot

import rospy
import math
import tf
from ar_track_alvar_msgs.msg import AlvarMarkers
from geometry_msgs.msg import Twist

poseMsg = None
goalMsg = None

threshold = 0.15

def MarkersCallback(markers):
	global poseMsg
	global goalMsg

	for marker in markers.markers:
		if marker.id == 2:
			poseMsg = marker.pose

		if marker.id == 6:
			goalMsg = marker.pose


def run():
	rospy.init_node('tracker', anonymous=True)

	pub = rospy.Publisher('/hero_2/cmd_vel', Twist, queue_size=10)

	rospy.Subscriber("/ar_pose_marker", AlvarMarkers, MarkersCallback)

	rate = rospy.Rate(2) # 50hz

	global poseMsg
	global goalMsg

	cmd_vel = Twist()

	while not rospy.is_shutdown():
		if goalMsg == None:
			print 'goal none...', goalMsg
			rate.sleep()
			continue

		dx = goalMsg.pose.position.x - poseMsg.pose.position.x
		dy = goalMsg.pose.position.y - poseMsg.pose.position.y

		theta = math.atan2(dy, dx)
		d = math.sqrt(dx ** 2 + dy ** 2)

		print 'dx={} dy={} d={} theta={}'.format(dx, dy, d, theta)
		
		w = (poseMsg.pose.orientation.x, poseMsg.pose.orientation.y,
			 poseMsg.pose.orientation.z, poseMsg.pose.orientation.w)
		euler = tf.transformations.euler_from_quaternion(w)
		yaw = euler[2]

		ang = (yaw - theta)

		if abs(ang) <= threshold:
			cmd_vel.angular.z = 0.0
		else:
			if ang > math.pi:
				ang -= 2*math.pi

			if ang < -math.pi:
				ang += 2*math.pi

			cmd_vel.angular.z = ang * 0.1

		if abs(d) <= threshold:
			cmd_x = 0.0
		else:
			cmd_x = d * 4
			
			if cmd_x > 1.6:
				cmd_x = 1.6

			if cmd_x < 0.9:
				cmd_x = 0.9

			
		cmd_vel.linear.x = cmd_x
		print '\npose.x={}'.format(poseMsg.pose.position.x)
		print 'pose.y={}'.format(poseMsg.pose.position.y)
		
		print 'z={}\n'.format(ang)
		print 'zcmd={}'.format(cmd_vel.angular.z)

		#cmd_vel.linear.x = 0.5 * (1 - abs(ang)/2*math.pi)
		pub.publish(cmd_vel)
		rate.sleep()


if __name__ == '__main__':
	try:
		run()
	except rospy.ROSInterruptException:
		pass

