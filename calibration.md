---
layout: page
title: Calibration
permalink: /calibration/
---

It is possible to calibrate some processes remotely using ROS services raised by the robot. Next, we list the calibration process for motors, controllers and distance sensors.

# Summary
- [Enter Configuration Mode](#Enter-Configuration-Mode)
- [Motor PWM Calibration](#Motor-PWM-Calibration)
- [Position Controller PID](#Position-Controller-PID)
- [Velocity Controller PID](#Velocity-Controller-PID)
- [IR Distance Sensor](#IR-Distance-Sensor)

# Enter Configuration Mode
To be able to access calibration mode, run launch file ```hero_confmode.launch``` instead of file ```hero_bringup.launch```.
```sh
$ roslaunch hero_bringup hero_confmode.launch
```

```sh
... logging to /home/rezeck/.ros/log/4d1fdafe-8eb9-11ed-b4a8-e454e82b3305/roslaunch-rezeck-28550.log
Checking log directory for disk usage. This may take a while.
Press Ctrl-C to interrupt
Done checking log file disk usage. Usage is <1GB.

xacro: in-order processing became default in ROS Melodic. You can drop the option.
Deprecated: xacro tag 'property' w/o 'xacro:' xml namespace prefix (will be forbidden in Noetic)
when processing file: /home/rezeck/catkin_ws/src/hero_common/hero_description/urdf/common.xacro
included from: /home/rezeck/catkin_ws/src/hero_common/hero_description/robot/hero.urdf.xacro
Use the following command to fix incorrect tag usage:
find . -iname "*.xacro" | xargs sed -i 's#<\([/]\?\)\(if\|unless\|include\|arg\|property\|macro\|insert_block\)#<\1xacro:\2#g'

started roslaunch server http://rezeck:39447/

SUMMARY
========

PARAMETERS
 * /description: <?xml version="1....
 * /hero_bringup/fork_server: False
 * /hero_bringup/port: tcp
 * /hero_bringup/tcp_port: 11411
 * /rosdistro: melodic
 * /rosversion: 1.14.13

NODES
  /
    hero_bringup (rosserial_python/serial_node.py)

auto-starting new master
process[master]: started with pid [28585]
ROS_MASTER_URI=http://localhost:11311

setting /run_id to 4d1fdafe-8eb9-11ed-b4a8-e454e82b3305
process[rosout-1]: started with pid [28607]
started core service [/rosout]
process[hero_bringup-2]: started with pid [28610]
[INFO] [1673116204.495423]: ROS Serial Python Node
[INFO] [1673116204.507878]: Fork_server is: False
[INFO] [1673116204.510605]: Waiting for socket connections on port 11411
[INFO] [1673116204.513295]: Waiting for socket connection
[INFO] [1673116211.760987]: Established a socket connection from 10.42.0.100 on port 53937
[INFO] [1673116211.764608]: calling startSerialClient
[INFO] [1673116213.872803]: Requesting topics...
[INFO] [1673116213.877849]: [/hero_2] Firmware: v3.5 | Hardware: v2.5 | Config: v2.3 | IP: 10.42.0.100 
[INFO] [1673116213.882569]: [/hero_2] IMU is not working or not connected! Error: 1
[INFO] [1673116213.887142]: [/hero_2] Conected at time 5970
[INFO] [1673116213.899679]: [/hero_2] Conected at time 6976
[INFO] [1673116214.092311]: Note: publish buffer size is 4096 bytes
[INFO] [1673116214.093081]: Setup publisher on /hero_2/laser [sensor_msgs/LaserScan]
[INFO] [1673116214.096119]: Setup service server on /hero_2/ir_calibration [hero_common/SetIRCalibration]
[INFO] [1673116214.098496]: Setup publisher on /hero_2/imu [sensor_msgs/Imu]
[INFO] [1673116214.101250]: Setup publisher on /hero_2/encoder [hero_common/Encoder]
[INFO] [1673116214.388237]: Setup publisher on /tf [tf/tfMessage]
[INFO] [1673116214.402824]: Setup publisher on /hero_2/odom [nav_msgs/Odometry]
[INFO] [1673116214.405288]: Setup service server on /hero_2/set_odom [hero_common/SetOdom]
[INFO] [1673116214.407618]: Setup service server on /hero_2/motors_parameters [hero_common/SetMotor]
[INFO] [1673116214.409854]: Setup service server on /hero_2/position_controller/pid_parameters [hero_common/SetPID]
[INFO] [1673116214.415074]: Setup service server on /hero_2/position_controller/pid_calibration [std_srvs/Trigger]
[INFO] [1673116214.417548]: Setup service server on /hero_2/velocity_controller/pid_parameters [hero_common/SetPID]
[INFO] [1673116214.420146]: Setup service server on /hero_2/velocity_controller/pid_calibration [std_srvs/Trigger]
[INFO] [1673116214.422874]: Note: subscribe buffer size is 4096 bytes
[INFO] [1673116214.423638]: Setup subscriber on /hero_2/led [std_msgs/ColorRGBA]
[INFO] [1673116214.428581]: Setup subscriber on /hero_2/cmd_motor [hero_common/Motor]
[INFO] [1673116214.432390]: Setup subscriber on /hero_2/position_controller/cmd_vel [geometry_msgs/Twist]
[INFO] [1673116214.437566]: Setup subscriber on /hero_2/velocity_controller/cmd_vel [geometry_msgs/Twist]
[INFO] [1673116214.911270]: [/hero_2] Conected at time 7978
```

After running the launch, verify that the robot has connected and that the following topics and services are available:
```sh
$ rostopic list 
```

```sh
/diagnostics
/hero_2/cmd_motor
/hero_2/encoder
/hero_2/imu
/hero_2/laser
/hero_2/led
/hero_2/odom
/hero_2/position_controller/cmd_vel
/hero_2/velocity_controller/cmd_vel
/rosout
/rosout_agg
/tf
```

```sh
$ rosservice list 
```

```sh
/hero_2/ir_calibration
/hero_2/motors_parameters
/hero_2/position_controller/pid_calibration
/hero_2/position_controller/pid_parameters
/hero_2/set_odom
/hero_2/velocity_controller/pid_calibration
/hero_2/velocity_controller/pid_parameters
/hero_bringup/get_loggers
/hero_bringup/set_logger_level
/rosout/get_loggers
/rosout/set_logger_level
```

# Motor PWM Calibration
The way to control the robot's motors is through the PWM technique, which allows controlling the voltage in the motor. The PWM range for the SG90 servo motor allows us to control the speed and direction of the wheel. In theory, the PWM range is 1000-2000 ms, and 1500 ms should have the motor stopped. In practice, this range can vary and does not have a linear behavior with respect to speed.

In this calibration step, we just need to find the PWM value at which the motor stops completely.

The best way to do this is to open the rqt viewer and configure it to visualize the wheel speed using the Plot tool and also open the easy message publisher tool, as in the figure below. Use this tool through the slide bar to send PWM commands to each motor. Try to position the slides so that the wheels are completely stopped and there is no jitter noise coming from the motors.

```sh
$ rosrun rqt_gui rqt_gui
```

![image](https://user-images.githubusercontent.com/14208261/211174037-2a12ac97-86a2-4b22-9e3a-a556d38cd640.png)

After finding these two values, use the following command to calibrate the motors. Use the values you found in this process.
```sh
$ rosservice call /hero_2/motors_parameters "left_motor_pwm: 1493 right_motor_pwm: 1448"
```
```sh
success: True
message: "Motor Parameters has been succesfully recorded!"
```


# Position Controller PID
After calibrating the motor PWM, we can calibrate the PID controller which will control the desired wheel position. This process is empirical and can be tuned using the following command:
```sh
$ rosservice call /hero_2/position_controller/pid_parameters "{lkp: 5.0, lki: 9.0, lkd: 0.1, rkp: 5.0, rki: 9.0, rkd: 0.1}"
```

```sh
success: True
message: "PID Parameters has been succesfully recorded!"
```
These values have a good response, so if you don't need to refine the controller, you can leave it as it is or try small variations.

# Velocity Controller PID
Similarly, we use a PID controller to control the speed of the robot's wheels. To tune the parameters, use the following command:
```sh
$ rosservice call /hero_2/velocity_controller/pid_parameters "{lkp: 1200.0, lki: 2300.0, lkd: 0.1, rkp: 1200.0, rki: 2300.0, rkd: 0.1}"
```

```sh
success: True
message: "PID Parameters has been succesfully recorded!"
```
These values have a good response, so if you don't need to refine the controller, you can leave it as it is or try small variations.

# IR Distance Sensor
