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

#ifndef __VELOCITY_CONTROL_H__
#define __VELOCITY_CONTROL_H__

/* ROS Library */
#define ROSSERIAL_ARDUINO_TCP
#include <ros.h>

/* Message types */
#include <geometry_msgs/Twist.h>
#include <hero_common/SetPID.h>
#include <std_srvs/Trigger.h>

/* Motor Position Control */
#include <PID_v1.h>                     /* http://playground.arduino.cc/Code/PIDLibrary */
#include <PID_AutoTune_v0.h>            /* https://playground.arduino.cc/Code/PIDAutotuneLibrary */
#include <EEPROM.h>                     /* https://www.arduino.cc/en/Reference/EEPROM */

#include "MotorDriver.h"
#include "WheelEncoder.h"

#define MEM_INIT_POS_PID_VELOCITY 110
#define MEM_ALOC_SIZE 512

/* Autotuner */
#define TUNE_STEP 80                  /* How far above and below the starting value will the output step? */
#define TUNE_NOISE 1              /* The autotune will ignore signal chatter smaller than this value this should be accurately set */
#define TUNE_LOOK_BACK 2              /* How far (seconds) back are we looking to identify peaks */
#define TUNE_STEADY_STATE_TIME 8000  /* Steady state time (ms) before pertubation */
#define TUNE_STEADY_STATE 130          /* Steady state PWM to start Autotune 0 - 100 should be ok*/

class VelocityControl {
  private:
    ros::NodeHandle *nh_;
    String heroName;
    
    MotorDriver *motorDriver;
    /* Encoder-base Odometry */
    WheelEncoder *wheelEncoder;

    /* Command Velocity-Position Callback */
    String cmdvelTopic;                                                 /* Topic name */
    ros::Subscriber<geometry_msgs::Twist, VelocityControl> *cmdvelSub;  /* Message type */

    /* Set PID parameters on both motors */
    ros::ServiceServer<hero_common::SetPID::Request, hero_common::SetPID::Response, VelocityControl> *setPIDService;          /* Service Type */
    String setPIDTopic;                                                                                  /* Service name */


    /* Autotune pid for motors */
    ros::ServiceServer<std_srvs::Trigger::Request, std_srvs::Trigger::Response, VelocityControl> *pidCalibrationService;         /* Service Type */
    String pidCalibrationTopic;                                                                             /* Service name */
   
    /* PID input and ouput */
    PID *leftMotorPID;
    PID *rightMotorPID;
    PID_ATune *leftMotorPIDTune;
    PID_ATune *rightMotorPIDTune;
    bool tuning = false;
    bool leftTuneDone = true;
    bool rightTuneDone = true;

    struct PID_CONFIG configVelPID;

    double leftMotorSetpoint = 0.0;
    double leftMotorInput = 0.0;
    double leftMotorOutput = 0.0;
    double leftMotorStartPos = 0.0;

    double rightMotorSetpoint = 0.0;
    double rightMotorInput = 0.0;
    double rightMotorOutput = 0.0;
    double rightMotorStartPos = 0.0;

    double output_lim = 250;
    double sample_time = 50000;
    unsigned long watchdog = 0;
    unsigned long rate = 20, timer;

    char stream[100];

  public:
    VelocityControl(unsigned long rate);
    void init(ros::NodeHandle &nh, String heroName, MotorDriver& motorDriver, WheelEncoder& wheelEncoder);
    void update();
    void update(unsigned long rate);

    void setRate(unsigned long rate);
    void reset(void);
    void resetLeftPID(void);
    void resetRightPID(void);

    void tunePID(void);

    /* Callback function */
    void cmdvelCallback(const geometry_msgs::Twist& msg);
    void setPIDCallback(const hero_common::SetPID::Request& req, hero_common::SetPID::Response& res);
    void pidCalibrationCallback(const std_srvs::Trigger::Request& req, std_srvs::Trigger::Response& res);   /* Callback function */
};

#endif
