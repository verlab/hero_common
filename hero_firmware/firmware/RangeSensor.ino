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

#include "RangeSensor.h"

RangeSensor::RangeSensor(unsigned long rate) {
  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.get(MEM_INIT_POS_IR_CALIB, irCalib);
  EEPROM.end();


  this->timer = millis();
  this->connect();
  this->setRate(rate);
}

void RangeSensor::init() {
  this->laserMessage.range_min = ROBOT_DIAMETER / 2.0;                                                     /* Min laser range */
  this->laserMessage.range_max = 0.20f + this->laserMessage.range_min;                                     /* Max laser range */
  this->laserMessage.angle_min = -M_PI;                                                                    /* Initial angle */
  this->laserMessage.angle_max = M_PI;                                                                     /* Final angle */
  this->laserMessage.angle_increment = 0.79 / 2.0;                                                         /* Angle increment */
  this->laserMessage.ranges_length = 16;                                                                   /* Samples; 8 proximity sensors */
  this->laserMessage.ranges = (float *)malloc(this->laserMessage.ranges_length * sizeof(float));           /* Instantiate ranges vector */
  this->laserMessage.intensities_length = 16;                                                              /* Samples; 8 proximity sensors */
  this->laserMessage.intensities = (float *)malloc(this->laserMessage.intensities_length * sizeof(float)); /* Instantiate intensities vector */
}

void RangeSensor::init(ros::NodeHandle &nh, String heroName) {
  this->nh_ = &nh; /* ROS Node Handle */
  this->heroName = heroName;
  this->heroName = (heroName.charAt(0) == '/') ? heroName.substring(1) : heroName;

  /* Address laser publisher */
  this->laserTopic = String("/") + this->heroName + String("/laser");                                     /* Update topic name */
  this->laserPub = new ros::Publisher(this->laserTopic.c_str(), &this->laserMessage); /* Instantiate publisher */
  this->laserFrame = this->heroName + String("/laser_link"); /* Update frame name */

  this->laserMessage.header.frame_id = this->laserFrame.c_str(); /* Set frame name */
  this->laserMessage.header.seq = 0;                             /* Start message sequency */

  this->laserMessage.range_min = ROBOT_DIAMETER / 2.0;                                                     /* Min laser range */
  this->laserMessage.range_max = 0.20f + this->laserMessage.range_min;                                     /* Max laser range */
  this->laserMessage.angle_min = -M_PI;                                                                    /* Initial angle */
  this->laserMessage.angle_max = M_PI;                                                                     /* Final angle */
  this->laserMessage.angle_increment = 0.79 / 2.0;                                                         /* Angle increment */
  this->laserMessage.ranges_length = 16;                                                                   /* Samples; 8 proximity sensors */
  this->laserMessage.ranges = (float *)malloc(this->laserMessage.ranges_length * sizeof(float));           /* Instantiate ranges vector */
  this->laserMessage.intensities_length = 16;                                                              /* Samples; 8 proximity sensors */
  this->laserMessage.intensities = (float *)malloc(this->laserMessage.intensities_length * sizeof(float)); /* Instantiate intensities vector */

  this->nh_->advertise(*this->laserPub);

  /* Address set PID motors service */
  this->setIRCalibTopic = String("/") + this->heroName + String("/ir_calibration");                                                                                                                                                    /* Update service name */
  this->setIRCalibService = new ros::ServiceServer<hero_common::SetIRCalibration::Request, hero_common::SetIRCalibration::Response, RangeSensor>(this->setIRCalibTopic.c_str(), &RangeSensor::setIRCalibCallback, this); /* Instantiate service */
  this->nh_->advertiseService(*this->setIRCalibService); /* Address fix motors service */                                                                                                                                /* Address Laser */
}

void RangeSensor::setRate(unsigned long rate) {
  this->rate = rate;
}

void RangeSensor::update(unsigned long rate) {
  if ((millis() - this->timer) > (1000 / rate)) {
    this->readSensor();
    /* Send laser message to be published into ROS */
    this->laserMessage.header.stamp = this->nh_->now();
    this->laserMessage.header.seq += 1;
    this->laserPub->publish(&laserMessage);
    this->timer = millis();
  }
}

void RangeSensor::update() {
  this->update(this->rate);
}


void RangeSensor::connect() {
  /* Setup Analog Multiplexer Pins */
  pinMode(MUX_A, OUTPUT);
  pinMode(MUX_B, OUTPUT);
  pinMode(MUX_C, OUTPUT);
  pinMode(MUX_EN, OUTPUT);
  analogWrite(MUX_EN, 0);
}

float RangeSensor::meterFromIntensity(int idx, float value) {
  float meter = sqrt((float) irCalib.alpha[idx] / value);  // Transform the analog value to a distance value in meters (given from field tests).
  meter = max(min(meter, 0.22f), 0.01f);
  return meter + this->laserMessage.range_min;
}

void RangeSensor::selectInput(int input) {
  // Extracting individual bits from the input
  int r0 = input & 0x01;         // Extracting the least significant bit
  int r1 = (input >> 1) & 0x01;  // Extracting the second least significant bit
  int r2 = (input >> 2) & 0x01;  // Extracting the third least significant bit

  // Setting the state of digital pins based on the extracted bits
  digitalWrite(MUX_A, r0);  // Setting MUX_A_PIN to r0
  digitalWrite(MUX_B, r1);  // Setting MUX_B_PIN to r1
  digitalWrite(MUX_C, r2);  // Setting MUX_C_PIN to r2
}

void RangeSensor::readSensor() {
  pinMode(MUX_EN, OUTPUT);
  for (int sensor = 0; sensor <= 7; sensor++) {
    /* Select the input  */
    selectInput(sensor);
    delayMicroseconds(10);
    /* Photodiode needs sleep for while since all the emissors are turned on at same time
        1. Read A0 sensor light
        2. Turn on the emissors and wait 100 us
        3. Read A0 sensor proximity
        4. Wait until A1 Espera até A1 desaturate and repeat for A1 {until A7}
        PS. It seems that the darker emissors recover faster than the light ones during over the saturation
    */
    analogWrite(MUX_EN, 0);
    delayMicroseconds(100);              // Photodiode needs sleep for a while since all the emitters are turned on at the same time
    float env = (float) analogRead(A0);  // Reading the ambient light level from sensor A0

    analogWrite(MUX_EN, 1024);   // Turning on all diodes/emitters and enabling the multiplexer
    delayMicroseconds(380);      // Waiting for the diodes/emitters to power up (100 microseconds)

    float sensor_reading = max(0.0f, (float)analogRead(A0) - env);  // Reading the proximity level from sensor A0 and subtracting the ambient light level
    this->laserMessage.intensities[real_pos_inter[sensor]] = sensor_reading;
    this->laserMessage.ranges[real_pos_inter[sensor]] = this->meterFromIntensity(real_pos[sensor], sensor_reading);

  }
  analogWrite(MUX_EN, 0);  // Turning off all diodes/emitters and disabling the multiplexer
  // delayMicroseconds(100);   // Waiting for the diodes/emitters to power down (100 microseconds)

#define RANGE_INTERPOLATION
#ifdef RANGE_INTERPOLATION
  for (int i = 1; i < 16; i += 2) {
    this->laserMessage.ranges[i] = 0.5 * this->laserMessage.ranges[i - 1] + 0.5 * this->laserMessage.ranges[(i + 1) % 16];
    this->laserMessage.intensities[i] = 0.5 * this->laserMessage.intensities[i - 1] + 0.5 * this->laserMessage.intensities[(i + 1) % 16];
  }
#endif
}


int RangeSensor::configModeCheck() {
  pinMode(MUX_EN, OUTPUT);
  int mode = 0;

  for (int sensor = 0; sensor <= 7; sensor++) {
    /* Select the input  */
    selectInput(sensor);
    delayMicroseconds(10);
    /* Photodiode needs sleep for while since all the emissors are turned on at same time
        1. Read A0 sensor light
        2. Turn on the emissors and wait 100 us
        3. Read A0 sensor proximity
        4. Wait until A1 Espera até A1 desaturate and repeat for A1 {until A7}
        PS. It seems that the darker emissors recover faster than the light ones during over the saturation
    */
    analogWrite(MUX_EN, 0);
    delayMicroseconds(100);  // diode should power up in 100 us
    int env = analogRead(A0);
    analogWrite(MUX_EN, 1024);  // turn on all diode and enable mux
    delayMicroseconds(400);      // diode should power up in 100 us -> 180 us

    if (!((analogRead(A0) - env) < TOUCH_THRESHOLD)) {
      // return 0;
      mode = (1 << real_pos[sensor]) | mode;
    }

    analogWrite(MUX_EN, 0); /* Turn off all diode and enable mux */
  }

  return mode;
}

// Store IR calibration data in EEPROM
void RangeSensor::storeIRCalibrationData(const float *alpha) {
  for (uint i = 0; i < 8; i++) {
    irCalib.alpha[i] = alpha[i];
  }
  // Save data to EEPROM
  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.put(MEM_INIT_POS_IR_CALIB, irCalib);
  EEPROM.end();
}

/* Set Motor parameters for both motors */
void RangeSensor::setIRCalibCallback(const hero_common::SetIRCalibration::Request &req, hero_common::SetIRCalibration::Response &res) {
  // Update IR calibration data with new values from the request
  irCalib.alpha[0] = req.IR0;
  irCalib.alpha[1] = req.IR1;
  irCalib.alpha[2] = req.IR2;
  irCalib.alpha[3] = req.IR3;
  irCalib.alpha[4] = req.IR4;
  irCalib.alpha[5] = req.IR5;
  irCalib.alpha[6] = req.IR6;
  irCalib.alpha[7] = req.IR7;

  // Log message to indicate storing IR calibration data in EEPROM
  sprintf(this->stream, "\33[92m[%s] Recording values in the flash... \33[0m", this->heroName.c_str());
  this->nh_->loginfo(this->stream);

  // Store the new calibration data in EEPROM
  this->storeIRCalibrationData(irCalib.alpha);

  // Log message to indicate successful recording
  sprintf(this->stream, "\33[92m[%s] IR calibration parameters have been successfully recorded! \33[0m", this->heroName.c_str());
  this->nh_->loginfo(this->stream);

  res.success = 1;
  res.message = "IR Calibration parameters have been successfully recorded!";
}

sensor_msgs::LaserScan RangeSensor::getMessage(void) {
  return this->laserMessage;
}
