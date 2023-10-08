#! /usr/bin/env python3
from __future__ import print_function
import re

from PyQt5 import QtWidgets, uic
from PyQt5.QtCore import *
from PyQt5.QtGui import *

import roslib

roslib.load_manifest("urdfdom_py")
import rospy
import rospkg
from urdf_parser_py.urdf import URDF

from std_srvs.srv import Empty
from gazebo_msgs.srv import DeleteModel
from gazebo_msgs.srv import SpawnModel, SpawnModelRequest

from gazebo_msgs.msg import ModelStates

import sys
import math
import os
import subprocess
import time


class Ui(QtWidgets.QMainWindow):
    def __init__(self):
        # Call the inherited classes __init__ method
        super(Ui, self).__init__()

        # ROS Init
        rospy.init_node("hero_setup", anonymous=False)
        rospy.Subscriber(
            "/gazebo/model_states", ModelStates, self.model_states_callback
        )
        self.current_model_states = None

        # Parameters
        self.n_robots = 0
        self.max_delay = 2000

        # Get ROS package path
        self.rospack = rospkg.RosPack()
        self.pkg_path = self.rospack.get_path("hero_gazebo")
        self.ui_path = self.pkg_path + "/script/hero_setup_gui.ui"

        # Load the .ui file
        uic.loadUi(self.ui_path, self)

        # Getting UI Objects
        self.gazebo_logo_label = self.findChild(QtWidgets.QLabel, "gazebo_logo_label")
        self.logo_pixmap = QPixmap(self.pkg_path + "/script/resource/gazebo_logo.png")
        self.gazebo_logo_label.setPixmap(self.logo_pixmap)

        self.statusBar = QtWidgets.QStatusBar()
        self.statusBar.setStyleSheet("color: rgb(245, 121, 0);")
        self.setStatusBar(self.statusBar)
        self.statusBar.showMessage("> Welcome: ")

        self.pause_button = self.findChild(QtWidgets.QPushButton, "pause_button")
        self.pause_button.clicked.connect(self.on_click_pause_button)
        self.on_click_pause_button()

        self.reset_model_button = self.findChild(
            QtWidgets.QPushButton, "reset_model_button"
        )
        self.reset_model_button.clicked.connect(self.on_click_reset_model_button)

        self.reset_world_button = self.findChild(
            QtWidgets.QPushButton, "reset_world_button"
        )
        self.reset_world_button.clicked.connect(self.on_click_reset_world_button)

        self.clear_env_button = self.findChild(
            QtWidgets.QPushButton, "clear_env_button"
        )
        self.clear_env_button.clicked.connect(self.on_click_clear_env_button)

        self.commit_arena_button = self.findChild(
            QtWidgets.QPushButton, "commit_arena_button"
        )
        self.commit_arena_button.clicked.connect(self.on_click_commit_arena_button)

        self.clear_arena_button = self.findChild(
            QtWidgets.QPushButton, "clear_arena_button"
        )
        self.clear_arena_button.clicked.connect(self.on_click_clear_arena_button)

        self.arena_pixmap_label = self.findChild(QtWidgets.QLabel, "arena_pixmap_label")
        self.arena_pixmap_label.setPixmap(
            QPixmap(self.pkg_path + "/worlds/models/arena_1/arena.jpg")
        )

        self.select_arena_box = self.findChild(QtWidgets.QComboBox, "select_arena_box")
        self.select_arena_box.currentIndexChanged.connect(
            self.on_click_select_arena_box
        )
        self.arenas = [f"arena_{i}" for i in range(8)]
        self.select_arena_box.addItems(self.arenas)
        self.current_arena = self.arenas[0]

        self.swarm_size_spinBox = self.findChild(
            QtWidgets.QSpinBox, "swarm_size_spinBox"
        )

        self.commit_swarm_button = self.findChild(
            QtWidgets.QPushButton, "commit_swarm_button"
        )
        self.commit_swarm_button.clicked.connect(self.on_click_commit_swarm_button)

        self.clear_swarm_button = self.findChild(
            QtWidgets.QPushButton, "clear_swarm_button"
        )
        self.clear_swarm_button.clicked.connect(self.on_click_clear_swarm_button)

        self.laser_checkBox = self.findChild(QtWidgets.QCheckBox, "laser_checkBox")
        self.odometry_checkBox = self.findChild(
            QtWidgets.QCheckBox, "odometry_checkBox"
        )
        self.led_checkBox = self.findChild(QtWidgets.QCheckBox, "led_checkBox")
        self.encoder_checkBox = self.findChild(QtWidgets.QCheckBox, "encoder_checkBox")
        self.imu_checkBox = self.findChild(QtWidgets.QCheckBox, "imu_checkBox")
        self.local_planner_checkBox = self.findChild(
            QtWidgets.QCheckBox, "local_planner_checkBox"
        )

        self.gen_launch_button = self.findChild(
            QtWidgets.QPushButton, "gen_launch_button"
        )
        self.gen_launch_button.clicked.connect(self.on_click_gen_launch_button)

        # Show the GUI
        self.show()

    def on_click_pause_button(self):
        if self.pause_button.isChecked():
            rospy.wait_for_service("/gazebo/pause_physics")
            try:
                serv = rospy.ServiceProxy("/gazebo/pause_physics", Empty)
                serv()
                self.pause_button.setText("Pause Physics")
                self.statusBar.showMessage("> Command: pause physics successed!")
            except rospy.ServiceException as e:
                print("Service call failed: %s" % e)
                self.statusBar.showMessage("> Command: pause physics failed!")
        else:
            rospy.wait_for_service("/gazebo/pause_physics")
            try:
                serv = rospy.ServiceProxy("/gazebo/unpause_physics", Empty)
                serv()
                self.pause_button.setText("Play Physics")
                self.statusBar.showMessage("> Command: play physics successed!")
            except rospy.ServiceException as e:
                print("Service call failed: %s" % e)
                self.statusBar.showMessage("> Command: play physics failed!")

    def on_click_reset_model_button(self):
        rospy.wait_for_service("/gazebo/reset_simulation")
        try:
            serv = rospy.ServiceProxy("/gazebo/reset_simulation", Empty)
            serv()
            self.statusBar.showMessage("> Command: reset simulation successed!")
        except rospy.ServiceException as e:
            print("Service call failed: %s" % e)
            self.statusBar.showMessage("> Command: reset simulation failed!")

    def on_click_reset_world_button(self):
        rospy.wait_for_service("/gazebo/reset_world")
        try:
            serv = rospy.ServiceProxy("/gazebo/reset_world", Empty)
            serv()
            self.statusBar.showMessage("> Command: reset world successed!")
        except rospy.ServiceException as e:
            print("Service call failed: %s" % e)
            self.statusBar.showMessage("> Command: reset world failed!")

    def on_click_clear_env_button(self):
        self.on_click_clear_swarm_button()
        self.on_click_clear_arena_button()

    def on_click_clear_arena_button(self):
        rospy.wait_for_service("/gazebo/delete_model")
        for arena_model in self.arenas:
            try:
                serv = rospy.ServiceProxy("/gazebo/delete_model", DeleteModel)
                serv(arena_model)
                self.statusBar.showMessage("> Command: clear arena successed!")
            except rospy.ServiceException as e:
                print("Service call failed: %s" % e)
                self.statusBar.showMessage("> Command: clear arena failed!")

    def on_click_commit_arena_button(self):
        rospy.wait_for_service("/gazebo/spawn_urdf_model")
        try:
            serv = rospy.ServiceProxy("/gazebo/spawn_urdf_model", SpawnModel)
            req = SpawnModelRequest()
            req.model_name = self.current_arena
            req.model_xml = open(
                self.rospack.get_path("hero_gazebo")
                + "/worlds/models/"
                + self.current_arena
                + "/arena.urdf",
                "r",
            ).read()
            # print((req.model_xml))
            req.robot_namespace = ""
            req.reference_frame = "world"
            serv(req)
            self.statusBar.showMessage("> Command: commit arena successed!")
            return serv
        except rospy.ServiceException as e:
            print("Service call failed: %s" % e)
            self.statusBar.showMessage("> Command: commit arena failed!")

    def on_click_select_arena_box(self, index):
        self.current_arena = self.arenas[index]
        self.arena_pixmap_label.setPixmap(
            QPixmap(
                self.pkg_path + "/worlds/models/" + self.current_arena + "/arena.jpg"
            )
        )

    def on_click_commit_swarm_button(self):
        num_robots = self.swarm_size_spinBox.value()
        self.statusBar.showMessage(
            "> Command: commiting {} robots...".format(num_robots)
        )
        for i in range(num_robots):
            self.statusBar.showMessage(
                "> Command: commiting {} of {} robots...".format(i + 1, num_robots)
            )
            rospy.wait_for_service("/gazebo/spawn_urdf_model")
            try:
                serv = rospy.ServiceProxy("/gazebo/spawn_urdf_model", SpawnModel)
                req = SpawnModelRequest()
                req.model_name = "hero_" + str(i)
                req.model_xml = open(
                    self.rospack.get_path("hero_description")
                    + "/robot/hero_light.urdf",
                    "r",
                ).read()
                print((req.model_xml))
                req.robot_namespace = "hero_" + str(i)
                req.reference_frame = "world"
                req.initial_pose.position.z = 0.4
                req.initial_pose.position.x = (
                    0.2 * (i % math.sqrt(num_robots))
                    - 0.2 * math.sqrt(num_robots) / 2.0
                )
                req.initial_pose.position.y = (
                    0.2 * int(i / math.sqrt(num_robots))
                    - 0.2 * math.sqrt(num_robots) / 2.0
                )
                serv(req)
                self.statusBar.showMessage(
                    "> Command: commit robot {} of {} successed!".format(
                        i + 1, self.swarm_size_spinBox.value()
                    )
                )
            except rospy.ServiceException as e:
                print("Service call failed: %s" % e)
                self.statusBar.showMessage("> Command: commit swarm failed!")
            print("Closed!")

    def on_click_clear_swarm_button(self):
        rospy.wait_for_service("/gazebo/delete_model")
        for i in range(100):
            try:
                serv = rospy.ServiceProxy("/gazebo/delete_model", DeleteModel)
                serv("hero_" + str(i))
                self.statusBar.showMessage("> Command: clearing swarm! Wait...")
            except rospy.ServiceException as e:
                print("Service call failed: %s" % e)
                self.statusBar.showMessage("> Command: clear swarm failed!")
        self.statusBar.showMessage("> Command: clear swarm successed!")

    def model_states_callback(self, msg):
        self.current_model_states = msg

    def on_click_gen_launch_button(self):
        urdf_file = "hero_light.urdf"
        if self.imu_checkBox.isChecked():
            urdf_file = "hero_imu.urdf"
        if self.laser_checkBox.isChecked():
            urdf_file = "hero_laser.urdf"
        if self.imu_checkBox.isChecked() and self.laser_checkBox.isChecked():
            urdf_file = "hero.urdf"

        if self.current_model_states is None:
            self.statusBar.showMessage(
                "> Command: failed to generate launch! Gazebo isn't ready! Try unpause the physics first! "
            )
            return
        launch_file = "<launch>"

        launch_file += """
	<param name="/robot_description" textfile="{}"/>
			""".format(
            "$(find hero_description)/robot/" + urdf_file
        )

        for i in range(len(self.current_model_states.name)):
            model_name = self.current_model_states.name[i]
            model_pose = self.current_model_states.pose[i]
            if "hero_" in model_name:
                launch_file += """
    <group ns ="{}">
        <param name="tf_prefix" value="{}" />
        <param name="robot_description_{}" command="$(find xacro)/xacro '$(find hero_description)/robot/hero_light.urdf'"/>
        <node name="spawn_urdf_{}" pkg="gazebo_ros" type="spawn_model" args="-urdf -model {} -x {} -y {} -z {} -robot_namespace {} -file {}" />
        <node pkg="tf" type="static_transform_publisher" name="{}_broadcaster" args="0 0 0 0 0 0 world /{}/odom 20" />
        <node name="robot_state_publisher" pkg="robot_state_publisher" type="robot_state_publisher"/>""".format(
                    model_name,
                    model_name,
                    model_name,
                    model_name,
                    model_name,
                    round(model_pose.position.x, 4),
                    round(model_pose.position.y, 4),
                    round(model_pose.position.z + 0.2, 4),
                    model_name,
                    "$(find hero_description)/robot/" + urdf_file,
                    model_name,
                    model_name,
                )
                if self.local_planner_checkBox.isChecked():
                    launch_file += """
		<node name="hero_local_planner_{}" pkg="hero_examples" type="local_planner.py" args="{}" output="screen"/>""".format(
                        model_name, model_name
                    )
                launch_file += """
    </group>"""

            if "arena" in model_name:
                launch_file += """
	<arg name="map_file" default="$(find hero_gazebo)/worlds/models/{}/map.yaml"/>
  	<node name="map_server" pkg="map_server" type="map_server" args="$(arg map_file)" />""".format(
                    model_name
                )

                launch_file += """
    <node pkg="tf" type="static_transform_publisher" name="map_to_world_broadcaster"
          args="0 0 0 0 0 0 map world 5" />"""

                launch_file += """
	<node name="spawn_urdf_{}" pkg="gazebo_ros" type="spawn_model" args="-urdf -model {} -x {} -y {} -z {} -file {}" />
""".format(
                    model_name,
                    model_name,
                    round(model_pose.position.x, 4),
                    round(model_pose.position.y, 4),
                    round(model_pose.position.z, 4),
                    "$(find hero_gazebo)/worlds/models/" + model_name + "/arena.urdf",
                )
        launch_file += """
</launch>"""
        print("\33[95m{}\33[0m".format(launch_file))
        self.preferedName = (
            self.rospack.get_path("hero_gazebo") + "/launch/custom_env.launch"
        )
        self.launchFileName = QtWidgets.QFileDialog.getSaveFileName(
            directory=self.preferedName
        )[0]
        with open(self.launchFileName, "w") as out_file:
            out_file.write(launch_file)


# Create an instance of QtWidgets.QApplication
app = QtWidgets.QApplication(sys.argv)
# Create an instance of our class
window = Ui()
# Start the application
app.exec_()
