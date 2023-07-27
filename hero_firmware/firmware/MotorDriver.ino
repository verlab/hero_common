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

#include "MotorDriver.h"


MotorDriver::MotorDriver(unsigned long rate) {
  /* Initiate Motors */
  this->leftMotor.detach();
  this->rightMotor.detach();
  delayMicroseconds(3000);
  this->halt();
  this->timer = millis();
  this->setRate(rate);

  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.get(MEM_INIT_POS_MOTOR_POSITION, motorData);
  EEPROM.end();
  
  if ((motorData.leftMotorDeadzone > 1000) && (motorData.leftMotorDeadzone < 2000)) {
    this->leftMotorDeadzone = motorData.leftMotorDeadzone;
  }

  if ((motorData.rightMotorDeadzone > 1000) && (motorData.rightMotorDeadzone < 2000)) {
    this->rightMotorDeadzone = motorData.rightMotorDeadzone;
  }
}

void MotorDriver::init(void){
  
}

void MotorDriver::init(ros::NodeHandle &nh, String heroName) {
  this->nh_ = &nh;   /* ROS Node Handle */
  this->heroName = heroName;

  /* Address motor pwm subscribe */
  this->motorTopic = this->heroName + String("/cmd_motor");                                                      /* Update topic name */
  this->motorSub = new ros::Subscriber<hero_common::Motor, MotorDriver>(this->motorTopic.c_str(), &MotorDriver::motorCallback, this);        /* Instantiate subscriber */
  this->nh_->subscribe(*this->motorSub);                                                                                                  /* Address set odom service */

  /* Address set PID motors service */
  this->setMotorTopic = this->heroName + String("/motors_parameters");                                                                                                 /* Update service name */
  this->setMotorService = new ros::ServiceServer<hero_common::SetMotor::Request, hero_common::SetMotor::Response, MotorDriver>(this->setMotorTopic.c_str(), &MotorDriver::setMotorCallback, this);               /* Instantiate service */
  this->nh_->advertiseService(*this->setMotorService);                                                                                                                          /* Address fix motors service */
}

void MotorDriver::command (int leftMotorCmd, int rightMotorCmd) {
  if (!this->leftMotor.attached()) this->leftMotor.attach(MOTOR_LEFT);
  if (!this->rightMotor.attached()) this->rightMotor.attach(MOTOR_RIGHT);
  this->leftMotor.writeMicroseconds(leftMotorCmd);
  this->rightMotor.writeMicroseconds(rightMotorCmd);
  delayMicroseconds(500);
  this->watchdogTimer = millis();
}

void MotorDriver::halt () {
  if (this->leftMotor.attached()) this->leftMotor.detach();
  if (this->rightMotor.attached()) this->rightMotor.detach();
  delayMicroseconds(1000);
}

void MotorDriver::setRate(unsigned long rate) {
  this->rate = rate;
}

void MotorDriver::update() {
  this->update(this->rate);
}

/* Motor update */
void MotorDriver::update(unsigned long rate) {
  if ((millis() - this->timer) > (1000 / rate) && (millis() - this->watchdogTimer) > 1000) {
    this->halt();
    this->timer = millis();
  }
}

/* Set motor pwm */
void MotorDriver::motorCallback(const hero_common::Motor& msg) {
  this->command((int)msg.left_motor_pwm, (int)msg.right_motor_pwm);
}

/* Set Motor parameters for both motors */
void MotorDriver::setMotorCallback(const hero_common::SetMotor::Request& req, hero_common::SetMotor::Response& res) {
  motorData.leftMotorDeadzone = req.left_motor_pwm;
  motorData.rightMotorDeadzone = req.right_motor_pwm;
  
  this->leftMotorDeadzone = req.left_motor_pwm;
  this->rightMotorDeadzone = req.right_motor_pwm;

  sprintf(this->stream, "\33[92m[%s] Recording values in the flash... \33[0m", this->heroName.c_str());
  this->nh_->loginfo(this->stream);

  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.put(MEM_INIT_POS_MOTOR_POSITION, motorData);
  EEPROM.end();

  sprintf(this->stream,  "\33[92m[%s] Motor Parameters has been succesfully recorded! \33[0m", this->heroName.c_str());
  this->nh_->loginfo(this->stream);
  res.success = 1;
  res.message = "Motor Parameters has been succesfully recorded!";
}
