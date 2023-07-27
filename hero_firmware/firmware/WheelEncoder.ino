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
 
#include "WheelEncoder.h"



WheelEncoder::WheelEncoder(unsigned long rate) {
  this->leftEncoder = new Encoder(ENC_A_LEFT, ENC_B_LEFT);            /* Left Encoder Configuration */
  this->rightEncoder = new Encoder(ENC_A_RIGHT, ENC_B_RIGHT);          /* Right Encoder Configuration */

  this->leftKF = new SimpleKalmanFilter(0.02f, 0.02f, 0.2f);
  this->rightKF = new SimpleKalmanFilter(0.02f, 0.02f, 0.2f);

  this->timer = millis();
  this->setRate(rate);

  this->leftEncoder->write(0);
  this->rightEncoder->write(0);
}

void WheelEncoder::init(void) {
  this->encoderMessage.left_speed_filtered = 0.0001;
  this->encoderMessage.right_speed_filtered = 0.0001;

  this->encoderMessage.left_speed = 0.001;
  this->encoderMessage.right_speed = 0.001;
}

void WheelEncoder::init(ros::NodeHandle &nh, String heroName) {
  this->nh_ = &nh;   /* ROS Node Handle */
  this->heroName = heroName;

  /* Address encoder publisher */
  this->encoderTopic = this->heroName + String("/encoder");                         /* Update topic name */
  this->encoderPub = new ros::Publisher(this->encoderTopic.c_str(), &this->encoderMessage);    /* Instantiate publisher */
  this->encoderFrame = this->heroName + String("/encoder");                         /* Update frame name */
  this->encoderMessage.header.frame_id = this->encoderFrame.c_str();                    /* Set frame name */
  this->encoderMessage.header.seq = -1;                                          /* Start message sequency */
  this->nh_->advertise(*this->encoderPub);                                           /* Address Laser */
  
  this->init();
}

void WheelEncoder::setRate(unsigned long rate) {
  this->rate = rate;
}

void WheelEncoder::clear() {
  this->leftEncoder->write(0);
  this->rightEncoder->write(0);
  this->encoderMessage.left_ticks = 0;
  this->encoderMessage.right_ticks = 0;
}


void WheelEncoder::update(void) {
  this->update(this->rate);
}

long WheelEncoder::getLeftEncoderTicks(void) {
  return this->leftEncoder->read();
}

long WheelEncoder::getRightEncoderTicks(void) {
  return this->rightEncoder->read();
}

void WheelEncoder::readSensor(void) {
  /* Update motor position */
  double left_ticks_now = this->leftEncoder->read();
  double right_ticks_now = this->rightEncoder->read();
  this->encoderMessage.timestep = ((double)(micros() - this->readTimer) / 1000000.0);

  /* Compute the difference of ticks */
  this->encoderMessage.left_diff  = left_ticks_now - this->encoderMessage.left_ticks; // Expressed in tickes.
  this->encoderMessage.right_diff = right_ticks_now - this->encoderMessage.right_ticks;   // Expressed in tickes.

  /* Update last encoder ticks*/
  this->encoderMessage.left_ticks = left_ticks_now;
  this->encoderMessage.right_ticks = right_ticks_now;

  /* Transform ticks to distance in meters */
  this->encoderMessage.left_dist = MOT_STEP_DIST * this->encoderMessage.left_diff;
  this->encoderMessage.right_dist = MOT_STEP_DIST * this->encoderMessage.right_diff;

  /* Get encoder speed in m/s */
  this->encoderMessage.left_speed  = (double) this->encoderMessage.left_dist / (this->encoderMessage.timestep + 1e-10);
  this->encoderMessage.right_speed = (double) this->encoderMessage.right_dist / (this->encoderMessage.timestep + 1e-10);
  /* Low-pass filter */
  //this->encoderMessage.left_speed_filtered = (1.0 - ENCODER_SPEED_GAIN) * this->encoderMessage.left_speed_filtered + ENCODER_SPEED_GAIN * this->encoderMessage.left_speed;
  //this->encoderMessage.right_speed_filtered = (1.0 - ENCODER_SPEED_GAIN) * this->encoderMessage.right_speed_filtered + ENCODER_SPEED_GAIN * this->encoderMessage.right_speed;
  /* Kalman filter */
  this->encoderMessage.left_speed_filtered = this->leftKF->updateEstimate(this->encoderMessage.left_speed);
  this->encoderMessage.right_speed_filtered = this->rightKF->updateEstimate(this->encoderMessage.right_speed);

  this->readTimer = micros();
}

/* Update and publish encoder data */
void WheelEncoder::update(unsigned long rate) {
  if ((millis() - this->timer) > (1000 / rate)) {
    this->readSensor();
    this->encoderMessage.header.stamp = this->nh_->now();
    this->encoderPub->publish( &this->encoderMessage );
    this->timer = millis();
  }
}

hero_common::Encoder WheelEncoder::getMessage(void) {
  return this->encoderMessage;
}
