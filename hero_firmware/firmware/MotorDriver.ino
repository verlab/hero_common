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
#include "config.h"
#include <math.h>

static_assert(sizeof(MOTOR_P) == 10, "MOTOR_P EEPROM layout must stay 10 bytes (PID @ 110)");

MotorDriver::MotorDriver(unsigned long rate) {
  this->nh_ = nullptr;
  this->leftMotor.detach();
  this->rightMotor.detach();
  delayMicroseconds(3000);
  this->halt();
  this->timer = millis();
  this->lastRampMs = 0;
  this->setRate(rate);

  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.get(MEM_INIT_POS_MOTOR_POSITION, motorData);
  EEPROM.end();

  this->applyMotorDataFromGlobals();
}

void MotorDriver::applyMotorDataFromGlobals(void) {
  if ((motorData.leftMotorDeadzone > 1000) && (motorData.leftMotorDeadzone < 2000)) {
    this->leftMotorDeadzone = motorData.leftMotorDeadzone;
  }
  if ((motorData.rightMotorDeadzone > 1000) && (motorData.rightMotorDeadzone < 2000)) {
    this->rightMotorDeadzone = motorData.rightMotorDeadzone;
  }

  uint16_t r = motorData.pwm_ramp_us_per_s;
  if (r == 0 || r == 0xFFFF) {
    r = MOTOR_PWM_DEFAULT_RAMP_US_S;
  } else if (r <= 1000) {
    /* Legacy stiffness-permille field: map to a usable ramp rate (µs/s). */
    r = (uint16_t)(400u + (unsigned)r * 7u);
  }
  if (r < MOTOR_PWM_RAMP_MIN_US_S) r = MOTOR_PWM_RAMP_MIN_US_S;
  if (r > MOTOR_PWM_RAMP_MAX_US_S) r = MOTOR_PWM_RAMP_MAX_US_S;
  this->pwmRampUsPerS = r;
}

void MotorDriver::init(void) {
}

void MotorDriver::init(ros::NodeHandle& nh, String heroName) {
  this->nh_ = &nh; /* ROS Node Handle */
  this->heroName = heroName;

  this->motorTopic = this->heroName + String("/cmd_motor");
  this->motorSub = new ros::Subscriber<hero_common::Motor, MotorDriver>(this->motorTopic.c_str(), &MotorDriver::motorCallback, this);
  this->nh_->subscribe(*this->motorSub);

  this->setMotorTopic = this->heroName + String("/motors_parameters");
  this->setMotorService = new ros::ServiceServer<hero_common::SetMotor::Request, hero_common::SetMotor::Response, MotorDriver>(this->setMotorTopic.c_str(), &MotorDriver::setMotorCallback, this);
  this->nh_->advertiseService(*this->setMotorService);
}

int MotorDriver::stepToward(int current, int target, int maxStep) {
  int d = target - current;
  if (d == 0) return current;
  if (abs(d) <= maxStep) return target;
  return current + (d > 0 ? maxStep : -maxStep);
}

void MotorDriver::processRamp(void) {
  bool L = this->leftMotor.attached();
  bool R = this->rightMotor.attached();
  if (!L && !R) {
    this->lastRampMs = millis();
    return;
  }

  unsigned long now = millis();
  unsigned long dt = now - this->lastRampMs;
  if (this->lastRampMs == 0) dt = 1;
  this->lastRampMs = now;
  if (dt > 400) dt = 400;

  long maxStep = (long)this->pwmRampUsPerS * (long)dt / 1000L;
  if (maxStep < 1L) maxStep = 1L;
  int ms = (int)maxStep;

  if (L) {
    this->leftActualUs = MotorDriver::stepToward(this->leftActualUs, this->leftTargetUs, ms);
    this->leftMotor.writeMicroseconds(this->leftActualUs);
  }
  if (R) {
    this->rightActualUs = MotorDriver::stepToward(this->rightActualUs, this->rightTargetUs, ms);
    this->rightMotor.writeMicroseconds(this->rightActualUs);
  }
}

void MotorDriver::command(int leftMotorCmd, int rightMotorCmd) {
  this->leftTargetUs = constrain(leftMotorCmd, 1000, 2000);
  this->rightTargetUs = constrain(rightMotorCmd, 1000, 2000);

  if (!this->leftMotor.attached()) {
    this->leftMotor.attach(MOTOR_LEFT);
    int rd = this->leftMotor.readMicroseconds();
    this->leftActualUs = (rd >= 1000 && rd <= 2000) ? rd : this->leftMotorDeadzone;
  }
  if (!this->rightMotor.attached()) {
    this->rightMotor.attach(MOTOR_RIGHT);
    int rd = this->rightMotor.readMicroseconds();
    this->rightActualUs = (rd >= 1000 && rd <= 2000) ? rd : this->rightMotorDeadzone;
  }

  this->processRamp();
  this->watchdogTimer = millis();
}

void MotorDriver::halt() {
  if (this->leftMotor.attached()) this->leftMotor.detach();
  if (this->rightMotor.attached()) this->rightMotor.detach();
  delayMicroseconds(1000);
  this->leftActualUs = this->leftMotorDeadzone;
  this->rightActualUs = this->rightMotorDeadzone;
  this->leftTargetUs = this->leftActualUs;
  this->rightTargetUs = this->rightActualUs;
  this->lastRampMs = 0;
}

void MotorDriver::setRate(unsigned long rate) {
  this->rate = rate;
}

void MotorDriver::update() {
  this->update(this->rate);
}

void MotorDriver::update(unsigned long rate) {
  this->processRamp();

  if (this->autoHaltEnabled && (millis() - this->timer) > (1000 / rate) && (millis() - this->watchdogTimer) > 1000) {
    this->halt();
    this->timer = millis();
  }
}

void MotorDriver::motorCallback(const hero_common::Motor& msg) {
  this->command((int)msg.left_motor_pwm, (int)msg.right_motor_pwm);
}

void MotorDriver::setMotorCallback(const hero_common::SetMotor::Request& req, hero_common::SetMotor::Response& res) {
  motorData.leftMotorDeadzone = req.left_motor_pwm;
  motorData.rightMotorDeadzone = req.right_motor_pwm;

  sprintf(this->stream, "\33[92m[%s] Recording values in the flash... \33[0m", this->heroName.c_str());
  this->nh_->loginfo(this->stream);

  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.put(MEM_INIT_POS_MOTOR_POSITION, motorData);
  EEPROM.end();

  sprintf(this->stream, "\33[92m[%s] Motor Parameters has been succesfully recorded! \33[0m", this->heroName.c_str());
  this->nh_->loginfo(this->stream);
  res.success = 1;
  res.message = "Motor Parameters has been succesfully recorded!";
  this->applyMotorDataFromGlobals();
}
