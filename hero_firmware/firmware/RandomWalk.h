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
 
#ifndef __RANDOM_WALK_H__
#define __RANDOM_WALK_H__

/* ROS Library */
#define ROSSERIAL_ARDUINO_TCP
#include <ros.h>

#include "VelocityControl.h"
#include "RangeSensor.h"
#include "LEDStatus.h"

#include <geometry_msgs/Twist.h>
#include <std_msgs/ColorRGBA.h>

class RandomWalkDemo {
  private:
    
    float p0 = 0.15; // Maximal sensor distance (in meters)
    float max_speed = 0.10; // Maximal speed of the robot (in meters/s)
    float theta_factor = 120.0; // angular speed factor

    VelocityControl *velocityControl;
    RangeSensor *rangeSensor;
    LEDStatus *ledStatus;
    
    unsigned long watchdogTimer = 0;
    unsigned long rate = 20, timer;

    char stream[100];

  public:
    
    RandomWalkDemo(unsigned long rate);
    void init(VelocityControl &velocityControl, RangeSensor &rangeSensor, LEDStatus &ledStatus);
    void update();
    void update(unsigned long rate);
    void halt ();

    void setRate(unsigned long rate);
};


#endif
