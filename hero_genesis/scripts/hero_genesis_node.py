#!/usr/bin/env python
"""ROS 1 bridge for the Genesis HeRo engine.

Topic layout matches hero_gazebo / firmware:
  /hero_N/cmd_vel
  /hero_N/velocity_controller/cmd_vel
  /hero_N/odom
  /hero_N/laser
  /hero_N/imu
  /hero_N/led
  /hero_N/encoder
  TF world -> /hero_N/odom -> hero_N/base_link
"""
from __future__ import print_function

import json
import math
import socket
import time

import rospy
import tf
from geometry_msgs.msg import Twist
from hero_common.msg import Encoder
from nav_msgs.msg import Odometry
from sensor_msgs.msg import Imu, JointState, LaserScan
from std_msgs.msg import ColorRGBA
from rosgraph_msgs.msg import Clock


N_RAYS = 16
RANGE_MIN = 0.037
RANGE_MAX = 0.50
WHEEL_RADIUS = 0.025


class EngineClient(object):
    def __init__(self, host, port, timeout=30.0):
        deadline = time.time() + timeout
        last_err = None
        while time.time() < deadline and not rospy.is_shutdown():
            try:
                sock = socket.create_connection((host, port), timeout=2.0)
                sock.settimeout(0.0)
                self.sock = sock
                self.buf = ""
                return
            except Exception as err:
                last_err = err
                rospy.sleep(0.4)
        raise RuntimeError("Genesis engine not reachable at %s:%s (%s)" % (host, port, last_err))

    def send(self, payload):
        try:
            self.sock.sendall((json.dumps(payload) + "\n").encode("utf-8"))
        except Exception as err:
            rospy.logwarn_throttle(2.0, "engine send failed: %s" % err)

    def poll(self):
        states = []
        try:
            chunk = self.sock.recv(65536)
        except Exception:
            return states
        if not chunk:
            return states
        self.buf += chunk.decode("utf-8", "replace")
        while "\n" in self.buf:
            line, self.buf = self.buf.split("\n", 1)
            line = line.strip()
            if not line:
                continue
            try:
                msg = json.loads(line)
            except ValueError:
                continue
            if msg.get("type") == "state":
                states.append(msg)
        return states

    def close(self):
        try:
            self.sock.close()
        except Exception:
            pass


class HeroBridge(object):
    def __init__(self):
        self.num = int(rospy.get_param("~num_robots", 4))
        host = rospy.get_param("~engine_host", "127.0.0.1")
        port = int(rospy.get_param("~engine_port", 11312))
        self.use_sim_time = rospy.get_param("/use_sim_time", True)
        self.engine = EngineClient(host, port)
        self.br = tf.TransformBroadcaster()
        self.clock_pub = rospy.Publisher("/clock", Clock, queue_size=10)
        self.robots = []
        for i in range(self.num):
            ns = "/hero_%d" % i
            robot = {
                "id": i,
                "ns": ns,
                "odom": rospy.Publisher(ns + "/odom", Odometry, queue_size=10),
                "laser": rospy.Publisher(ns + "/laser", LaserScan, queue_size=10),
                "imu": rospy.Publisher(ns + "/imu", Imu, queue_size=10),
                "enc": rospy.Publisher(ns + "/encoder", Encoder, queue_size=10),
                "js": rospy.Publisher(ns + "/joint_states", JointState, queue_size=10),
                "prev_ticks": None,
                "prev_t": None,
            }
            rospy.Subscriber(ns + "/cmd_vel", Twist, self._cmd_cb, i, queue_size=10)
            rospy.Subscriber(
                ns + "/velocity_controller/cmd_vel", Twist, self._cmd_cb, i, queue_size=10
            )
            rospy.Subscriber(ns + "/led", ColorRGBA, self._led_cb, i, queue_size=10)
            self.robots.append(robot)
        rospy.loginfo("HeRo Genesis bridge: %d robots on %s:%s" % (self.num, host, port))

    def _cmd_cb(self, msg, idx):
        self.engine.send({
            "type": "cmd_vel",
            "id": idx,
            "lin": msg.linear.x,
            "ang": msg.angular.z,
        })

    def _led_cb(self, msg, idx):
        self.engine.send({
            "type": "led",
            "id": idx,
            "r": msg.r,
            "g": msg.g,
            "b": msg.b,
            "a": msg.a,
        })

    def publish_state(self, state):
        stamp = rospy.Time.from_sec(float(state.get("t", 0.0)))
        if self.use_sim_time:
            clk = Clock()
            clk.clock = stamp
            self.clock_pub.publish(clk)
        by_id = {int(r["id"]): r for r in state.get("robots", [])}
        for robot in self.robots:
            data = by_id.get(robot["id"])
            if not data:
                continue
            self._publish_one(robot, data, stamp)

    def _publish_one(self, robot, data, stamp):
        idx = robot["id"]
        ns = "hero_%d" % idx
        odom_frame = "%s/odom" % ns
        base_frame = "%s/base_link" % ns
        laser_frame = "%s/laser_link" % ns
        x, y, yaw = float(data["x"]), float(data["y"]), float(data["yaw"])
        v, w = float(data["v"]), float(data["w"])
        quat = tf.transformations.quaternion_from_euler(0, 0, yaw)

        self.br.sendTransform((0, 0, 0), (0, 0, 0, 1), stamp, odom_frame, "world")
        self.br.sendTransform((x, y, 0.0), quat, stamp, base_frame, odom_frame)
        self.br.sendTransform((0, 0, 0.051), (0, 0, 0, 1), stamp, laser_frame, base_frame)

        odom = Odometry()
        odom.header.stamp = stamp
        odom.header.frame_id = odom_frame
        odom.child_frame_id = base_frame
        odom.pose.pose.position.x = x
        odom.pose.pose.position.y = y
        odom.pose.pose.orientation.x = quat[0]
        odom.pose.pose.orientation.y = quat[1]
        odom.pose.pose.orientation.z = quat[2]
        odom.pose.pose.orientation.w = quat[3]
        odom.twist.twist.linear.x = v
        odom.twist.twist.angular.z = w
        robot["odom"].publish(odom)

        scan = LaserScan()
        scan.header.stamp = stamp
        scan.header.frame_id = laser_frame
        scan.angle_min = -math.pi
        scan.angle_max = math.pi
        scan.angle_increment = 2.0 * math.pi / N_RAYS
        scan.time_increment = 0.0
        scan.scan_time = 0.05
        scan.range_min = RANGE_MIN
        scan.range_max = RANGE_MAX
        scan.ranges = [float(r) for r in data.get("ranges", [RANGE_MAX] * N_RAYS)]
        robot["laser"].publish(scan)

        imu = Imu()
        imu.header.stamp = stamp
        imu.header.frame_id = "%s/hat_link" % ns
        imu.orientation.x = quat[0]
        imu.orientation.y = quat[1]
        imu.orientation.z = quat[2]
        imu.orientation.w = quat[3]
        imu.angular_velocity.z = w
        imu.linear_acceleration.z = 9.81
        robot["imu"].publish(imu)

        t = float(stamp.to_sec())
        left = float(data.get("left_ticks", 0.0))
        right = float(data.get("right_ticks", 0.0))
        prev = robot["prev_ticks"]
        dt = 0.01 if robot["prev_t"] is None else max(1e-4, t - robot["prev_t"])
        ld = 0.0 if prev is None else left - prev[0]
        rd = 0.0 if prev is None else right - prev[1]
        enc = Encoder()
        enc.header.stamp = stamp
        enc.header.frame_id = base_frame
        enc.left_ticks = left
        enc.right_ticks = right
        enc.left_diff = ld
        enc.right_diff = rd
        enc.left_dist = ld * (2.0 * math.pi * WHEEL_RADIUS) / 288.0
        enc.right_dist = rd * (2.0 * math.pi * WHEEL_RADIUS) / 288.0
        enc.timestep = dt
        enc.left_speed = float(data.get("wl", 0.0))
        enc.right_speed = float(data.get("wr", 0.0))
        enc.left_speed_filtered = enc.left_speed
        enc.right_speed_filtered = enc.right_speed
        robot["enc"].publish(enc)
        robot["prev_ticks"] = (left, right)
        robot["prev_t"] = t

        js = JointState()
        js.header.stamp = stamp
        js.name = ["left_wheel_joint", "right_wheel_joint"]
        js.position = [left * 2.0 * math.pi / 288.0, right * 2.0 * math.pi / 288.0]
        js.velocity = [enc.left_speed, enc.right_speed]
        robot["js"].publish(js)

    def spin(self):
        rate = rospy.Rate(100)
        try:
            while not rospy.is_shutdown():
                for state in self.engine.poll():
                    self.publish_state(state)
                rate.sleep()
        finally:
            self.engine.close()


def main():
    rospy.init_node("hero_genesis")
    HeroBridge().spin()


if __name__ == "__main__":
    main()
