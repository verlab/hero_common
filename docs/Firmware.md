---
layout: page
title: Flash firmware
permalink: /firmware/
section: software
lead: Step 2 of 4. The sketch lives in hero_firmware/firmware and targets the ESP8266. You need the Arduino IDE (or PlatformIO) and the Silicon Labs USB-UART driver.
---

## 1. Arduino and USB driver

Install the latest Arduino IDE from the [Arduino website](https://www.arduino.cc/en/Main/Software).

The USB-UART chip needs the [Silicon Labs VCP driver](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers) for your OS. Linux often already has it.

## 2. ESP8266 board package

Open **File → Preferences**.

- Set the sketchbook location to the firmware folder in this repo.
- Add this URL to **Additional Boards Manager URLs**: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
- Restart the IDE.

![Arduino preferences](https://user-images.githubusercontent.com/14208261/188973944-474bb232-37c5-48e0-8865-7ba4c443a4ad.png)

Then **Tools → Boards → Boards Manager**, install **esp8266** version **2.5.0**.

![Boards Manager](https://user-images.githubusercontent.com/14208261/188975070-1a5e8aa5-92e0-4570-9a74-cf961a4afa0a.png)

Select **NodeMCU 1.0** and match the other Tools settings in this screenshot.

![Board settings](https://user-images.githubusercontent.com/14208261/188975934-1b4051b8-77d2-4751-98d3-de9e04f2cf72.png)

## 3. Upload the sketch

Open the robot sketch from the sketchbook.

![Open sketch](https://user-images.githubusercontent.com/14208261/188976507-afc0d992-4fb8-440e-9c5b-f0d023f4c159.png)

Static defaults live in `config.h` (Wi‑Fi, ROS master, robot id). Prefer the web configurator in the next step for network name and robot id — do not bake those into the sketch unless you have to.

![config.h](https://user-images.githubusercontent.com/14208261/188977085-3b0410be-4e94-402d-abeb-3569f74e4c5d.png)

Connect HeRo over USB and upload.

![Upload](https://user-images.githubusercontent.com/14208261/188977467-1ae30670-dd9a-4d02-bb2e-10f7f653d594.png)
