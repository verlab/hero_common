# HeRo brignup Server

This package bringup rosserial tcp server to connect the robots with ROS.

## How to use
- Connect the robot on the same network where your computer is.
- Open the terminal and type the following command. This launch file calls the rosserial python server.

```sh
$ roslaunch hero_bringup hero_bringup.launch
```

## Teleoperation
- To remotely control the robot, use the following command. It's important to set the id of the robot by using the arguments id.
- Use the keyboard to control the robot. Use the keys w/x to decrease the linear speed to less than 0.25 cm/s and the keys e/c to adjust the angular speed.

```sh
$ roslaunch hero_bringup hero_teleop.launch id:=0
```