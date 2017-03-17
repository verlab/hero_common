# Swarm Robots Project (Verlab)
This project contributes to an open source ROS-based framework for swarm robotics.

# Dependencies
- ROS Kinect
- rosserial
- Arduino IDE (to install the firmware)

# How to install Swarm Robots Node
- Using git (or download the zip file) clone this repository into ros workspace.
- Compile with catkin_make.

# How to install the firmware
- Open the arduino IDE. 
- Go to preferences and change the sketchbook location to access the folder firmware (restart the IDE).
## Sink Firmware
- Open the sink code inside the sketchbook.
- Connect the sink usb device and upload the code.

## Robots Firmware
- Open the robot code inside the sketchbook.
- Change the ID variable to one that you want.
- Connect the robot via and upload the code.

# How to start the framework
- Run the swarm_node.launch file with:
```
$ roslaunch swarm_driver swarm_node.launch
```
 
# TODO LIST
- [ ] Add proximity sensors on robot.
- [ ] Build a small model of the robot.
- [ ] Implement a method to compute the odometry.
- [ ] ...
