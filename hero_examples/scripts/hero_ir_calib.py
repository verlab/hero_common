#!/usr/bin/env python3
"""
This code implements a calibration method for the infrared sensors on the robot. 
The process consists of finding a gain parameter that adjusts the signal model of the sensor to find its distance in meters. 
The reflected signal intensity measured with a sensor is modeled by:

    s(d, \gamma) = \frac{\alpha}{d^2} \cos(\gamma) + \beta,

where $s(d, \gamma)$ is the output value of the sensor, $d$ is the distance to the object, and $\gamma$ is the angle of incidence with the surface; 
the model variable $\alpha$ includes several parameters such as the reflectivity coefficient, output power of the emitted IR light and the sensitivity 
of the sensor and it is estimated empirically; $\beta$ is the offset value of the amplifier and ambient light effect and it is measured regularly after 
performing the Equation~\ref{eq:infrared}. 

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
import numpy as np

from sensor_msgs.msg import LaserScan
from hero_common.srv import SetIRCalibration

class IRCalib(object):
    """ This code calibrate the IR sensor of the robot."""

    def __init__(self):
        rospy.init_node('ir_calibration', anonymous=True)
        self.intensities = []
        self.max_samples = 100
        self.robot_diameter = 0.07367
        self.distance = 0.10
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

        rospy.Subscriber(self.namespace+"laser", LaserScan, self.laser_cb)
        rospy.wait_for_service(self.namespace+"ir_calibration")
        self.calib_service = rospy.ServiceProxy(self.namespace+"ir_calibration", SetIRCalibration)

    def laser_cb(self, msg):
        if len(msg.intensities) == 16: # using interpolation
            self.intensities.append(msg.intensities[::2])
        else:
            self.intensities.append(msg.intensities)

    def alpha(self, intensity, d):
        return intensity * d * d

    def run(self):
        rate = rospy.Rate(30)
        rospy.loginfo("[IR Calibration]: Starting calibration! Wait...")
        while not rospy.is_shutdown():
            if len(self.intensities) < self.max_samples:
                rospy.loginfo_throttle(1, "Taking samples {} of {}. Wait...".format(len(self.intensities), self.max_samples))
                rate.sleep()
                continue

            mean_intensities = self.intensities
            mean_intensities = np.array(mean_intensities)
            std_intensities = mean_intensities.std(axis=0)
            mean_intensities = mean_intensities.mean(axis=0)
            rospy.loginfo("Mean Intensities:")
            rospy.loginfo(mean_intensities.round(2))
            rospy.loginfo("Std Intensities:")
            rospy.loginfo(std_intensities.round(2))
            alphas = self.alpha(mean_intensities, [self.distance]*8)
            rospy.loginfo("\33[92mAlpha parameter:\33[92m")
            rospy.loginfo("\33[92m{}\33[0m".format(alphas.round(2)))
            try:
                rospy.loginfo("[IR Calibration]: Recording calibration to robot {}".format(self.namespace))
                resp = self.calib_service(alphas[0], alphas[1], alphas[2], alphas[3], alphas[4], alphas[5], alphas[6], alphas[7])
                rospy.loginfo("[IR Calibration]: Calibration has been successfully recorded!")
            except rospy.ServiceException as exc:
                rospy.logwarn("[IR Calibration]: Service did not process request " + str(exc))

            rate.sleep()
            rospy.loginfo("[IR Calibration]: Finished!")
            break


# Main function
if __name__ == '__main__':
    try:
        cal = IRCalib()
        cal.run()
    except rospy.ROSInterruptException:
        rospy.loginfo("[IR Calibration]: Finnished!")
