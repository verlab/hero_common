# Swarm Robots Project (Verlab)
[![N|Solid](http://www.verlab.dcc.ufmg.br/verlab/wp-content/uploads/2014/06/logo-verlab-small-transp-300x572.png)](www.verlab.dcc.ufmg.br)

This project contributes to an open source ROS-based framework for swarm robotics. We propose an low cost, high availability swarm system that could be printed and assembled multiple times without special knowledge or hardware skills.

# Authors:
- [Paulo Rezeck](https://github.com/rezeck)
- [Hector Azpurua](https://github.com/h3ct0r)

# Dependencies
- ROS Kinect
- rosserial
- Arduino IDE (to install the firmware)

# How to install Swarm Robots Node
- Using git (or download the zip file) clone this repository into ros workspace.
- Compile with: 
```
$ catkin_make
```

# How to install the firmware
- Open the arduino IDE. 
- Go to preferences and change the sketchbook location to access the folder firmware (restart the IDE).

## Sink Firmware
- Open the sink code inside the sketchbook.
- Connect the sink usb device and upload the code.

## Robots Firmware
- Open the robot code inside the sketchbook.
- Change the ID variable to one that you want.
- Connect the robot via usb and upload the code.

# How to start the framework
- Run the swarm_node.launch file with:
```
$ roslaunch swarm_driver swarm_node.launch
```
- Run the swarm_teleop.launch file to control it:
```
$ roslaunch swarm_driver swarm_teleop.launch
```
 
# TODO LIST
- [ ] Add proximity sensors on robot.
- [ ] Build a small model of the robot.
- [ ] Implement a method to compute the odometry.
- [ ] Add new magnetic joints
- [ ] Location system (cameras)
- [ ] Swarm controller in ROS 
