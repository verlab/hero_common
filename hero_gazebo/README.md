# Gazebo Simulations
We provide HeRo simulations on Gazebo.

## Features
- Differential drive controller
- Odometry
- IMU
- IR Proximity range (simulated with laser)


## How to use
- Open the terminal and type the following command. This command will initiate Gazebo and spawn on HeRo using potential field controller as an example.
```sh
$ roslaunch hero_gazebo gazebo_bringup.launch 
```
![system](../hero_resources/media/images/gazebo_1.png)
![system](../hero_resources/media/images/gazebo_2.png)

- If you want to spawn another robot, just use the following command. It's important set the argument id for every robot that you spawn.
```sh
$ roslaunch hero_gazebo hero_spawn.launch id:=1 y:=-0.8 x:=1.8
```
![system](../hero_resources/media/images/gazebo_mul.png)
![system](../hero_resources/media/images/gazebo_3.png)

## Configurations
Feel free to disable some unusable sensors. I believe that the easy way to do that is commenting some includes on robot.urdf.xacro, in hero_descriptions. For example, the following hero description will disable the imu and laser.
```xml
<?xml version="1.0"?>
<robot xmlns:xacro="http://www.ros.org/wiki/xacro" name="hero_0">
  <!-- Properties  -->
  <xacro:include filename="$(find hero_description)/urdf/common.xacro" />
  <!-- Initiate HeRo model and controller -->
  <xacro:include filename="$(find hero_description)/urdf/hero.xacro" />
  <xacro:include filename="$(find hero_description)/urdf/hero.gazebo.xacro" />
  <xacro:include filename="$(find hero_description)/urdf/hero.transmissions.xacro" />
  <!-- Initiate Laser and IMU sensors -->
  <!--xacro:include filename="$(find hero_description)/urdf/laser.xacro" /-->
  <!--xacro:include filename="$(find hero_description)/urdf/laser.gazebo.xacro" /-->
  <!--xacro:include filename="$(find hero_description)/urdf/imu.gazebo.xacro" /-->

</robot>
```
