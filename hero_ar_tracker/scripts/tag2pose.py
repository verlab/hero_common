#!/usr/bin/env python3

import rospy
from apriltag_ros.msg import AprilTagDetectionArray
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Pose2D
import tf2_ros
import geometry_msgs.msg

def publish_static_transform():
    static_transform_stamped = geometry_msgs.msg.TransformStamped()
    static_transform_stamped.header.stamp = rospy.Time.now()
    static_transform_stamped.header.frame_id = "world"
    static_transform_stamped.child_frame_id = "usb_cam"

    # Define the transformation
    static_transform_stamped.transform.translation.x = 0.0  # Adjust these values as needed
    static_transform_stamped.transform.translation.y = 0.0
    static_transform_stamped.transform.translation.z = 0.0
    static_transform_stamped.transform.rotation.x = 0.0
    static_transform_stamped.transform.rotation.y = 0.0
    static_transform_stamped.transform.rotation.z = 0.0
    static_transform_stamped.transform.rotation.w = 1.0

    static_broadcaster.sendTransform(static_transform_stamped)

def tag_callback(data):
    for detection in data.detections:
        tag_id = detection.id[0]
        tag_pose = detection.pose.pose.pose

        # Check if publisher for this tag ID already exists
        if tag_id not in publishers:
            topic_name = f'/hero_{tag_id}/pose'
            publishers[tag_id] = rospy.Publisher(topic_name, Odometry, queue_size=1)
        
        # Populate and publish PoseStamped message
        pose_msg = Odometry()
        pose_msg.header.stamp = rospy.Time.now()
        pose_msg.header.frame_id = 'world'
        pose_msg.child_frame_id = f'/hero_{tag_id}/base_link'
        
        # Assuming detection.pose contains the tag's pose information
        pose_msg.pose.pose = tag_pose
        
        publishers[tag_id].publish(pose_msg)
        publish_static_transform()

if __name__ == '__main__':
    rospy.init_node('tag2pose')

    # Initialize publishers dictionary
    publishers = {}

    # Initialize tf2_ros StaticTransformBroadcaster
    static_broadcaster = tf2_ros.StaticTransformBroadcaster()

    # Publish the static transform once
    publish_static_transform()


    # Subscriber to listen for tag detections
    rospy.Subscriber('/tag_detections', AprilTagDetectionArray, tag_callback)

    rospy.spin()
