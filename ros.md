---
layout: page
title: ROS
permalink: /ros/
---

## Network Setup
In order to remotely operate the robots by using ROS middleware, you need to set on the robot the network credentials where it should conect and also the IP address of the computer running ROS, so called ROSMaster IP and Port. Here, there many alternatives such as create access point (hotspot) on your computer, or using a router.

> HeRo WiFi only works with 2.4GHz network.

## Setting HeRo Network Credentials, Name, Etc.
The robot firmware has two operation mode: config mode (works as a server for a web configuration page) and ros mode. 
In this stage you need to start the robots into **config mode**.

Turn on Hero while all sensors are covered, the RGB Led will be flashing pink.
![image](https://user-images.githubusercontent.com/14208261/188984464-a642f4ca-eccd-42a8-a5de-ba6c5ceef6fb.png)

In this config mode the robot will work as an WIFI access point. 
Now, uses your computer or smartphone to connect to this WIFI access point.
- ESSID: HERO_ROBOT_*****
- Password: s3cr3tp4ss

![image](https://user-images.githubusercontent.com/14208261/188985377-c601eed2-55ee-4b30-83ae-48a2ab747848.png)

Open this link in your web browser http://192.168.4.1/ and set the network credentials where the robot should connect.
![image](https://user-images.githubusercontent.com/14208261/188985741-89d5bb6e-dc7a-4a43-aa26-55446060de00.png)

![image](https://user-images.githubusercontent.com/14208261/188985952-9429cf34-2c73-4fb4-9175-931fcb21fc47.png)

![image](https://user-images.githubusercontent.com/14208261/188986050-c08518bc-2560-44c5-93df-190dc329232d.png)

Save and turn off HeRo.

# Connecting HeRo to and your computer
After properly set the network credentials on the robot, it should connect automatically in the network. The robot will blink blue for 2 seconds if it connected to the network, otherwise it will keep blink in red.

![output](https://user-images.githubusercontent.com/14208261/188990277-4e2ba79e-3ec1-473e-b82d-8a4eaccbc45a.gif)

Once HeRo is connected with your computer, you won't need to configure it again. (Just if you change your computer's WIFI configuration). So, everytime you want to use HeRo you must just make sure that the network access point is up.

<!-- - Create a hotspot in your computer, follow this guide https://www.how2shout.com/how-to/2-ways-to-create-wifi-hotspot-in-ubuntu-20-04-lts-focal-fossa.html

- In Ubuntu 20.04 there are some bugs when you try to create a hotspot for the first time, maybe it will be blocked like it is in the screenshot. To resolve this you just need to change tabs in Settings, for example click in Network and then click back in Wifi.
<img src="https://github.com/verlab/hero_common/raw/master/hero_resources/media/images/hero_hotspotbug.png" width="800">

- Run ifconfig to get your IP
<img src="https://github.com/verlab/hero_common/raw/master/hero_resources/media/images/hero_ifconfig.png" width="800">
<img src="https://github.com/verlab/hero_common/raw/master/hero_resources/media/images/hero_inet.png" width="800">

- Turn off hotspot

- Turn on Hotspot

- Turn on Hero. Hero will be flashing red. If it was configured correctly, it will flash Blue and the RGB Led will turn off. The following video shows how this process works in practice.
[Video] -->

<!-- - Once Hero is connected with your computer, you won't need to configure it again. (Just if you change your computer's WIFI hotspot configuration). So, everytime you want to use Hero you must turn on your computer's WIFI hotspot. -->


# How to start a ROS Node
Run the ```hero_bringup.launch``` file with: (keep it running)
```sh
$ roslaunch hero_bringup hero_bringup.launch
```

Turn on the Robot(s). You will note some verbose messages on terminal. If everthings is fine, you will see a similiar result as the image bellow.

![image](https://user-images.githubusercontent.com/14208261/188991513-8f5b1816-d9cd-4dee-93d9-0f929c70323f.png)

## Available Topics
```sh
rostopic list
/hero_0/cmd_motor # command each motor PWM
/hero_0/encoder # encoder feedback
/hero_0/imu # gyro, acc, orientation estimation
/hero_0/laser # 8 IR distance sensor
/hero_0/led # top rgb leds command
/hero_0/odom # odometry estimation
/hero_0/position_controller/cmd_vel # position controller commands
/hero_0/velocity_controller/cmd_vel # velocity controller commands
/rosout
/rosout_agg
/tf # full HeRo tf tree
```

## Available Services
```
$ rosservice list
/hero_3/pid_calibration
/hero_3/set_frequency
/hero_3/set_odom
/hero_3/set_pid_parameters
```

## Teleop Demo
- In another terminal, run hero_teleop.launch file to move Hero around, you must set the specific robot id:
- 
```
$ roslaunch hero_bringup hero_teleop.launch id:=0
```
![output](https://user-images.githubusercontent.com/14208261/188993419-52fea191-6da7-48d5-9ff6-0117f13973f2.gif)
