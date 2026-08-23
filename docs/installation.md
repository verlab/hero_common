---
layout: page
title: Install ROS
permalink: /installation/
section: software
lead: Step 1 of 4. Clone the catkin workspace, then pick Docker or compile from source. Tested on ROS 1 Melodic and Noetic.
---

## What you need

- [ROS 1](http://wiki.ros.org/ROS/Installation) — Melodic or Noetic
- [rosserial](http://wiki.ros.org/rosserial)
- [Gazebo](https://gazebosim.org/home) and [Qt](https://www.qt.io/) if you will run the simulator later

The Arduino IDE is only needed in the next step, when you flash the ESP8266.

## Docker

If Docker is not installed yet, follow the [NVIDIA container toolkit guide](https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/install-guide.html) (or the official Docker docs).

Clone the repository and build the ROS 1 image:

```sh
$ git clone https://github.com/verlab/hero_common.git
$ cd hero_common/hero_common
$ docker-compose build ros1
```

## Build from source

If you do not have a catkin workspace yet, follow the [ROS install](http://wiki.ros.org/ROS/Installation) and [workspace](http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment) tutorials, then clone into `src`:

```sh
$ cd ~/catkin_ws/src
$ git clone --depth 1 --branch noetic-devel https://github.com/verlab/hero_common.git
```

Install dependencies and compile:

```sh
$ cd ~/catkin_ws
$ rosdep install --from-paths src/hero_common --ignore-src -r -y
$ catkin_make
$ source devel/setup.bash
```
