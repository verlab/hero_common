/*
  ******************************************************************************
                      H E R O   F I R M W A R E
  ******************************************************************************
  Paulo Rezeck        <rezeck@dcc.ufmg.br>
  Mauricio Ferrari    <mauferrari@dcc.ufmg.br>
  Hector Azpurua      <hectorxxx@gmail.com>


                Computer Vision and Robotics Lab (VeRLab)
               Universidade Federal de Minas Gerais - Brazil
  ******************************************************************************
  Copyright (c) 2021 Paulo Rezeck.  All right reserved.
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  ******************************************************************************/

/* ESP Library */
#include <ESP8266WiFi.h>

/* ROS Library */
#define ROSSERIAL_ARDUINO_TCP
#include <ros.h>

/* Libraries */
#include "config.h"

#include "LEDStatus.h"
LEDStatus ledStatus(20);

#include "WebConfig.h"
WebConfig webConfig(4);

#include "ROSHandle.h"
ROSHandle rosHandle(SYNC_RATE, 1);

#include "RangeSensor.h"
RangeSensor rangeSensor(10);

#include "WheelEncoder.h"
WheelEncoder wheelEncoder(30);

#include "IMUSensor.h"
IMUSensor imuSensor(20);

#include "Odometry.h"
Odometry odometry(30);

#include "MotorDriver.h"
MotorDriver motorDriver(20);

#include "PositionControl.h"
PositionControl positionControl(20);

#include "VelocityControl.h"
VelocityControl velocityControl(20);


/* Main Setup */
void setup() {
  /* Stopping Motors */
  pinMode(MOTOR_RIGHT, OUTPUT);
  pinMode(MOTOR_LEFT, OUTPUT);
  digitalWrite(MOTOR_RIGHT, LOW);
  digitalWrite(MOTOR_LEFT, LOW);
  /* Setup laser Readings */
  rangeSensor.connect();
  /* Cover all the range sensor to enable web config mode */
  config_mode = rangeSensor.configModeCheck();
  /* Clean status led */
  ledStatus.reset();
  if (config_mode) {
    /* Create an AP that enables the user to setup some parameter of the robot. See config_via_wifi.h. */
    webConfig.init(ledStatus);
  }
  else {
    /* Setup ROS Communication */
    rosHandle.init(ledStatus);

    /* Setup LED to communicate with ROS */
    ledStatus.init(rosHandle.nh, rosHandle.heroName);
    /* Setup range sensor to communicate with ROS */
    rangeSensor.init(rosHandle.nh, rosHandle.heroName);
    /* Setup imu sensor to communicate with ROS */
    imuSensor.init(rosHandle.nh, rosHandle.heroName);
    /* Setup wheel encoder sensor to communicate with ROS */
    wheelEncoder.init(rosHandle.nh, rosHandle.heroName);

    /* Compute odometry to send with ROS */
#ifdef __IMU_SENSOR_H__
    odometry.init(rosHandle.nh, rosHandle.heroName, wheelEncoder, imuSensor);
#else
    odometry.init(rosHandle.nh, rosHandle.heroName, wheelEncoder);
#endif
    /* Setup motors to communicate with ROS */
    motorDriver.init(rosHandle.nh, rosHandle.heroName);


    /* Compute position control to by receving commands from ROS */
    positionControl.init(rosHandle.nh, rosHandle.heroName, motorDriver, wheelEncoder);
    /* Compute velocity control to by receving commands from ROS */
    velocityControl.init(rosHandle.nh, rosHandle.heroName, motorDriver, wheelEncoder);

    ledStatus.welcome(*ledStatus.cyan, 100);
  }
}


/* Main loop */
void loop() {
  if (config_mode) { // Web Configuration Mode
    webConfig.update();
  }
  else if (rosHandle.connected()) { // ROS Mode
    /* Get data from sensor and send it to ROS */
    motorDriver.update(2);
    rangeSensor.update(20);
    imuSensor.update(30);
    ledStatus.update(2);
    odometry.update(30);
    wheelEncoder.update(30);
    positionControl.update(50);
    velocityControl.update(50);

    rosHandle.sync();
  } else {
    delayMicroseconds(50000);
    rosHandle.sync();
  }
}
