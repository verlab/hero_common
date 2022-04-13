#!/usr/bin/env python
# Potential field to navigate the robot

import rospy
import math
import numpy as np
import tf
import sys

from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import Pose2D
from apriltag_ros.msg import AprilTagDetectionArray
from tf.transformations import euler_from_quaternion, quaternion_from_euler, quaternion_multiply, quaternion_inverse
from geometry_msgs.msg import Quaternion

from std_msgs.msg import ColorRGBA


class Tag2Pose(object):
    def __init__(self):
        rospy.init_node("tag2pose", anonymous=True)
        self.namespace = str(sys.argv[1])
        self.id = int(self.namespace.split("_")[1])
        if self.id == 5:
            self.id = 10
        if self.id == 6:
            self.id = 11
        rospy.loginfo("[{}] Initializing...".format(self.namespace))

                
        self.pub = rospy.Publisher(self.namespace + "/pose", Odometry, queue_size=1)
        self.pub_ground = rospy.Publisher(self.namespace + "/ground_pose", Pose2D, queue_size=1)

        rospy.Subscriber("/tag_detections", AprilTagDetectionArray, self.tags_cb, queue_size=1)

        if "hero" in self.namespace and self.id < 5:
            rospy.Subscriber(self.namespace + "/odom", Odometry, self.odom_cb, queue_size=1)

        self.br = tf.TransformBroadcaster()
    
        self.once = True
        self.pose_ = Odometry()
        self.pose_.header.frame_id = "/world"
        self.pose_.child_frame_id = self.namespace + "/base_link"
        self.world_offset = [5,5]
        self.odom_state = [0.,0.,0.,0.,0.,0.,0.]
        self.last_odom = None
        self.tag_state = [0.,0.,0.,0.,0.,0.,0.]
        self.last_tag = None
        self.last_tag_stamp = None
        self.counter = 0
        self.ref_ = [0,0,0,0,0,0,0]
        self.firt_time_pub = True
    

    def odom_cb(self, msg):
        if self.last_odom is None:
            self.last_odom = msg
            rospy.loginfo("\33[92m[{}] Using robot odometry!\33[0m".format(self.namespace))
        else:
            dt = (msg.header.stamp - self.last_odom.header.stamp).to_nsec()/1.0e9 + 1e-10
            # rospy.loginfo_throttle(1, ">>>>> Odom dt: {}".format(dt))
            self.odom_state[0] = (msg.pose.pose.position.x - self.last_odom.pose.pose.position.x)/dt
            self.odom_state[1] = (msg.pose.pose.position.y - self.last_odom.pose.pose.position.y)/dt
            self.odom_state[2] = (msg.pose.pose.position.z - self.last_odom.pose.pose.position.z)/dt
            q1 = [self.last_odom.pose.pose.orientation.x, self.last_odom.pose.pose.orientation.y, self.last_odom.pose.pose.orientation.z, self.last_odom.pose.pose.orientation.w]
            q2 = [msg.pose.pose.orientation.x, msg.pose.pose.orientation.y, msg.pose.pose.orientation.z, msg.pose.pose.orientation.w]
            q1_inv = quaternion_inverse(q1)
            qdiff = quaternion_multiply(q2, q1_inv)
            self.odom_state[3] = qdiff[0]/dt
            self.odom_state[4] = qdiff[1]/dt
            self.odom_state[5] = qdiff[2]/dt
            self.odom_state[6] = qdiff[3]/dt
            # self.odom_state[3] = (msg.pose.pose.orientation.x - self.last_odom.pose.pose.orientation.x)/dt
            # self.odom_state[4] = (msg.pose.pose.orientation.y - self.last_odom.pose.pose.orientation.y)/dt
            # self.odom_state[5] = (msg.pose.pose.orientation.z - self.last_odom.pose.pose.orientation.z)/dt
            # self.odom_state[6] = (msg.pose.pose.orientation.w - self.last_odom.pose.pose.orientation.w)/dt
            self.last_odom = msg
            # print(self.odom_state)

    def normalize(self, q):
        dx2 = q.x*q.x
        dy2 = q.y*q.y
        dz2 = q.z*q.z
        dw2 = q.w*q.w
        norm = math.sqrt(dw2 + dz2 + dy2 + dx2) #+ 10e-9
        if abs(norm) < 1e-8:
            norm = 1
            q[3] = 1
        q.x /= norm
        q.y /= norm
        q.z /= norm
        q.w /= norm
        return q

    def normalizeA(self, q):
        dx2 = q[0]*q[0]
        dy2 = q[1]*q[1]
        dz2 = q[2]*q[2]
        dw2 = q[3]*q[3]
        norm = math.sqrt(dw2 + dz2 + dy2 + dx2) #+ 10e-9
        if abs(norm) < 1e-8:
            norm = 1
            q[3] = 1
        q[0] /= norm
        q[1] /= norm
        q[2] /= norm
        q[3] /= norm
        return q

    def tags_cb(self, msg):
        new_pose_ = None
        for tag in msg.detections:
            # filtering by height
            if tag.pose.pose.pose.position.z > 2.30 or tag.pose.pose.pose.position.z < 1.90:
                continue
            if tag.id[0] == self.id:
                new_pose_ = tag.pose.pose
                # Transform frame to world
                new_pose_.pose.position.y = -new_pose_.pose.position.y
                q_rot = quaternion_from_euler(math.pi, 0, 0)
                q_new = quaternion_multiply(q_rot, [new_pose_.pose.orientation.x, new_pose_.pose.orientation.y, new_pose_.pose.orientation.z, new_pose_.pose.orientation.w])
                new_pose_.pose.orientation.x = 0.0 * q_new[0]
                new_pose_.pose.orientation.y = 0.0 * q_new[1]
                new_pose_.pose.orientation.z = q_new[2]
                new_pose_.pose.orientation.w = q_new[3]
                new_pose_.pose.orientation = self.normalize(new_pose_.pose.orientation)
                if self.last_tag is None:
                    self.last_tag = new_pose_
                    self.last_tag_stamp = msg.header.stamp
                    rospy.loginfo("\33[92m[{}] Initial pose: ({},{})\33[0m".format(self.namespace, new_pose_.pose.position.x, new_pose_.pose.position.y))
                dx = abs(self.last_tag.pose.position.x - new_pose_.pose.position.x)
                dy = abs(self.last_tag.pose.position.y - new_pose_.pose.position.y)
                if dx > 0.3 or dy > 0.3:
                    new_pose_ = None
                    continue

        if self.last_tag_stamp is None:
            return

        if new_pose_ is None and self.id >= 10:
            return

        if new_pose_ is None and self.id < 5:
            # return
            # rospy.logwarn_throttle(1, "[{}] Not getting data from {} detections!".format(self.namespace, len(msg.detections)))
            new_pose_ = self.last_tag
            dt = (msg.header.stamp - self.last_tag_stamp).to_nsec()/1.0e9
            new_pose_.pose.position.x += self.odom_state[0] * dt
            new_pose_.pose.position.y += self.odom_state[1] * dt
            new_pose_.pose.position.z += self.odom_state[2] * dt
            q = [new_pose_.pose.orientation.x, new_pose_.pose.orientation.y, new_pose_.pose.orientation.z, new_pose_.pose.orientation.w]
            q_odom = self.normalizeA([0, 0, self.odom_state[5] * dt, self.odom_state[6] * dt])
            q = quaternion_multiply(q, q_odom)
            new_pose_.pose.orientation.x = q[0]
            new_pose_.pose.orientation.y = q[1]
            new_pose_.pose.orientation.z = q[2]
            new_pose_.pose.orientation.w = q[3]
            new_pose_.pose.orientation = self.normalize(new_pose_.pose.orientation)
        elif self.id < 5:
            dt = (msg.header.stamp - self.last_tag_stamp).to_nsec()/1.0e9 + 1e-10
            self.tag_state[0] = (new_pose_.pose.position.x - self.last_tag.pose.position.x)/dt
            self.tag_state[1] = (new_pose_.pose.position.y - self.last_tag.pose.position.y)/dt
            self.tag_state[2] = (new_pose_.pose.position.z - self.last_tag.pose.position.z)/dt
            q1 = [self.last_tag.pose.orientation.x, self.last_tag.pose.orientation.y, self.last_tag.pose.orientation.z, self.last_tag.pose.orientation.w]
            q2 = [new_pose_.pose.orientation.x, new_pose_.pose.orientation.y, new_pose_.pose.orientation.z, new_pose_.pose.orientation.w]
            q1_inv = quaternion_inverse(q1)
            qdiff = quaternion_multiply(q2, q1_inv)
            self.tag_state[3] = qdiff[0]/dt
            self.tag_state[4] = qdiff[1]/dt
            self.tag_state[5] = qdiff[2]/dt
            self.tag_state[6] = qdiff[3]/dt
            K = 0.75
            # print("Odom: {}".format(self.odom_state))
            # print("Tag: {}".format(self.tag_state))
            new_pose_.pose.position.x = self.last_tag.pose.position.x + (K) * self.odom_state[0] * dt + (1.0 - K) * self.tag_state[0] * dt
            new_pose_.pose.position.y = self.last_tag.pose.position.y + (K) * self.odom_state[1] * dt + (1.0 - K) * self.tag_state[1] * dt
            new_pose_.pose.position.z = self.last_tag.pose.position.z + (K) * self.odom_state[2] * dt + (1.0 - K) * self.tag_state[2] * dt
            # print(self.odom_state)
            # print(self.tag_state)
            # print("=====")
            q_tag_odom = self.normalizeA([0, 0, (K) * self.odom_state[5] * dt + (1.0 - K) * self.tag_state[5] * dt, (K) * self.odom_state[6] * dt + (1.0 - K) * self.tag_state[6] * dt])
            q = [new_pose_.pose.orientation.x, new_pose_.pose.orientation.y, new_pose_.pose.orientation.z, new_pose_.pose.orientation.w]
            q = quaternion_multiply(q, q_tag_odom)
            new_pose_.pose.orientation.x = q[0]
            new_pose_.pose.orientation.y = q[1]
            new_pose_.pose.orientation.z = q[2]
            new_pose_.pose.orientation.w = q[3]
            new_pose_.pose.orientation = self.normalize(new_pose_.pose.orientation)

        self.last_tag = new_pose_
        self.last_tag_stamp = msg.header.stamp
        
        # Transform frame 
        self.pose_.pose.pose.position.x =  new_pose_.pose.position.x + self.world_offset[0]  
        self.pose_.pose.pose.position.y =  new_pose_.pose.position.y + self.world_offset[1]   
        self.pose_.pose.pose.position.z =  new_pose_.pose.position.z*0
        self.pose_.pose.pose.orientation.x = new_pose_.pose.orientation.x
        self.pose_.pose.pose.orientation.y = new_pose_.pose.orientation.y
        self.pose_.pose.pose.orientation.z = new_pose_.pose.orientation.z
        self.pose_.pose.pose.orientation.w = new_pose_.pose.orientation.w

        # self.pose_.pose.pose.orientation.y = 0.0
        # self.pose_.pose.pose.orientation.z = q_new[2]
        # self.pose_.pose.pose.orientation.w = q_new[3]
        # self.pose_.pose.pose.orientation = self.normalize(self.pose_.pose.pose.orientation)


        # Compute Ground pose
        pose2d = Pose2D()
        pose2d.x = self.pose_.pose.pose.position.x
        pose2d.y = self.pose_.pose.pose.position.y
        quat = [self.pose_.pose.pose.orientation.x, self.pose_.pose.pose.orientation.y, self.pose_.pose.pose.orientation.z, self.pose_.pose.pose.orientation.w]
        (_, _, pose2d.theta) = euler_from_quaternion (quat)
        # publish data
        self.pose_.header.stamp = rospy.Time.now()
        self.pub_ground.publish(pose2d)
        self.pub.publish(self.pose_)
        if self.firt_time_pub:
            self.ref_ = [self.pose_.pose.pose.position.x, self.pose_.pose.pose.position.y, self.pose_.pose.pose.position.z, quat[0], quat[1], quat[2], quat[3]]
            self.firt_time_pub = False
        self.br.sendTransform((self.ref_[0], self.ref_[1], 0), [self.ref_[3], self.ref_[4], self.ref_[5], self.ref_[6]], rospy.Time.now(), self.namespace + "/odom", "/world")


    def run(self):
        rospy.spin()


# Main function
if __name__ == '__main__':
    try:
        rw = Tag2Pose()
        rw.run()
    except rospy.ROSInterruptException:
        rospy.loginfo("[{}] Closed!".format(rw.namespace))
