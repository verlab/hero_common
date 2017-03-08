#!/usr/bin/env python

#################################################################
#               S W A R M   D R I V E R
#################################################################
# Paulo Rezeck <rezeck@dcc.ufmg.br>
# Hector Azpurua <hectorxxx@gmail.com>
# 02 Oct 2017
# Project Swarm
# Computer Vision and Robotics Lab - VERLAB
# Federal University of Minas Gerais UFMG - Brazil
#################################################################
import roslib; roslib.load_manifest('swarm_driver')

import rospy
from swarm_driver.msg import Command
from geometry_msgs.msg import Twist
from std_msgs.msg import UInt8


class Robot(object):
	def __init__(self, robot_id):
		self.robot_id = robot_id
		# Subscribe to Command Velocity Topic
		rospy.Subscriber('/robot_' + str(self.robot_id) + '/cmd_vel', Twist, self.handler_velocity)
		# Publisher the low-level commands to robots
		self.swarm_commands = rospy.Publisher('/swarm/command', Command, queue_size=1)
		# Wheel Radio (cm)
		self.wheel_diameter = 4
		# Separation between wheels (cm)
		self.wheel_separtion = 5.3
		# Max linear speed
		self.max_linear = self.wheel_diameter
		# Max angular speed
		self.max_angular = 2 * self.wheel_diameter/self.wheel_separtion

	def handler_velocity(self, data):
		"""
		Controls the velocity of each wheel based on linear and angular velocities.
		:param data:
		|linear| < max_linear
		|angular| < max_angular
		"""
		linear = max(min(data.linear.x, self.max_linear), -self.max_linear)
		angular = max(min(data.angular.z, self.max_angular), -self.max_angular)
		
		# Kinematic model for differential robot.
		wl = (linear - (self.wheel_separtion / 2.) * angular) / self.wheel_diameter
		wr = (linear + (self.wheel_separtion / 2.) * angular) / self.wheel_diameter
		# Command publish to control the robot
		cmd = Command()
		cmd.robot_id = self.robot_id
		cmd.wheel_right = (wr + 1) * 98
		cmd.wheel_left = (wl + 1) * 98
		# Publishing 
		self.swarm_commands.publish(cmd)


class SwarmDriver(object):
	def __init__(self):
		# list of all robots findable in enviroment
		self.robot_ids = [11, 12, 13]
		self.robots = []
		for _id in self.robot_ids:
			self.robots.append(Robot(_id))

	def run(self):
		print "[Status] Running :", self.robot_ids
		while not rospy.is_shutdown():
			pass


def run():
	rospy.init_node("swarm_driver", anonymous=True)
	SwarmDriver().run()


if __name__ == "__main__":
	run()