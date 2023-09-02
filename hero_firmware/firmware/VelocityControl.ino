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

#include "VelocityControl.h"

VelocityControl::VelocityControl(unsigned long rate) {
  this->timer = millis();
  this->setRate(rate);

  /* Setup left Motor PID */
  this->leftMotorPID = new PID (&this->leftMotorInput, &this->leftMotorOutput, &this->leftMotorSetpoint, 1200.0, 2300.0, 0.1, 0, REVERSE); /* Motor PID */
  this->leftMotorPID->SetMode(AUTOMATIC);
  this->leftMotorPID->SetOutputLimits(-output_lim, output_lim);       /* Max output limit for left motor */
  this->leftMotorPID->SetSampleTime(sample_time);                     /* 10 microseconds */

  /* Setup autotuner for PID */
  this->leftMotorPIDTune = new PID_ATune(&this->leftMotorInput, &this->leftMotorOutput);    /* PID autotuner */
  this->leftMotorPIDTune->SetControlType(PID_ATune::SOME_OVERSHOOT_PID);    /* Set control type for autotuner */
  this->leftMotorPIDTune->SetNoiseBand(TUNE_NOISE);                         /* The autotune will ignore signal chatter smaller than this value this should be accurately set */
  this->leftMotorPIDTune->SetOutputStep(TUNE_STEP);                         /* How far above and below the starting value will the output step? */
  this->leftMotorPIDTune->SetLookbackSec((int)TUNE_LOOK_BACK);              /* How far back are we looking to identify peaks */

  /* Setup right Motor PID */
  this->rightMotorPID = new PID (&this->rightMotorInput, &this->rightMotorOutput, &this->rightMotorSetpoint, 1200.0, 2300.0, 0.1, 0, DIRECT); /* Motor PID */
  this->rightMotorPID->SetMode(AUTOMATIC);
  this->rightMotorPID->SetOutputLimits(-output_lim, output_lim);       /* Max output limit for left motor */
  this->rightMotorPID->SetSampleTime(sample_time);                     /* 10 microseconds */

  this->rightMotorPIDTune = new PID_ATune(&this->rightMotorInput, &this->rightMotorOutput);    /* PID autotuner */
  this->rightMotorPIDTune->SetControlType(PID_ATune::SOME_OVERSHOOT_PID);
  this->rightMotorPIDTune->SetNoiseBand(TUNE_NOISE);                        /* The autotune will ignore signal chatter smaller than this value this should be accurately set */
  this->rightMotorPIDTune->SetOutputStep(TUNE_STEP);                        /* How far above and below the starting value will the output step? */
  this->rightMotorPIDTune->SetLookbackSec((int)TUNE_LOOK_BACK);             /* How far back are we looking to identify peaks */

  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.get(MEM_INIT_POS_PID_VELOCITY, configVelPID);
  EEPROM.end();

  if (configVelPID.lkp > 0) {
    this->leftMotorPID->SetTunings(configVelPID.lkp, configVelPID.lki, configVelPID.lkd);
  }

  if (configVelPID.rkp > 0) {
    this->rightMotorPID->SetTunings(configVelPID.rkp, configVelPID.rki, configVelPID.rkd);
  }
}

void VelocityControl::init(MotorDriver& motorDriver, WheelEncoder& wheelEncoder) {
  this->motorDriver = &motorDriver;
  this->wheelEncoder = &wheelEncoder;
}

void VelocityControl::init(ros::NodeHandle &nh, String heroName, MotorDriver& motorDriver, WheelEncoder& wheelEncoder) {
  this->motorDriver = &motorDriver;
  this->wheelEncoder = &wheelEncoder;

  this->nh_ = &nh;   /* ROS Node Handle */
  this->heroName = heroName;

  /* Address command velocity-position subscribe */
  this->cmdvelTopic = this->heroName + String("/velocity_controller/cmd_vel");                          /* Update topic name */
  this->cmdvelSub = new ros::Subscriber<geometry_msgs::Twist, VelocityControl>(this->cmdvelTopic.c_str(), &VelocityControl::cmdvelCallback, this);     /* Instantiate subscriber */
  this->nh_->subscribe(*this->cmdvelSub);      /* Address Command Vel */

  /* Address set PID motors service */
  this->setPIDTopic = this->heroName + String("/velocity_controller/pid_parameters");                                                                                                 /* Update service name */
  this->setPIDService = new ros::ServiceServer<hero_common::SetPID::Request, hero_common::SetPID::Response, VelocityControl>(this->setPIDTopic.c_str(), &VelocityControl::setPIDCallback, this);               /* Instantiate service */
  this->nh_->advertiseService(*this->setPIDService);                                                                                                                          /* Address fix motors service */

  /* Address PID calibration service */
  this->pidCalibrationTopic = this->heroName + String("/velocity_controller/pid_calibration");                                                                                                     /* Update service name */
  this->pidCalibrationService = new ros::ServiceServer<std_srvs::Trigger::Request, std_srvs::Trigger::Response, VelocityControl>(this->pidCalibrationTopic.c_str(), &VelocityControl::pidCalibrationCallback, this);    /* Instantiate service */
  this->nh_->advertiseService(*this->pidCalibrationService);
}


void VelocityControl::setRate(unsigned long rate) {
  this->rate = rate;
}

void VelocityControl::update() {
  this->update(this->rate);
}

/* Update control loop and set the output to the motors */
void VelocityControl::update(unsigned long rate) {
  if (((millis() - this->timer) > (1000 / rate)) && ((millis() - this->watchdog) < 1000)) {
    /* Position-Control */
    this->wheelEncoder->readSensor();
    this->leftMotorInput = (double)this->wheelEncoder->getMessage().left_speed_filtered;
    this->rightMotorInput = (double)this->wheelEncoder->getMessage().right_speed_filtered;;
    if (this->tuning) {
      this->watchdog = millis();
      this->tunePID();
      sprintf(this->stream, "\33[93m[%s] Tunning Motor Set: [%f,%f], [%f,%f]->[%d,%d]\33[0m", this->heroName.c_str(), (float)this->leftMotorSetpoint, (float)this->rightMotorSetpoint, (float)this->leftMotorInput, (float)this->rightMotorInput, (int)this->leftMotorOutput, (int)this->rightMotorOutput);
      this->nh_->loginfo(this->stream);
    }
    else {
      this->leftMotorPID->Compute();
      this->rightMotorPID->Compute();

//      sprintf(this->stream, "\33[92m[%s] Motor Set: [%f,%f], [%f,%f]->[%d,%d]\33[0m", this->heroName.c_str(), (float)this->leftMotorSetpoint, (float)this->rightMotorSetpoint, (float)this->leftMotorInput, (float)this->rightMotorInput, (int)this->leftMotorOutput, (int)this->rightMotorOutput);
//      this->nh_->loginfo(this->stream);

      this->motorDriver->command((int)(this->leftMotorOutput) + (int)(this->motorDriver->leftMotorDeadzone), (int)(this->rightMotorOutput) + (int)(this->motorDriver->rightMotorDeadzone));
    }
    this->timer = millis();
  }
}

void VelocityControl::reset(void) {
  this->resetLeftPID();
  this->resetRightPID();

  sprintf(this->stream, "\33[93m[%s] Reseting PID...\33[0m", this->heroName.c_str());
  this->nh_->loginfo(this->stream);
}

void VelocityControl::resetLeftPID(void) {
  this->leftMotorPID->SetMode(MANUAL);
  this->leftMotorInput = 0;
  this->leftMotorOutput  = 0;
  this->leftMotorPID->SetMode(AUTOMATIC);
}

void VelocityControl::resetRightPID(void) {
  this->rightMotorPID->SetMode(MANUAL);
  this->rightMotorInput = 0;
  this->rightMotorOutput = 0;
  this->rightMotorPID->SetMode(AUTOMATIC);
}

/* Compute inverse kinematic of a Differential Drive Robot */
void VelocityControl::cmdvelCallback(const geometry_msgs::Twist& msg) {
  /* Dropping in case of high frequency commands */
  if (millis() - this->watchdog < 50) {
    return;
  }

  /* Get robot velocities */
  double linear = max(min((double)msg.linear.x, MAX_LINEAR_VEL), -MAX_LINEAR_VEL); // max linear speed 0.25 m/s
  double angular = max(min((double)msg.angular.z, MAX_ANGULAR_VEL), -MAX_ANGULAR_VEL); // max angular speed 0.08 rad/s
  /* Inverse Kinematic of a Differential Drive Robot */
  double V_l = (double)(2.0 * linear - WHEEL_SEPARATION * angular) / 2.0;
  double V_r = (double)(2.0 * linear + WHEEL_SEPARATION * angular) / 2.0;

  if (linear == 0.0 && angular == 0.0) { /* Robot is not moving, so disable motor to safe battery */
    this->reset();
    this->watchdog = 0;
    this->motorDriver->halt();
  } else {
    double leftMotorDirection = V_l * this->leftMotorSetpoint;
    if (leftMotorDirection < 0) {
      this->resetLeftPID();
    }
    double rightMotorDirection = V_r * this->rightMotorSetpoint;
    if (rightMotorDirection < 0) {
      this->resetRightPID();
    }

    this->leftMotorSetpoint = V_l;
    this->rightMotorSetpoint = V_r;
    
    this->watchdog = millis();
  }

  /* Disable tunning if still receiving commands */
  this->tuning = false;
  this->leftMotorPIDTune->Cancel();
  this->rightMotorPIDTune->Cancel();
}


/* Set PID parameters for both motors */
void VelocityControl::setPIDCallback(const hero_common::SetPID::Request& req, hero_common::SetPID::Response& res) {
  configVelPID.rkp = (float)req.rkp;
  configVelPID.rki = (float)req.rki;
  configVelPID.rkd = (float)req.rkd;
  configVelPID.lkp = (float)req.lkp;
  configVelPID.lki = (float)req.lki;
  configVelPID.lkd = (float)req.lkd;

  this->leftMotorPID->SetTunings((double)configVelPID.lkp, (double)configVelPID.lki, (double)configVelPID.lkd);
  this->rightMotorPID->SetTunings((double)configVelPID.rkp, (double)configVelPID.rki, (double)configVelPID.rkd);

  sprintf(this->stream, "\33[92m[%s] Left  Motor PID = [%f, %f, %f]\33[0m", this->heroName.c_str(), (double)configVelPID.lkp, (double)configVelPID.lki, (double)configVelPID.lkd);
  this->nh_->loginfo(this->stream);
  sprintf(this->stream, "\33[92m[%s] Right Motor PID = [%f, %f, %f]\33[0m", this->heroName.c_str(), (double)configVelPID.rkp, (double)configVelPID.rki, (double)configVelPID.rkd);
  this->nh_->loginfo(this->stream);

  sprintf(this->stream, "\33[92m[%s] Recording values in the flash... \33[0m", this->heroName.c_str());
  this->nh_->loginfo(this->stream);

  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.put(MEM_INIT_POS_PID_VELOCITY, configVelPID);
  EEPROM.end();

  sprintf(this->stream,  "\33[92m[%s] PID Parameters has been succesfully recorded! \33[0m", this->heroName.c_str());
  this->nh_->loginfo(this->stream);
  res.success = 1;
  res.message = "PID Parameters has been succesfully recorded!";
}


/* Autotune PID Motors */
void VelocityControl::pidCalibrationCallback(const std_srvs::Trigger::Request& req, std_srvs::Trigger::Response& res) {
  sprintf(this->stream, "\33[94m[%s] Starting Motors Auto Tuning! Wait... \33[0m", this->heroName.c_str());
  this->nh_->loginfo(this->stream);
  this->leftMotorOutput = -TUNE_STEADY_STATE;
  this->rightMotorOutput = TUNE_STEADY_STATE;
  this->motorDriver->command((int)(this->leftMotorOutput) + (int)(this->motorDriver->leftMotorDeadzone), (int)(this->rightMotorOutput) + (int)(this->motorDriver->rightMotorDeadzone));
  this->tuning = false;
  this->leftMotorPIDTune->Cancel();
  this->rightMotorPIDTune->Cancel();

  this->leftTuneDone = false;
  this->rightTuneDone = false;
  //  tunning_steady_state = millis();
  this->tuning = true;
  res.message = "PID Autotuning!";
  this->watchdog = millis();
}


void VelocityControl::tunePID(void) {
  if (!this->leftTuneDone) this->leftTuneDone = this->leftMotorPIDTune->Runtime();
  if (!this->rightTuneDone) this->rightTuneDone = this->rightMotorPIDTune->Runtime();
  if (this->leftTuneDone && this->rightTuneDone) {
    this->tuning = false; /* We're done, set the tuning parameters */
    float lkp = this->leftMotorPIDTune->GetKp();
    float lki = this->leftMotorPIDTune->GetKi();
    float lkd = this->leftMotorPIDTune->GetKd();
    if (lkp > 1 && lkp < 100) { // * Tuning is successed
      this->leftMotorPID->SetTunings(lkp, lki, lkd);
      this->leftMotorPID->SetMode(this->leftMotorPID->GetMode());
      this->leftMotorPIDTune->Cancel();
    } else { // * Tuning is failure
      this->nh_->loginfo("\33[92m Left Motor Tuning Failure! Using default values.\33[0m");
    }
    sprintf(this->stream, "\33[94m Left Motor Best PID params (%f, %f, %f) \33[0m", lkp, lki, lkd);
    this->nh_->loginfo(this->stream);
    float rkp = this->rightMotorPIDTune->GetKp();
    float rki = this->rightMotorPIDTune->GetKi();
    float rkd = this->rightMotorPIDTune->GetKd();
    if (rkp > 1 && rkp < 100) { // * Tuning is successed
      this->rightMotorPID->SetTunings(rkp, rki, rkd);
      this->rightMotorPID->SetMode(this->rightMotorPID->GetMode());
      this->rightMotorPIDTune->Cancel();
    } else { // * Tuning is failure
      this->nh_->loginfo("\33[92m Right Motor Tuning Failure! Using default values. \33[0m");
    }
    sprintf(this->stream, "\33[94m Right Motor Best PID params: (%f, %f, %f) \33[0m", rkp, rki, rkd);
    this->nh_->loginfo(this->stream);
  }
  this->motorDriver->command((int)(-this->leftMotorOutput) + (int)(this->motorDriver->leftMotorDeadzone), (int)(this->rightMotorOutput) + (int)(this->motorDriver->rightMotorDeadzone));
}
