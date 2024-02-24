#!/usr/bin/env python3

import rospy
import math

from apriltag_ros.msg import AprilTagDetectionArray
from nav_msgs.msg import Odometry

import tf2_ros
from geometry_msgs.msg import TransformStamped

from tf.transformations import euler_from_quaternion, quaternion_from_euler, quaternion_multiply, quaternion_inverse


def publish_static_transform():
    static_transform_stamped = TransformStamped()
    static_transform_stamped.header.stamp = rospy.Time.now()
    static_transform_stamped.header.frame_id = "world"
    static_transform_stamped.child_frame_id = "usb_cam"

    # Define the transformation
    static_transform_stamped.transform.translation.x = (
        0.0  # Adjust these values as needed
    )
    static_transform_stamped.transform.translation.y = 0.0
    static_transform_stamped.transform.translation.z = 0.0
    static_transform_stamped.transform.rotation.x = 0.0
    static_transform_stamped.transform.rotation.y = 0.0
    static_transform_stamped.transform.rotation.z = 0.0
    static_transform_stamped.transform.rotation.w = 1.0

    static_broadcaster.sendTransform(static_transform_stamped)


def normalize(q):
    dx2 = q.x * q.x
    dy2 = q.y * q.y
    dz2 = q.z * q.z
    dw2 = q.w * q.w
    norm = math.sqrt(dw2 + dz2 + dy2 + dx2)  # + 10e-9
    if abs(norm) < 1e-8:
        norm = 1
        q[3] = 1
    q.x /= norm
    q.y /= norm
    q.z /= norm
    q.w /= norm
    return q


def odom_callback(self, msg, tag_id):
    if tag_id not in odom_state:
        odom_state[tag_id] = {
            "prev_msg": msg,
            "d_position": {"x": 0, "y": 0, "z": 0},
            "d_orientation": {"x": 0, "y": 0, "z": 0, "w": 1},
        }
    else:
        dt = (msg.header.stamp - odom_state[tag_id]["prev_msg"].header.stamp).to_nsec() / 1.0e9 + 1e-10

        odom_state[tag_id]["d_position"]["x"] = (msg.pose.pose.position.x - odom_state[tag_id]["prev_msg"].pose.pose.position.x) / dt
        odom_state[tag_id]["d_position"]["y"] = (msg.pose.pose.position.y - odom_state[tag_id]["prev_msg"].pose.pose.position.y) / dt
        odom_state[tag_id]["d_position"]["z"] = (msg.pose.pose.position.z - odom_state[tag_id]["prev_msg"].pose.pose.position.z) / dt

        q0 = [odom_state[tag_id]["prev_msg"].pose.pose.orientation.x, 
              odom_state[tag_id]["prev_msg"].pose.pose.orientation.y, 
              odom_state[tag_id]["prev_msg"].pose.pose.orientation.z, 
              odom_state[tag_id]["prev_msg"].pose.pose.orientation.w]
        
        qt = [msg.pose.pose.orientation.x, 
              msg.pose.pose.orientation.y, 
              msg.pose.pose.orientation.z, 
              msg.pose.pose.orientation.w]
        
        q0_inv = quaternion_inverse(q0)
        qdiff = quaternion_multiply(qt, q0_inv)

        odom_state[tag_id]["d_orientation"]["x"] = qdiff[0]/dt
        odom_state[tag_id]["d_orientation"]["y"] = qdiff[1]/dt
        odom_state[tag_id]["d_orientation"]["z"] = qdiff[2]/dt
        odom_state[tag_id]["d_orientation"]["w"] = qdiff[3]/dt

        odom_state[tag_id]["prev_msg"] = msg


def tag_callback(data):
    new_poses = {}
    
    for detection in data.detections:
        tag_id = detection.id[0]
        tag_pose = detection.pose.pose.pose

        # Check if publisher for this tag ID already exists
        if tag_id not in publishers:
            pose_topic_name = f"/hero_{tag_id}/pose"
            odom_topic_name = f"/hero_{tag_id}/odom"
            publishers[tag_id] = rospy.Publisher(
                pose_topic_name, Odometry, queue_size=1
            )
            rospy.Subscriber(odom_topic_name, Odometry, odom_callback, tag_id)

        # Populate and publish PoseStamped message
        pose_msg = Odometry()
        pose_msg.header.stamp = rospy.Time.now()
        pose_msg.header.frame_id = "world"
        pose_msg.child_frame_id = f"/hero_{tag_id}/base_link"
        # print(tag_pose)

        # Assuming detection.pose contains the tag's pose information
        pose_msg.pose.pose = tag_pose
        pose_msg.pose.pose.position.y = -pose_msg.pose.pose.position.y
        pose_msg.pose.pose.position.z = 0

        q_rot = quaternion_from_euler(math.pi, 0, 0)
        q_new = quaternion_multiply(
            q_rot,
            [
                pose_msg.pose.pose.orientation.x,
                pose_msg.pose.pose.orientation.y,
                pose_msg.pose.pose.orientation.z,
                pose_msg.pose.pose.orientation.w,
            ],
        )
        pose_msg.pose.pose.orientation.x = 0
        pose_msg.pose.pose.orientation.y = 0
        pose_msg.pose.pose.orientation.z = q_new[2]
        pose_msg.pose.pose.orientation.w = q_new[3]
        pose_msg.pose.pose.orientation = normalize(pose_msg.pose.pose.orientation)

        publishers[tag_id].publish(pose_msg)
        publish_static_transform()


if __name__ == "__main__":
    rospy.init_node("tag2pose")

    # Initialize publishers dictionary
    publishers = {}
    odom_state = {}

    # Initialize tf2_ros StaticTransformBroadcaster
    static_broadcaster = tf2_ros.StaticTransformBroadcaster()

    # Publish the static transform once
    publish_static_transform()

    # Subscriber to listen for tag detections
    rospy.Subscriber("/tag_detections", AprilTagDetectionArray, tag_callback)

    rospy.spin()
