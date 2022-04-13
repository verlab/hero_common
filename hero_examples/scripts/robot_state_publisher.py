#!/usr/bin/env python
# The follow script takes the robot:
#   - odometry
#   - laser
#   - object target
#  reading and publish a markovian state of the robot, assuming modeling as POMDP.

import rospy
import math
import numpy as np
import tf
import sys

from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import Pose2D
from std_msgs.msg import ColorRGBA
from sensor_msgs.msg import Image
from gazebo_msgs.msg import ModelStates

from cv_bridge import CvBridge
import cv2

class RobotState(object):
    def __init__(self):
        self.odom = None
        self.laser = None
        self.target = Pose2D()
        self.object = None

        rospy.init_node("robot_markov_state_publisher", anonymous=False)
        self.namespace = str(sys.argv[1])

        self.laser_topic = self.namespace + "/laser" 
        rospy.Subscriber(self.laser_topic, LaserScan, self.laser_cb)
        
        self.odom_topic = self.namespace + "/odom" 
        rospy.Subscriber(self.odom_topic, Odometry, self.odom_cb)
        
        self.target_topic = self.namespace + "/target" 
        rospy.Subscriber(self.target_topic, Pose2D, self.target_cb)

        self.object_topic = "/gazebo/model_states"
        rospy.Subscriber(self.object_topic, ModelStates, self.object_cb)
        self.target_name = rospy.get_param("target_name", "box")
        
        self.state_topic = self.namespace + "/markov_state" 
        self.pub = rospy.Publisher(self.state_topic, Image, queue_size=1)

        self.height = rospy.get_param("height", 100)
        self.width =  rospy.get_param("width", 100)
        rospy.loginfo("[{}] State frame height: {}".format(self.namespace, self.height))
        rospy.loginfo("[{}] State frame width: {}".format(self.namespace, self.width))

        self.reference = rospy.get_param("reference", "global")
        rospy.loginfo("[{}] State reference: {}".format(self.namespace, self.reference))
        self.kernel = rospy.get_param("kernel", 2)
        rospy.loginfo("[{}] State dilate kernel: {}".format(self.namespace, self.kernel))
        self.has_obstacle = rospy.get_param("has_obstacle", True)
        rospy.loginfo("[{}] State assume obstacles: {}".format(self.namespace, self.has_obstacle))

        self.bridge = CvBridge()

        rospy.logwarn_once("[{}] Waiting readings...".format(self.namespace))


    def object_cb(self, msg):
        rospy.loginfo_once("[{}] Subscribing to gazebo model topic: {}".format(self.namespace, self.object_topic))
        idx = msg.name.index(self.target_name)
        self.object = msg.pose[idx]

    
    def odom_cb(self, msg):
        rospy.loginfo_once("[{}] Subscribing to odom topic: {}".format(self.namespace, self.odom_topic))
        self.odom = msg

    def drawObjectLocation(self, image, object, robot, max_range):
        dx = (object[0] - robot[0])
        dy = -(object[1] - robot[1])
        d = np.sqrt(dx * dx + dy * dy)
        fade = 0
        if d < 4:
            dx = int(0.98 * max(min(dx, max_range), -max_range) *  self.width  * 0.5 / max_range + self.width * 0.5)
            dy = int(0.98 * max(min(dy, max_range), -max_range) *  self.height * 0.5 / max_range + self.height * 0.5)
            fade = (1.0 - d * 0.25)  * 255
            image = cv2.rectangle(image, (dx-1, dy-1), (dx+1, dy+1), (fade, 0, 0), -1)
        return image

    def drawLaser(self, image, ranges, intensities, angle_min, angle_increment, max_range, robot, object):
        dx = (object[0] - robot[0])
        dy = -(object[1] - robot[1])
        d = np.sqrt(dx * dx + dy * dy)
        fade = (1.0 - d * 0.25)  * 255
        object_detected = False

        for i in range(len(ranges)):                   
            if ranges[i] >max_range:
                continue

            if self.reference == "local":
                theta = i * angle_increment + angle_min
            else:
                theta = i * angle_increment + angle_min + robot[2]

            px = -0.98 * ranges[i] * np.sin(theta) *  self.width   * 0.5 / max_range + self.width  * 0.5
            py =  0.98 * ranges[i] * np.cos(theta) *  self.height * 0.5 / max_range + self.height * 0.5

            if intensities[i] == 1.0: # objects
                image[int(px)][int(py)][0] = fade
                image[int(px)][int(py)][1] = 0
                image[int(px)][int(py)][2] = 0
                object_detected = True
            elif self.has_obstacle: # obstacles
                image[int(px)][int(py)][0] = 0
                image[int(px)][int(py)][1] = 0
                image[int(px)][int(py)][2] = 255                        
            
        image = cv2.erode(image, np.ones((self.kernel, self.kernel), np.uint8), iterations=1)
        return image, object_detected


    def drawTarget(self, image, max_range, robot, target):
        dx =  (target[0] - robot[0])
        dy = -(target[1] - robot[1])
        dx = int(0.98 * max(min(dx, max_range), -max_range) *  self.width  * 0.5 / max_range + self.width  * 0.5)
        dy = int(0.98 * max(min(dy, max_range), -max_range) *  self.height * 0.5 / max_range + self.height * 0.5)
        image = cv2.rectangle(image, (dx-1, dy-1), (dx+1, dy+1), (0,255,0), -1)
        return image


    def laser_cb(self, msg):
        rospy.loginfo_once("[{}] Subscribing to laser topic: {}".format(self.namespace, self.laser_topic))
        self.laser = msg
        if self.odom is None:
            return

        image = np.ones((self.height, self.width, 3), np.uint8) * 255

        if self.laser is not None:
            # Get robot rpy orientation
            w = (self.odom.pose.pose.orientation.x, self.odom.pose.pose.orientation.y,
                self.odom.pose.pose.orientation.z, self.odom.pose.pose.orientation.w)
            _, _, yaw = tf.transformations.euler_from_quaternion(w)
            image, object_detected = self.drawLaser(image, self.laser.ranges, self.laser.intensities, self.laser.angle_min, self.laser.angle_increment, self.laser.range_max,  [self.odom.pose.pose.position.x, self.odom.pose.pose.position.y, yaw], [self.object.position.x, self.object.position.y] )

        if self.object is not None and not object_detected:
            image = self.drawObjectLocation(image, [self.object.position.x, self.object.position.y], [self.odom.pose.pose.position.x, self.odom.pose.pose.position.y], self.laser.range_max)


        if self.target is not None:
            image = self.drawTarget(image,  self.laser.range_max, [self.odom.pose.pose.position.x, self.odom.pose.pose.position.y], [self.target.x, self.target.y])

        if image is not None:
            self.pub.publish(self.bridge.cv2_to_imgmsg(image, encoding='bgr8'))
            rospy.loginfo_once("[{}] Publishing to robot state topic: {}".format(self.namespace, self.state_topic))


    def target_cb(self, msg):
        rospy.loginfo("[{}] Subscribing to target topic: {}".format(self.namespace, self.target_topic))
        self.target = msg

    def process(self):
        rospy.spin()


# Main function
if __name__ == '__main__':
    try:
        handle_ = RobotState()
        handle_.process()
    except rospy.ROSInterruptException:
        rospy.loginfo("[{}] Robot state publisher is closed!".format(handle_.namespace))
