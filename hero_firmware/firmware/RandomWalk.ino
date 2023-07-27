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

#include "RandomWalk.h"


RandomWalkDemo::RandomWalkDemo(unsigned long rate) {
  this->timer = millis();
  this->setRate(rate);
}

void RandomWalkDemo::init(VelocityControl &velocityControl, RangeSensor &rangeSensor, LEDStatus &ledStatus) {
  this->velocityControl = &velocityControl;
  this->rangeSensor = &rangeSensor;
  this->ledStatus = &ledStatus;
}

void RandomWalkDemo::halt() {
  //parar motors
}

void RandomWalkDemo::setRate(unsigned long rate) {
  this->rate = rate;
}

void RandomWalkDemo::update() {
  this->update(this->rate);
}

/* Control update */
void RandomWalkDemo::update(unsigned long rate) {
  if ((millis() - this->timer) > (1000 / rate) && (millis() - this->watchdogTimer) > 1000) {
    std_msgs::ColorRGBA msg;
    msg.r = 0.0;  // Red component
    msg.g = 1.0;  // Green component
    msg.b = 1.0;  // Blue component
    msg.a = 1.0;  // Alpha (brightness) component

    geometry_msgs::Twist cmd_vel;
    cmd_vel.linear.x = 0.06;
    cmd_vel.angular.z = 0.0;  

    // Get current Range Sensor
    this->rangeSensor->readSensor();

    // all side blocked BBB -> turn left
    if ((this->rangeSensor->getMessage().ranges[10] < this->p0) && (this->rangeSensor->getMessage().ranges[8] < this->p0) && (this->rangeSensor->getMessage().ranges[6] < this->p0)) {
      cmd_vel.angular.z = 0.05 * this->theta_factor;
      cmd_vel.linear.x = 0.02;
      msg.r = 1.0;  // Red component
      msg.g = 0.0;  // Green component
      msg.b = 0.0;  // Blue component
    }
    // left & front blocked (BBL) -> turn right
    else if ((this->rangeSensor->getMessage().ranges[10] < this->p0) && (this->rangeSensor->getMessage().ranges[8] < this->p0) && (this->rangeSensor->getMessage().ranges[6] >= this->p0)) {
      cmd_vel.angular.z = -0.03 * this->theta_factor;
      cmd_vel.linear.x = 0.02;
      msg.r = 1.0;  // Red component
      msg.g = 0.0;  // Green component
      msg.b = 0.0;  // Blue component
    }
    // left & right blocked (BLB)-> turn left
    else if ((this->rangeSensor->getMessage().ranges[10] < this->p0) && (this->rangeSensor->getMessage().ranges[8] >= this->p0) && (this->rangeSensor->getMessage().ranges[6] < this->p0)) {
      cmd_vel.angular.z = 0.05 * this->theta_factor;
      cmd_vel.linear.x = 0.02;
      msg.r = 1.0;  // Red component
      msg.g = 0.0;  // Green component
      msg.b = 0.0;  // Blue component
    }
    // front blocked (LBL)-> turn left
    else if ((this->rangeSensor->getMessage().ranges[10] >= this->p0) && (this->rangeSensor->getMessage().ranges[8] < this->p0) && (this->rangeSensor->getMessage().ranges[6] >= this->p0)) {
      cmd_vel.angular.z = 0.03 * this->theta_factor;
      cmd_vel.linear.x = 0.02;
      msg.r = 1.0;  // Red component
      msg.g = 0.0;  // Green component
      msg.b = 0.0;  // Blue component
    }
    // all free (LLL) -> forward
    else if ((this->rangeSensor->getMessage().ranges[10] >= this->p0) && (this->rangeSensor->getMessage().ranges[8] >= this->p0) && (this->rangeSensor->getMessage().ranges[6] >= this->p0)) {
      cmd_vel.angular.z = 0.0 * this->theta_factor;
    }
    // right blocked (BLL) -> turn right
    else if ((this->rangeSensor->getMessage().ranges[10] < this->p0 && this->rangeSensor->getMessage().ranges[8] >= this->p0 && this->rangeSensor->getMessage().ranges[6] >= this->p0)) {
      cmd_vel.angular.z = -0.01 * this->theta_factor;
      cmd_vel.linear.x = 0.02;
      msg.r = 1.0;  // Red component
      msg.g = 0.0;  // Green component
      msg.b = 0.0;  // Blue component
    }
    // right blocked (LBB) -> turn left
    else if ((this->rangeSensor->getMessage().ranges[10] >= this->p0 && this->rangeSensor->getMessage().ranges[8] < this->p0 && this->rangeSensor->getMessage().ranges[6] < this->p0)) {
      cmd_vel.angular.z = 0.03 * this->theta_factor;
      cmd_vel.linear.x = 0.02;
      msg.r = 1.0;  // Red component
      msg.g = 0.0;  // Green component
      msg.b = 0.0;  // Blue component
    }
    // left blocked (LLB) -> turn left
    else if ((this->rangeSensor->getMessage().ranges[10] >= this->p0 && this->rangeSensor->getMessage().ranges[8] >= this->p0 && this->rangeSensor->getMessage().ranges[6] < this->p0)) {
      cmd_vel.angular.z = 0.01 * this->theta_factor;
      cmd_vel.linear.x = 0.02;
      msg.r = 1.0;  // Red component
      msg.g = 0.0;  // Green component
      msg.b = 0.0;  // Blue component
    }

    // send velocity command
    this->velocityControl->cmdvelCallback(cmd_vel);
    // send led status command
    this->ledStatus->ledCallback(msg);

    this->timer = millis();
  }
}
