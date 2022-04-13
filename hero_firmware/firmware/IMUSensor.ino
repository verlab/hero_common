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

#include "IMUSensor.h"

IMUSensor::IMUSensor(unsigned long rate) {
  this->timer = millis();
  this->setRate(rate);
}


void IMUSensor::init(ros::NodeHandle &nh, String heroName) {
  this->nh_ = &nh;   /* ROS Node Handle */
  this->heroName = heroName;

  /* Address IMU publisher */
  this->imuTopic = this->heroName + String("/imu");                       /* Update topic name */
  this->imuPub = new ros::Publisher(this->imuTopic.c_str(), &this->imuMessage);    /* Instantiate publisher */
  this->imuFrame = this->heroName + String("/hat_link");                       /* Update frame name */
  this->imuMessage.header.frame_id = this->imuFrame.c_str();                  /* Set frame name */
  this->imuMessage.header.seq = -1;                                      /* Start message sequency */
  this->imuMessage.linear_acceleration_covariance[0] = 2.51605824e-03;   /* Accelerometer Covariance */
  this->imuMessage.linear_acceleration_covariance[1] = -7.08956399e-04;
  this->imuMessage.linear_acceleration_covariance[2] = -1.45457923e-04;
  this->imuMessage.linear_acceleration_covariance[3] = -7.08956399e-04;
  this->imuMessage.linear_acceleration_covariance[4] = 2.00625688e-03;
  this->imuMessage.linear_acceleration_covariance[5] = 3.71079569e-05;
  this->imuMessage.linear_acceleration_covariance[6] = -1.45457923e-04;
  this->imuMessage.linear_acceleration_covariance[7] = 3.71079569e-05;
  this->imuMessage.linear_acceleration_covariance[8] = 5.77742340e-05;
  this->imuMessage.angular_velocity_covariance[0] = 0.61750543;          /* Gyro Covariance */
  this->imuMessage.angular_velocity_covariance[1] = -0.22783495;
  this->imuMessage.angular_velocity_covariance[2] = -0.32218393;
  this->imuMessage.angular_velocity_covariance[3] = -0.22783495;
  this->imuMessage.angular_velocity_covariance[4] = 1.71576496;
  this->imuMessage.angular_velocity_covariance[5] = 0.24605797;
  this->imuMessage.angular_velocity_covariance[6] = -0.32218393;
  this->imuMessage.angular_velocity_covariance[7] = 0.24605797;
  this->imuMessage.angular_velocity_covariance[8] = 0.63667265;
  this->nh_->advertise(*this->imuPub);                                       /* Address IMU */


  /* Setup IMU I2C communication */
  /* Initiate IMU */
  Wire.pins(I2C_SDA, I2C_SCL); //3 as SDA and 1 as SCL
  Wire.begin(); //3 as SDA and 1 as SCL
  Wire.setClock(400000); // 400kHz I2C clock.
  /* Initialize device */
  delay(10);
  this->mpu = new MPU6050();
  this->mpu->initialize();
  /* load and configure the DMP */
  this->devStatus = this->mpu->dmpInitialize();
  /* supply your own gyro offsets here, scaled for min sensitivity */
//  this->mpu->setXGyroOffset(XGYRO_OFFSET);
//  this->mpu->setYGyroOffset(YGYRO_OFFSET);
//  this->mpu->setZGyroOffset(ZGYRO_OFFSET);
//  this->mpu->setZAccelOffset(ZACC_OFFSET); // 1688 factory default for my test chip
  /* Make sure it worked (returns 0 if so) */
  if (this->devStatus == 0) {
    /* turn on the DMP, now that it's ready */
    this->mpu->setDMPEnabled(true);
    /* enable Arduino interrupt detection */
    this->mpuIntStatus = this->mpu->getIntStatus();
    /* set our DMP Ready flag so the main loop() function knows it's okay to use it */
    this->dmpReady = true;
    /* get expected DMP packet size for later comparison */
    this->packetSize = this->mpu->dmpGetFIFOPacketSize();
    sprintf(this->stream, "\33[92m[%s] IMU hat detected!\33[0m", this->heroName.c_str());
    this->nh_->loginfo(this->stream);
  } else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
    sprintf(this->stream, "\33[91m[%s] IMU is not working or not connected! Error: %d\33[0m", this->heroName.c_str(), this->devStatus);
    this->nh_->loginfo(this->stream);
    this->IMUSensorEnable = false;
  }

  this->readSensor();

  //  if (this->devStatus != 0) {/
  //    sprintf(this->stream, "\33[93m[%s] IMU is not working or not connected!\33[0m", this->heroName.c_str());
  //    this->nh_->loginfo(this->stream);
  //    this->disable();/
  //  }/
}

bool IMUSensor::isEnable(void) {
  return this->IMUSensorEnable;
}

void IMUSensor::enable(void) {
  this->IMUSensorEnable = true;
}

void IMUSensor::disable(void) {
  this->IMUSensorEnable = false;
}

void IMUSensor::setRate(unsigned long rate) {
  this->rate = rate;
}

void IMUSensor::update(unsigned long rate) {
  if (((millis() - this->timer) > (1000 / rate)) && IMUSensorEnable) {
    this->readSensor();
    /* Send laser message to be published into ROS */
    this->imuMessage.header.stamp = this->nh_->now();
    this->imuPub->publish( &this->imuMessage);
    this->timer = millis();
  }
}

void IMUSensor::update() {
  this->update(this->rate);
}

/* Read IMU data and publish it*/
void IMUSensor::readSensor(void) {
  if (!this->dmpReady) return;

  /* wait for MPU interrupt or extra packet(s) available */
  this->mpuIntStatus = this->mpu->getIntStatus();

  /* get current FIFO count */
  this->fifoCount = this->mpu->getFIFOCount();

  /* check for overflow (this should never happen unless our code is too inefficient) */
  if ((this->mpuIntStatus & 0x10) || this->fifoCount == 1024) {
    /* reset so we can continue cleanly */
    this->mpu->resetFIFO();
    /* otherwise, check for DMP data ready interrupt (this should happen frequently) */
  } else if (this->mpuIntStatus & 0x02) {
    /* wait for correct available data length, should be a VERY short wait */
    while (this->fifoCount < this->packetSize) this->fifoCount = this->mpu->getFIFOCount();

    /* read a packet from FIFO */
    this->mpu->getFIFOBytes(this->fifoBuffer, this->packetSize);

    /* track FIFO count here in case there is > 1 packet available
      (this lets us immediately read more without waiting for an interrupt) */
    this->fifoCount -= this->packetSize;

    /* Display quaternion values in easy matrix form: w x y z */
    this->mpu->dmpGetQuaternion(&this->q, this->fifoBuffer);
    this->mpu->dmpGetGravity(&this->gravity, &this->q);
    this->mpu->dmpGetYawPitchRoll(this->ypr, &this->q, &this->gravity);
    this->mpu->dmpGetAccel(&this->aa, this->fifoBuffer);
    this->mpu->dmpGetGyro(&this->gy, this->fifoBuffer);

    /* These methods (and a few others) are also available */
    this->imuMessage.orientation.x = this->q.x;
    this->imuMessage.orientation.y = this->q.y;
    this->imuMessage.orientation.z = this->q.z;
    this->imuMessage.orientation.w = this->q.w;

    this->imuMessage.angular_velocity.x = this->gy.x;
    this->imuMessage.angular_velocity.y = this->gy.y;
    this->imuMessage.angular_velocity.z = this->gy.z;

    this->imuMessage.linear_acceleration.x = this->aa.x / 1000.0;
    this->imuMessage.linear_acceleration.y = this->aa.y / 1000.0;
    this->imuMessage.linear_acceleration.z = this->aa.z / 1000.0;
  }
}


float IMUSensor::get(void) {
  return this->ypr[0];
}
