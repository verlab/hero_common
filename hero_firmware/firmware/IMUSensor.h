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

#ifndef __IMU_SENSOR_H__
#define __IMU_SENSOR_H__

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h" /* https://playground.arduino.cc/Main/MPU-6050 */
#include "Wire.h" /* Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation */

/* ROS Library */
#define ROSSERIAL_ARDUINO_TCP
#include <ros.h>

/* Message types */
#include <sensor_msgs/Imu.h>

class IMUSensor {
  private:
    ros::NodeHandle *nh_;
    String heroName;
    /* IMU publisher */
    sensor_msgs::Imu imuMessage;  /* Message Type */
    String imuTopic;          /* Topic name */
    ros::Publisher *imuPub;   /* Publisher */
    String imuFrame;          /* Laser link frame */
    unsigned long rate = 20, timer;

    /* IMU I2C Configuration */
    MPU6050 *mpu;
    /* MPU control/status vars */
    bool dmpReady = false;    /* set true if DMP init was successful */
    uint8_t mpuIntStatus;     /* holds actual interrupt status byte from MPU */
    uint8_t devStatus;        /* return status after each device operation (0 = success, !0 = error) */
    uint16_t packetSize;      /* expected DMP packet size (default is 42 bytes) */
    uint16_t fifoCount;       /* count of all bytes currently in FIFO */
    uint8_t fifoBuffer[64];   /* FIFO storage buffer */
    /* MPU orientation/motion vars */
    Quaternion q;           /* [w, x, y, z]         quaternion container */
    VectorInt16 aa;         /* [x, y, z]            accel sensor measurements */
    VectorInt16 gy;         /* [x, y, z]            gyro sensor measurements */
    VectorInt16 aaReal;     /* [x, y, z]            gravity-free accel sensor measurements */
    VectorInt16 aaWorld;    /* [x, y, z]            world-frame accel sensor measurements */
    VectorFloat gravity;    /* [x, y, z]            gravity vector */
    float ypr[3];           /* [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector */

    char stream[100];
    bool IMUSensorEnable = true;

  public:
    IMUSensor(unsigned long rate);
    void init(ros::NodeHandle &nh, String heroName);
    void update();
    void update(unsigned long rate);
    void enable(void);
    void disable(void);
    bool isEnable(void);
    void setRate(unsigned long rate);
    void readSensor();
    bool configModeCheck();
    float get(void);
};


#endif
