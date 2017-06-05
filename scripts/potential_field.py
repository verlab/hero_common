#!/usr/bin/env python
# Controller to navigate the robot

import rospy
import math
import tf
from ar_track_alvar_msgs.msg import AlvarMarkers
from swarm_driver.msg import Proximity
from geometry_msgs.msg import Twist

poseMsg = None
goalMsg = None
proximityMsg = None
angles = [-math.pi/4.0, 0, math.pi/4.0]


threshold = 0.15

def MarkersCallback(markers):
	global poseMsg
	global goalMsg

	for marker in markers.markers:
		if marker.id == 2:
			poseMsg = marker.pose

		if marker.id == 6:
			goalMsg = marker.pose

def ProximityCallback(proximity):
	global proximityMsg
	proximityMsg = [proximity.proximity_1, proximity.proximity_2, proximity.proximity_3]



def run():
	rospy.init_node('tracker', anonymous=True)

	pub = rospy.Publisher('/hero_2/cmd_vel', Twist, queue_size=10)

	rospy.Subscriber("/ar_pose_marker", AlvarMarkers, MarkersCallback)
	rospy.Subscriber("/hero_2/proximity", Proximity, ProximityCallback)

	rate = rospy.Rate(4) # 50hz

	global poseMsg
	global goalMsg

	cmd_vel = Twist()

	while not rospy.is_shutdown():
		if goalMsg == None:
			print 'goal none...', goalMsg
			rate.sleep()
			continue

		w = (poseMsg.pose.orientation.x, poseMsg.pose.orientation.y,
			 poseMsg.pose.orientation.z, poseMsg.pose.orientation.w)
		euler = tf.transformations.euler_from_quaternion(w)
		yaw = euler[2]

		dx = goalMsg.pose.position.x - poseMsg.pose.position.x
		dy = goalMsg.pose.position.y - poseMsg.pose.position.y
		d = math.sqrt(dx ** 2 + dy ** 2)
		theta = math.atan2(dy, dx)
		fatt_x = -20.0 * math.cos(theta) * d
		fatt_y = -20.0 * math.sin(theta) * d
		
		frep_x = 0.0
		frep_y = 0.0
		p0 = 100
		for i in range(len(proximityMsg)):
			pq = proximityMsg[i]	
			if pq <= p0:
				repx = 10**7 * (1.0/pq - 1.0/p0) * math.cos(angles[i]+yaw+math.pi)/(pq**2)
				repy = 10**7 * (1.0/pq - 1.0/p0) * math.sin(angles[i]+yaw+math.pi)/(pq**2)
				frep_x += repx
				frep_y += repy
		print fatt_x, fatt_y, frep_x, frep_y
		fx = fatt_x - frep_x
		fy = fatt_y - frep_y
		f = math.sqrt(fx**2 + fy**2)
		sigma = math.atan2(fy, fx) - yaw
		print "sigma1:", sigma
		if sigma > math.pi:
			sigma = sigma - 2.0 * math.pi
		if sigma < -math.pi:
			sigma = sigma + 2.0 * math.pi

		if abs(d) <= threshold:
			cmd_vel.linear.x = 0.0
			cmd_vel.angular.z = 0.0;
		else:
			cmd_vel.linear.x = min(0.8, f)
			print "sigma2:", sigma/(2*math.pi)
			sigma = min(max(sigma/(2*math.pi), (-0.1)), (0.1));
			cmd_vel.angular.z = sigma;
		

		# if abs(ang) <= threshold:
		# 	cmd_vel.angular.z = 0.0
		# else:
		# 	if ang > math.pi:
		# 		ang -= 2*math.pi

		# 	if ang < -math.pi:
		# 		ang += 2*math.pi

		# 	cmd_vel.angular.z = ang * 0.1

		# if abs(d) <= threshold:
		# 	cmd_x = 0.0
		# else:
		# 	cmd_x = d * 4

		# 	if cmd_x > 1.6:
		# 		cmd_x = 1.6

		# 	if cmd_x < 0.9:
		# 		cmd_x = 0.9

			
		#cmd_vel.linear.x = cmd_x
		#print '\npose.x={}'.format(poseMsg.pose.position.x)
		#print 'pose.y={}'.format(poseMsg.pose.position.y)

		#print 'z={}\n'.format(ang)
		#print 'zcmd={}'.format(cmd_vel.angular.z)

		pub.publish(cmd_vel)
		rate.sleep()


if __name__ == '__main__':
	try:
		run()
	except rospy.ROSInterruptException:
		pass

