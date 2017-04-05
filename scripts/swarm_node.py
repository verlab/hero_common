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
from swarm_driver.msg import Command, Sensors
from geometry_msgs.msg import Twist
from std_msgs.msg import UInt8

import numpy as np

class Robot(object):
	def __init__(self, robot_id):
		self.robot_id = robot_id
		# Subscribe to Command Velocity Topic
		#rospy.Subscriber('/robot_' + str(self.robot_id) + '/cmd_vel', Twist, self.handler_velocity)
		rospy.Subscriber('/cmd_vel', Twist, self.handler_velocity)

		# Publisher the Sensors states
		self.pub_sensors = rospy.Publisher('/robot_' + str(self.robot_id) + '/sensor', Sensors, queue_size=10)
		# Sensors state
		self.sense = Sensors()
		self.sense.robot_id = self.robot_id
		# Publisher the low-level commands to robots
		self.pub_commands = rospy.Publisher('/swarm/command', Command, queue_size=10)
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
		self.pub_commands.publish(cmd)

	def pub_sensors(self, sense):
		self.sense.data = sense.data
		self.pub_sensors.publish(self.sense)


class SwarmDriver(object):
	def __init__(self):
		# Instanciated a list of all robots enable in enviroment
		self.robots = []
		# Subscribe to swarm ID topic
		rospy.Subscriber('/swarm/id', UInt8, self.search_robots)
		rospy.Subscriber('/swarm/sensor', Sensors, self.update_sensors)
		self.pub_request = rospy.Publisher('/swarm/request', UInt8, queue_size=1)

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

	# Read the sensors data come from pipe and make the respective robot publish it
	def update_sensors(self, data):
		for i in range(len(self.robots)):
			if data.robot_id == self.robots[i].robot_id:
				self.robots[i].pub_sensors.publish(data)

	# Print all robots enable that was found in environment
	def list_all_robots(self):
		for robot in self.robots:
			print '\x1b[6;30;43m', '[Status]: Robot', robot.robot_id, 'is enable.', '\x1b[0m'

	def request_sensors(self):
		for robot in self.robots:
			self.pub_request.publish(np.uint8(robot.robot_id))

	def run(self):
		print '\x1b[6;30;43m', '[Status]: Swarm Manager is working! Please turn on the robots...', '\x1b[0m'
		rate = rospy.Rate(2) # 5hz
		while not rospy.is_shutdown():
			self.request_sensors()
			rate.sleep()



def run():
	rospy.init_node("swarm_driver", anonymous=True)
	SwarmDriver().run()


if __name__ == "__main__":
	run()