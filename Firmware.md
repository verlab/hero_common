---
layout: page
title: Firmware
permalink: /firmware/
---


## Burning HeRo firmware

### Arduino Installation
- Install the latest version from the [Arduino website](https://www.arduino.cc/en/Main/Software).
- The following driver is required in order to your computer communication with the HeRo microcontroller. It probably is already installed in Linux distribuition, but check if this before you start burning the firmware on the robot microcontroller. Download and install the properly [driver version](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers) for your OS.

### Setup ESP8266 board
First you need to update the board manager with a custom URL to enable Arduino IDE compile esp8266 mpu. 
Open up Arduino, then go to the Preferences (File > Preferences). 

- Change the sketchbook location to access the folder firmware.
- Add ```http://arduino.esp8266.com/stable/package_esp8266com_index.json``` to Additional Boards Manager URLS.
- Restart the IDE.

![image](https://user-images.githubusercontent.com/14208261/188973944-474bb232-37c5-48e0-8865-7ba4c443a4ad.png)

After restart the IDE, navigate to the Board Manager by going to (Tools > Boards > Boards Manager). There
should be a couple new entries in addition to the standard Arduino boards. Look for ```esp8266```.
Click on that entry, then select Install. You need to install 2.5.0 version of esp8266 library. 

![image](https://user-images.githubusercontent.com/14208261/188975070-1a5e8aa5-92e0-4570-9a74-cf961a4afa0a.png)


- The download process should take some minutes depending on your internet speed. After the
download is done, select NodeMCU 1.0 from the Tools tab and follow the other settings.

![image](https://user-images.githubusercontent.com/14208261/188975934-1b4051b8-77d2-4751-98d3-de9e04f2cf72.png)


## How to install the HeRo firmware
Open the robot code inside the sketchbook.
![image](https://user-images.githubusercontent.com/14208261/188976507-afc0d992-4fb8-440e-9c5b-f0d023f4c159.png)

All configuration parameters are available at config.h:
  - WiFi Essid and password for connection with ROS master
  - Robot ID
  
> You can change this parameters later by using the web interface.

![image](https://user-images.githubusercontent.com/14208261/188977085-3b0410be-4e94-402d-abeb-3569f74e4c5d.png)

- Connect HeRo at USB and upload the code.

![image](https://user-images.githubusercontent.com/14208261/188977467-1ae30670-dd9a-4d02-bb2e-10f7f653d594.png)
