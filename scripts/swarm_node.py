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

import numpy as np

class Robot(object):
	def __init__(self, robot_id):
		self.robot_id = robot_id
		# Subscribe to Command Velocity Topic
		rospy.Subscriber('/robot_' + str(self.robot_id) + '/cmd_vel', Twist, self.handler_velocity)
		# Publisher the low-level commands to robots
		self.swarm_commands = rospy.Publisher('/swarm/command', Command, queue_size=1)
		# Wheel Radio (cm)
		self.wheel_diameter = 6.64
		# Separation between wheels (cm)
		self.wheel_separtion = 6.6
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
		wr = max(-0.5, min(wr, 0.5))
		wl = max(-0.5, min(wl, 0.5))
		# Command publish to control the robot
		cmd = Command()
		cmd.robot_id = self.robot_id
		cmd.wheel_right = np.int8((-wr) * 255)
		cmd.wheel_left = np.int8((wl) * 255)
		# Publishing 
		self.swarm_commands.publish(cmd)


class SwarmDriver(object):
	def __init__(self):
		# Instanciated a list of all robots enable in enviroment
		self.robots = []
		# Subscribe to swarm ID topic
		rospy.Subscriber('/swarm/id', UInt8, self.search_robots)


	# Check if the robot was instanciated before
	def was_this_robot_enable(self, _id):
		for robot in self.robots:
			if robot.robot_id == _id:
				return True
		return False

	# Read the topic /swarm/id to find new enable robots
	def search_robots(self, data):
		if not self.was_this_robot_enable(data.data):
			print '\x1b[6;30;42m', '[Status] System has found Robot', data.data, '\x1b[0m'
			self.robots.append(Robot(data.data))

	def list_all_robots(self):
		for robot in self.robots:
			print '\x1b[6;30;41m', '[Status]: Robot', robot.robot_id, 'is enable.', '\x1b[0m'

	def run(self):
		self.list_all_robots()
		while not rospy.is_shutdown():
			pass


def run():
	rospy.init_node("swarm_driver", anonymous=True)
	SwarmDriver().run()


if __name__ == "__main__":
	run()