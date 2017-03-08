#!/usr/bin/env python

#################################################################
#               S W A R M   D R I V E R
#################################################################
# Paulo Rezeck <rezeck@dcc.ufmg.br>
# Hector Azpurua <hectorxxx@gmail.com>
# 02 Oct 2017
# Project Swarm
# Computer Vision and Robotics Lab - VERLAB
# Federal University of Minas Gerais - Brazil
#################################################################

import rospy
from swarm_driver.msg import Command
from std_msgs.msg import UInt8

## Robot dimensions
# Wheel Radio (cm)
WHEEL_DIAMETER = 4

# Separation between wheels (cm)
WHEEL_SEPARATION = 5.3

class SwarmDriver(object):
	def __init__(self):
		# list of all robots findable in enviroment (automatic harvest)
		self.robots = []
		pass

	def run(self):
		pass

	def handler_velocity(self, data):
		"""
		Controls the velocity of each wheel based on linear and angular velocities.
		:param data:
		"""
		linear = data.linear.x
		angular = data.angular.z
		# Kinematic model for differential robot.
		wl = (linear - (WHEEL_SEPARATION / 2.) * angular) / WHEEL_DIAMETER
		wr = (linear + (WHEEL_SEPARATION / 2.) * angular) / WHEEL_DIAMETER
		# At input 1000, angular velocity is 1 cycle / s or  2*pi/s.
		left_vel = wl * 1000.
		right_vel = wr * 1000.
		self._bridge.set_motors_speed(left_vel, right_vel)

def run():
	rospy.init_node("swarm_driver", anonymous=True)
	SwarmDriver().run()


if __name__ == "__main__":
	run()