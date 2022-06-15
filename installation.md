---
layout: page
title: Installation
permalink: /installation/
---

# How to install HeRo common node
- If you don't have a ROS Workspace, you must download and configure it. Please, follow the instructions in http://wiki.ros.org/ROS/Installation and http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment.


- Using git (or download the zip file) clone this repository into ROS Workspace.
```
$ git clone https://github.com/verlab/hero_common.git
```
- Compile with: 
```
$ catkin_make # or catkin build
```
- Fixing package dependencies:
```
$ apt install ros-noetic-usb-cam
$ apt install ros-noetic-rosserial
$ apt install ros-noetic-rosserial-server
```



# How to install the firmware
- Open the arduino IDE.
- Go to preferences:
 - Change the sketchbook location to access the folder firmware.
 - Add (http://arduino.esp8266.com/stable/package_esp8266com_index.json) to Additional Boards Manager URLS.
 - Restart the IDE.
- Go to Sketchbook/hero/firware




# Robots Firmware
- Open the robot code inside the sketchbook.
- All configuration parameters are available at config.h
  - WiFi Essid and password for connection with ROS master
  - Robot ID
- Connect HeRo at USB and upload the code.
