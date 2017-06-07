# HeRo: An Open Platform for Robotics Research and Education
[![N|Solid](http://www.verlab.dcc.ufmg.br/verlab/wp-content/uploads/2014/06/logo-verlab-small-transp-300x572.png)](www.verlab.dcc.ufmg.br)

This project contributes to an open source ROS-based framework for swarm robotics. We propose an low cost, high availability swarm system that could be printed and assembled multiple times without special knowledge or hardware skills.

# Authors:
- [Paulo Rezeck](https://github.com/rezeck)
- [Hector Azpurua](https://github.com/h3ct0r)

# Dependencies
- ROS Kinect
- AR Alvar Tracker
- Rosserial
- Arduino IDE (to install the firmware)

# How to install HeRo driver node
- Using git (or download the zip file) clone this repository into ros workspace.
- Compile with: 
```
$ catkin_make
```
- Fixing package dependencies:
```
$ rosdep install hero_driver
```

# How to install the firmware
- Open the arduino IDE.
- Go to preferences:
 - Change the sketchbook location to access the folder firmware.
 - Add (http://arduino.esp8266.com/stable/package_esp8266com_index.json) to Additional Boards Manager URLS and restart the IDE.
- Go to Sketchbook/hero/firware

## Robots Firmware
- Open the robot code inside the sketchbook.
- Change the essid and password parameter to acess the ROS master.
- Set an ID for each robot.
- Connect HeRo at USB and upload the code.

# How to start the ROS node

- Run the swarm_node.launch file with:
```
$ roslaunch hero_driver hero_node.launch
```
- Turn on the robots.

## Teleop Demo
- Run the hero_teleop.launch file to control it and set the specific robot id:
```
$ roslaunch swarm_driver swarm_teleop.launch robot_id:=1
```
