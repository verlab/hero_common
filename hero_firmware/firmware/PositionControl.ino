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

#include "PositionControl.h"

PositionControl::PositionControl(unsigned long rate) {
  this->timer = millis();
  this->setRate(rate);

  /* Setup left Motor PID */
  this->leftMotorPID = new PID (&this->leftMotorInput, &this->leftMotorOutput, &this->leftMotorSetpoint, 5.0, 9.0, 0.1, 0, REVERSE); /* Motor PID */
  this->leftMotorPID->SetMode(AUTOMATIC);
  this->leftMotorPID->SetOutputLimits(-output_lim, output_lim);       /* Max output limit for left motor */
  this->leftMotorPID->SetSampleTime(sample_time);                     /* 10 microseconds */

  /* Setup autotuner for PID */
  this->leftMotorPIDTune = new PID_ATune(&this->leftMotorInput, &this->leftMotorOutput);    /* PID autotuner */
  this->leftMotorPIDTune->SetControlType(PID_ATune::NO_OVERSHOOT_PID);    /* Set control type for autotuner */
  this->leftMotorPIDTune->SetNoiseBand(TUNE_NOISE);                         /* The autotune will ignore signal chatter smaller than this value this should be accurately set */
  this->leftMotorPIDTune->SetOutputStep(TUNE_STEP);                         /* How far above and below the starting value will the output step? */
  this->leftMotorPIDTune->SetLookbackSec((int)TUNE_LOOK_BACK);              /* How far back are we looking to identify peaks */

  /* Setup right Motor PID */
  this->rightMotorPID = new PID (&this->rightMotorInput, &this->rightMotorOutput, &this->rightMotorSetpoint, 5.0, 9.0, 0.1, 0, DIRECT); /* Motor PID */
  this->rightMotorPID->SetMode(AUTOMATIC);
  this->rightMotorPID->SetOutputLimits(-output_lim, output_lim);       /* Max output limit for left motor */
  this->rightMotorPID->SetSampleTime(sample_time);                     /* 10 microseconds */

  this->rightMotorPIDTune = new PID_ATune(&this->rightMotorInput, &this->rightMotorOutput);    /* PID autotuner */
  this->rightMotorPIDTune->SetControlType(PID_ATune::NO_OVERSHOOT_PID);
  this->rightMotorPIDTune->SetNoiseBand(TUNE_NOISE);                        /* The autotune will ignore signal chatter smaller than this value this should be accurately set */
  this->rightMotorPIDTune->SetOutputStep(TUNE_STEP);                        /* How far above and below the starting value will the output step? */
  this->rightMotorPIDTune->SetLookbackSec((int)TUNE_LOOK_BACK);             /* How far back are we looking to identify peaks */

  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.get(MEM_INIT_POS_PID_POSITION, configPosPID);
  EEPROM.end();

  if (configPosPID.lkp > 0) {
    this->leftMotorPID->SetTunings(configPosPID.lkp, configPosPID.lki, configPosPID.lkd);
  }

  if (configPosPID.rkp > 0) {
    this->rightMotorPID->SetTunings(configPosPID.rkp, configPosPID.rki, configPosPID.rkd);
  }
}

void PositionControl::init(ros::NodeHandle &nh, String heroName, MotorDriver& motorDriver, WheelEncoder& wheelEncoder) {
  this->motorDriver = &motorDriver;
  this->wheelEncoder = &wheelEncoder;

  this->nh_ = &nh;   /* ROS Node Handle */
  this->heroName = heroName;

  /* Address command velocity-position subscribe */
  this->cmdvelTopic = this->heroName + String("/position_controller/cmd_vel");                          /* Update topic name */
  this->cmdvelSub = new ros::Subscriber<geometry_msgs::Twist, PositionControl>(this->cmdvelTopic.c_str(), &PositionControl::cmdvelCallback, this);     /* Instantiate subscriber */
  this->nh_->subscribe(*this->cmdvelSub);      /* Address Command Vel */

  /* Address set PID motors service */
  this->setPIDTopic = this->heroName + String("/position_controller/pid_parameters");                                                                                                 /* Update service name */
  this->setPIDService = new ros::ServiceServer<hero_common::SetPID::Request, hero_common::SetPID::Response, PositionControl>(this->setPIDTopic.c_str(), &PositionControl::setPIDCallback, this);               /* Instantiate service */
  this->nh_->advertiseService(*this->setPIDService);                                                                                                                          /* Address fix motors service */

  /* Address PID calibration service */
  this->pidCalibrationTopic = this->heroName + String("/position_controller/pid_calibration");                                                                                                     /* Update service name */
  this->pidCalibrationService = new ros::ServiceServer<std_srvs::Trigger::Request, std_srvs::Trigger::Response, PositionControl>(this->pidCalibrationTopic.c_str(), &PositionControl::pidCalibrationCallback, this);    /* Instantiate service */
  this->nh_->advertiseService(*this->pidCalibrationService);
}


void PositionControl::setRate(unsigned long rate) {
  this->rate = rate;
}

void PositionControl::update() {
  this->update(this->rate);
}

/* Update control loop and set the output to the motors */
void PositionControl::update(unsigned long rate) {
  if (((millis() - this->timer) > (1000 / rate)) && ((millis() - this->watchdog) < 3000)) {
    /* Position-Control */
    this->leftMotorInput = ((double)this->wheelEncoder->getLeftEncoderTicks() - this->leftMotorStartPos);
    this->rightMotorInput = ((double)this->wheelEncoder->getRightEncoderTicks() - this->rightMotorStartPos);
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

void PositionControl::reset(void) {
  this->leftMotorPID->SetMode(MANUAL);
  this->rightMotorPID->SetMode(MANUAL);
  this->leftMotorInput = 0;
  this->rightMotorInput = 0;
  this->leftMotorOutput  = 0;
  this->rightMotorOutput  = 0;
  this->leftMotorStartPos  = (double)this->wheelEncoder->getLeftEncoderTicks();
  this->rightMotorStartPos = (double)this->wheelEncoder->getRightEncoderTicks();
  this->leftMotorPID->SetMode(AUTOMATIC);
  this->rightMotorPID->SetMode(AUTOMATIC);

  sprintf(this->stream, "\33[93m[%s] Reseting PID...\33[0m", this->heroName.c_str());
  this->nh_->loginfo(this->stream);
}

void PositionControl::resetLeftPID(void) {
  this->leftMotorPID->SetMode(MANUAL);
  this->leftMotorInput = 0;
  this->leftMotorOutput  = 0;
  this->leftMotorPID->SetMode(AUTOMATIC);
}

void PositionControl::resetRightPID(void) {
  this->rightMotorPID->SetMode(MANUAL);
  this->rightMotorInput = 0;
  this->rightMotorOutput = 0;
  this->rightMotorPID->SetMode(AUTOMATIC);
}

void PositionControl::cmdvelCallback(const geometry_msgs::Twist& msg) {
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

  double dt = 1.0;
  double new_l_motor_pos = (double) V_l * dt / MOT_STEP_DIST; // ticks left wheel should take after dt seconds
  double new_r_motor_pos = (double) V_r * dt / MOT_STEP_DIST; // ticks right wheel should take after dt seconds

//  this->leftMotorSetpoint = new_l_motor_pos;
//  this->rightMotorSetpoint = new_r_motor_pos;
//
//  this->leftMotorStartPos  = (double) this->wheelEncoder->getLeftEncoderTicks();
//  this->rightMotorStartPos = (double) this->wheelEncoder->getRightEncoderTicks();

  if (linear == 0.0 && angular == 0.0) { /* Robot is not moving, so disable motor to safe battery */
    this->reset();
    this->motorDriver->halt();
    this->watchdog = 0;
  } else {
//    if ((millis() - this->watchdog) > 800) {
//      this->reset();
//    }
        double leftMotorDirection = new_l_motor_pos * this->leftMotorSetpoint;
        if (leftMotorDirection < 0) {
          this->resetLeftPID();
        }
        double rightMotorDirection = new_r_motor_pos * this->rightMotorSetpoint;
        if (rightMotorDirection < 0) {
          this->resetRightPID();
        }
        this->leftMotorSetpoint = new_l_motor_pos;
        this->rightMotorSetpoint = new_r_motor_pos;
    
        this->leftMotorStartPos  = (double) this->wheelEncoder->getLeftEncoderTicks();
        this->rightMotorStartPos = (double) this->wheelEncoder->getRightEncoderTicks();

    this->watchdog = millis();
  }
  /*
     else {
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
  */
  /* Disable tunning if still receiving commands */
  this->tuning = false;
  this->leftMotorPIDTune->Cancel();
  this->rightMotorPIDTune->Cancel();
}


/* Set PID parameters for both motors */
void PositionControl::setPIDCallback(const hero_common::SetPID::Request& req, hero_common::SetPID::Response& res) {
  configPosPID.rkp = (float)req.rkp;
  configPosPID.rki = (float)req.rki;
  configPosPID.rkd = (float)req.rkd;
  configPosPID.lkp = (float)req.lkp;
  configPosPID.lki = (float)req.lki;
  configPosPID.lkd = (float)req.lkd;

  this->leftMotorPID->SetTunings((double)configPosPID.lkp, (double)configPosPID.lki, (double)configPosPID.lkd);
  this->rightMotorPID->SetTunings((double)configPosPID.rkp, (double)configPosPID.rki, (double)configPosPID.rkd);

  sprintf(this->stream, "\33[92m[%s] Left  Motor PID = [%f, %f, %f]\33[0m", this->heroName.c_str(), (double)configPosPID.lkp, (double)configPosPID.lki, (double)configPosPID.lkd);
  this->nh_->loginfo(this->stream);
  sprintf(this->stream, "\33[92m[%s] Right Motor PID = [%f, %f, %f]\33[0m", this->heroName.c_str(), (double)configPosPID.rkp, (double)configPosPID.rki, (double)configPosPID.rkd);
  this->nh_->loginfo(this->stream);

  sprintf(this->stream, "\33[92m[%s] Recording values in the flash... \33[0m", this->heroName.c_str());
  this->nh_->loginfo(this->stream);

  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.put(MEM_INIT_POS_PID_POSITION, configPosPID);
  EEPROM.end();

  sprintf(this->stream,  "\33[92m[%s] PID Parameters has been succesfully recorded! \33[0m", this->heroName.c_str());
  this->nh_->loginfo(this->stream);
  res.success = 1;
  res.message = "PID Parameters has been succesfully recorded!";
}


/* Autotune PID Motors */
void PositionControl::pidCalibrationCallback(const std_srvs::Trigger::Request& req, std_srvs::Trigger::Response& res) {
  sprintf(this->stream, "\33[94m[%s] Starting Motors Auto Tuning! Wait... \33[0m", this->heroName.c_str());
  this->nh_->loginfo(this->stream);
  this->leftMotorOutput = 0;
  this->rightMotorOutput = 0;
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


void PositionControl::tunePID(void) {
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
