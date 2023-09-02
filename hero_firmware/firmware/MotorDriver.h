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
 
#ifndef __MOTOR_DRIVER_H__
#define __MOTOR_DRIVER_H__

/* ROS Library */
#define ROSSERIAL_ARDUINO_TCP
#include <ros.h>

#include <Servo.h>                      /* https://www.arduino.cc/en/Reference/Servo */
#include <EEPROM.h>                     /* https://www.arduino.cc/en/Reference/EEPROM */


/* Message types */
#include <hero_common/Motor.h>
#include <hero_common/SetMotor.h>

#define MEM_INIT_POS_MOTOR_POSITION 100
#define MEM_ALOC_SIZE 512

class MotorDriver {
  private:
    ros::NodeHandle *nh_;
    String heroName;

    /* Motor PWM Callback */
    String motorTopic;                                            /* Topic name */
    ros::Subscriber<hero_common::Motor, MotorDriver> *motorSub;   /* Subscriber */

    /* Set Motor deadzone PWM */
    String setMotorTopic; 
    ros::ServiceServer<hero_common::SetMotor::Request, hero_common::SetMotor::Response, MotorDriver> *setMotorService;    /* Service Type */

    /* Motor Configuration */
    Servo leftMotor; /* Left Motor Control */
    Servo rightMotor; /* Right Motor Control */

    bool pwm_only = false;
    
    unsigned long watchdogTimer = 0;
    unsigned long rate = 20, timer;

    char stream[100];

  public:
    int leftMotorDeadzone = MOTOR_LEFT_HALT_PWM;
    int rightMotorDeadzone = MOTOR_RIGHT_HALT_PWM;
  
    MotorDriver(unsigned long rate);
    void init(void);
    void init(ros::NodeHandle &nh, String heroName);
    void update();
    void update(unsigned long rate);
    void compute();
    void controlMotorWithStiffness(Servo &servo, int motorCmd);
    void command (int leftMotorCmd, int rightMotorCmd);
    void halt ();

    void setRate(unsigned long rate);
    void readSensor();

    /* Callback function */
    void motorCallback(const hero_common::Motor& msg);
    void setMotorCallback(const hero_common::SetMotor::Request& req, hero_common::SetMotor::Response& res);
};


#endif
