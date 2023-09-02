#!/usr/bin/env python3
"""
This code implements a calibration method that consists of find the PWM value that turns the
velocity of the wheel to zero. Ideally, this value should be 1500 us, but it will dependes on 
the resistors used as voltage divider. Than, it is required to calibrate this value to get better
results on the velocity controller of the robot.

For more details, check out our paper: HeRo 2.0: A Low-Cost Robot for Swarm Robotics Research.
"""

__author__ = "Paulo Rezeck"
__copyright__ = "Copyright 2023, HeRo Project"
__license__ = "Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License"
__version__ = "0.8.0"
__maintainer__ = "Paulo Rezeck"
__email__ = "rezeck@dcc.ufmg.br"


import rospy
import sys

from hero_common.msg import Motor, Encoder

class MotorPWMCalib:
    def __init__(self):
        # Initialize the ROS node
        rospy.init_node('motor_pwm_calib_node', anonymous=True)

        if len(sys.argv) < 2:
            self.namespace = "/hero_0/"
            rospy.loginfo("Could not find any robot namespace!")
            rospy.loginfo("Setting default namespace: {}".format(self.namespace))
        else:
            self.namespace = str(sys.argv[1])
            if self.namespace[0] != '/':
                self.namespace = '/' + self.namespace
            if self.namespace[-1] != '/':
                self.namespace = self.namespace + '/'
            rospy.loginfo("Setting robot namespace: {}".format(self.namespace))

        # Subscribe to the "/hero_1/encoder" topic to get motor velocity
        rospy.Subscriber(f'{self.namespace}encoder', Encoder, self.encoder_callback)

        # Publisher for sending PWM commands to the motor
        self.motor_pwm_pub = rospy.Publisher(f'{self.namespace}cmd_motor', Motor, queue_size=1)

        # PWM range (1000-2000) for the motor commands
        self.pwm_min = 1000
        self.pwm_max = 2000

        self.current_left_velocity = 0.1
        self.current_right_velocity = 0.1

        self.left_motor_bound = [self.pwm_min, self.pwm_max]
        self.right_motor_bound = [self.pwm_min, self.pwm_max]

        self.left_motor_done = False
        self.right_motor_done = False

        # Maximum difference allowed to consider the velocity as close to 0.0 m/s
        self.velocity_threshold = 0.001

    def encoder_callback(self, msg):
        # Callback function for receiving motor velocity updates
        self.current_left_velocity = msg.left_speed_filtered
        self.current_right_velocity = msg.right_speed_filtered

        # # Calculate the PWM command to force the velocity to 0.0 m/s
        # pwm_command_left = self.binary_search_pwm(current_left_velocity)
        # pwm_command_right = self.binary_search_pwm(current_right_velocity)

        # # Publish the calculated PWM command
        # pwm_command = Motor()
        # pwm_command.left_motor_pwm = pwm_command_left
        # pwm_command.right_motor_pwm = pwm_command_right
        # self.motor_pwm_pub.publish(pwm_command)

    def binary_search_pwm(self, current_velocity):
        # Binary search to find the PWM command that results in zero velocity

        # Define the initial boundaries for binary search
        lower_bound = self.pwm_min
        upper_bound = self.pwm_max

        while upper_bound - lower_bound > 1:
            # Calculate the midpoint PWM value
            mid = (lower_bound + upper_bound) // 2

            # Set the motor to the midpoint PWM value
            self.motor_pwm_pub.publish(mid)
            rospy.sleep(1.0)  # Allow some time for the motor to respond

            # Get the updated velocity after setting the motor PWM
            current_velocity = self.get_current_velocity()

            # If the velocity is within the threshold, stop the search
            if abs(current_velocity) <= self.velocity_threshold:
                return mid
            elif current_velocity > 0:
                # If the velocity is positive, adjust the upper bound
                upper_bound = mid
            else:
                # If the velocity is negative, adjust the lower bound
                lower_bound = mid

        # If the loop ends without finding the exact zero velocity, return the midpoint
        return (lower_bound + upper_bound) // 2
    
    def search(self, current_velocity, pwm_command, bound):
        # Binary search to find the PWM command that results in zero velocity

        # If the velocity is within the threshold, stop the search
        if abs(current_velocity) <= self.velocity_threshold:
            return bound, True
        elif current_velocity > 0:
            # If the velocity is positive, adjust the upper bound
            bound[1] = pwm_command
        else:
            # If the velocity is negative, adjust the lower bound
            bound[0] = pwm_command
        return bound, False

    def run(self):
        rospy.wait_for_message(f'{self.namespace}encoder', Encoder)
        # Start the ROS node and keep it running until shutdown
        self.rate = rospy.Rate(1)  # 20 hz

        while not rospy.is_shutdown():
            # Calculate the midpoint PWM value
            pwm_command_left = (self.left_motor_bound[0] + self.left_motor_bound[1]) // 2
            pwm_command_right = (self.right_motor_bound[0] + self.right_motor_bound[1]) // 2

            # Set the motor to the midpoint PWM value
            pwm_command = Motor()
            pwm_command.left_motor_pwm = pwm_command_left
            pwm_command.right_motor_pwm = pwm_command_right
            self.motor_pwm_pub.publish(pwm_command) 
            rospy.sleep(3.0)  # Allow some time for the motor to respond

            self.left_motor_bound, self.left_motor_done = self.search(self.current_left_velocity, pwm_command_left, self.left_motor_bound)
            self.right_motor_bound, self.right_motor_done = self.search(self.current_right_velocity, pwm_command_right, self.right_motor_bound)

            print(f"PWM: {pwm_command_left} Vel: {self.current_left_velocity} - Done? {self.left_motor_done}")
            print(f"PWM: {pwm_command_left} Vel: {self.current_left_velocity} - Done? {self.right_motor_done}")
            print()

            if self.left_motor_done and self.right_motor_bound:
                break

            self.rate.sleep()

if __name__ == '__main__':
    try:
        motor_pwm_calib = MotorPWMCalib()
        motor_pwm_calib.run()
    except rospy.ROSInterruptException:
        pass
