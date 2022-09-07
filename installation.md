---
layout: page
title: Installation
permalink: /installation/
---

## Dependencies
- [ROS](http://wiki.ros.org/ROS/Installation) (tested on Melodic and Noetic);
- [rosserial](http://wiki.ros.org/rosserial);
- [Gazebo](https://gazebosim.org/home);
- [QT](https://www.qt.io/);
- [Arduino IDE](https://www.arduino.cc/en/software) (only for firmware programming);

## Method 1: Docker
> If you don't have Docker installed you may want to check this [tutorial](https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/install-guide.html).

Using git (or download the zip file) clone this repository into your preferable directory.
```sh
$ git clone https://github.com/verlab/hero_common.git
```
Access the folder hero_common, build the docker compose file:
```sh
$ cd hero_common/hero_common
$ docker-compose build ros1 # for ROS 1 noetic installation
$ docker-compose build # for ROS 2 foxy installation
```
> This package it not fully compatible with ROS 2, but you can execute the package on ROS 1 instance, and use ros1_bridge which is a ROS 2 package that allow ROS 2 to interface with ROS 1 topics and services.

## Method 2: Build from source
> If you don't have a ROS Workspace, you must download and configure it. 
Please, follow the instructions in http://wiki.ros.org/ROS/Installation and http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment.

- Using git (or download the zip file) clone this repository into ROS Workspace (e.g. ~/catkin-ws). Select the properly branch given your ROS distro.
```sh
$ cd ~/catkin_ws/src
$ git clone --depth 1 --branch noetic-devel https://github.com/verlab/hero_common.git # select your ROS distro
```

- Fixing package dependencies:
```sh
$ cd ..
$ rosdep install --from-paths src/hero_common --ignore-src -r -y
```

- Compile your ROS workspace directory (e.g. ~/catkin-ws): 
```sh
$ cd ~/catkin_ws
$ catkin_make # or catkin build
$ source devel/setup.bash # Set the appropriate bash extension
```
