---
layout: page
title: Connect a robot
permalink: /ros/
section: software
lead: Step 3 of 4. Each robot joins your 2.4 GHz network and talks to the ROS master over TCP. Set the SSID, the master IP, and a unique id — then it appears as /hero_N.
---

## 1. 2.4 GHz network

The computer that runs `roscore` is the ROS master. The robot needs that IP (port 11411 by default). A laptop hotspot or a lab router both work. HeRo Wi‑Fi is 2.4 GHz only.

## 2. Open the web configurator

The firmware has two modes: **config** (access-point + web page) and **ROS**. Start the robot in config mode.

Turn HeRo on with all IR sensors covered. The RGB LED flashes pink.

![Config mode](https://user-images.githubusercontent.com/14208261/188984464-a642f4ca-eccd-42a8-a5de-ba6c5ceef6fb.png)

The robot becomes a Wi‑Fi access point. Connect from a laptop or phone:

- ESSID: `HERO_ROBOT_*****`
- Password: `s3cr3tp4ss`

![Access point](https://user-images.githubusercontent.com/14208261/188985377-c601eed2-55ee-4b30-83ae-48a2ab747848.png)

Open [http://192.168.4.1/](http://192.168.4.1/) and set the network the robot should join, the ROS master IP, and the robot id.

![Configurator](https://user-images.githubusercontent.com/14208261/188985741-89d5bb6e-dc7a-4a43-aa26-55446060de00.png)

![Wi‑Fi fields](https://user-images.githubusercontent.com/14208261/188985952-9429cf34-2c73-4fb4-9175-931fcb21fc47.png)

![Save](https://user-images.githubusercontent.com/14208261/188986050-c08518bc-2560-44c5-93df-190dc329232d.png)

Save, then power the robot off.

## 3. Start the ROS master

After the credentials are saved, the robot joins that network on the next boot. A 2-second blue blink means it connected; red means it did not.

![Connection blink](https://user-images.githubusercontent.com/14208261/188990277-4e2ba79e-3ec1-473e-b82d-8a4eaccbc45a.gif)

You only need to configure it again if the Wi‑Fi or master IP changes. Keep the access point up whenever you use the robots.

Start the TCP rosserial server and leave it running:

```sh
$ roslaunch hero_bringup hero_bringup.launch
```

Turn the robots on. You should see connection messages like this.

![Bringup](https://user-images.githubusercontent.com/14208261/188991513-8f5b1816-d9cd-4dee-93d9-0f929c70323f.png)

## 4. Topics and services

```sh
$ rostopic list
/hero_0/cmd_motor
/hero_0/encoder
/hero_0/imu
/hero_0/laser
/hero_0/led
/hero_0/odom
/hero_0/position_controller/cmd_vel
/hero_0/velocity_controller/cmd_vel
/tf
```

```sh
$ rosservice list
/hero_0/pid_calibration
/hero_0/set_frequency
/hero_0/set_odom
/hero_0/set_pid_parameters
```

Drive one robot from another terminal (set the id):

```sh
$ roslaunch hero_bringup hero_teleop.launch id:=0
```

![Teleop](https://user-images.githubusercontent.com/14208261/188993419-52fea191-6da7-48d5-9ff6-0117f13973f2.gif)
