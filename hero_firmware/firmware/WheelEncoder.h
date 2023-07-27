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
 
#ifndef __WHEEL_ENCODER_H__
#define __WHEEL_ENCODER_H__

/* ROS Library */
#define ROSSERIAL_ARDUINO_TCP
#include <ros.h>

/* Message types */
#include <hero_common/Encoder.h>

#include <Encoder.h>                    /* https://github.com/PaulStoffregen/Encoder */
#include <SimpleKalmanFilter.h>         /* https://github.com/denyssene/SimpleKalmanFilter */

#define INPUT_PULLUP            /* Enable internal pull-up resistor */
#define ENCODER_USE_INTERRUPTS  /* Uses interruption to count the encoders ticks */

class WheelEncoder {
  private:
    ros::NodeHandle *nh_;
    String heroName;
    /* Encoder publisher */
    hero_common::Encoder encoderMessage;    /* Message Type */
    String encoderTopic;                    /* Topic name */
    ros::Publisher *encoderPub;             /* Publisher */
    String encoderFrame;                    /* Encoder link frame */
    unsigned long readTimer = 0;            /* Last time sensor was read */ 
    unsigned long rate = 20, timer;         /* Update frequency */

    Encoder *leftEncoder;           /* Left Encoder Configuration */
    Encoder *rightEncoder;          /* Right Encoder Configuration */
    SimpleKalmanFilter *leftKF;
    SimpleKalmanFilter *rightKF;
    long motorPositionRight = 0;    /* Motor position */
    long motorPositionLeft = 0;

  public:
    WheelEncoder(unsigned long rate);
    void init(void);
    void init(ros::NodeHandle &nh, String heroName);
    void update(void);
    void update(unsigned long rate);
    long getLeftEncoderTicks(void);
    long getRightEncoderTicks(void);

    void clear(void);
    void setRate(unsigned long rate);
    void readSensor(void);

    hero_common::Encoder getMessage(void);
};


#endif
