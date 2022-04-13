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


void RangeSensor::init(ros::NodeHandle &nh, String heroName) {
  this->nh_ = &nh;   /* ROS Node Handle */
  this->heroName = heroName;
  
  /* Address laser publisher */
  this->laserTopic = heroName + String("/laser");                                        /* Update topic name */
  this->laserPub = new ros::Publisher(this->laserTopic.c_str(), &this->laserMessage);    /* Instantiate publisher */
  this->laserFrame = heroName + String("/laser_link");                                   /* Update frame name */
  
  this->laserMessage.header.frame_id = this->laserFrame.c_str();                         /* Set frame name */
  this->laserMessage.header.seq = -1;                                                    /* Start message sequency */
  
  this->laserMessage.range_min = 0.07367/2.0; //0.0;                                                    /* Min laser range */
  this->laserMessage.range_max = 0.20;                                                   /* Max laser range */
  this->laserMessage.angle_min = -M_PI;                                                  /* Initial angle */
  this->laserMessage.angle_max = M_PI;                                                   /* Final angle */
  this->laserMessage.angle_increment = 0.79/2.0;                                             /* Angle increment */
  this->laserMessage.ranges_length = 16;                                                  /* Samples; 8 proximity sensors */
  this->laserMessage.ranges = (float *)malloc(this->laserMessage.ranges_length * sizeof(float));                        /* Instantiate ranges vector */
  this->laserMessage.intensities_length = 16;                                             /* Samples; 8 proximity sensors */
  this->laserMessage.intensities = (float *)malloc(this->laserMessage.intensities_length * sizeof(float));                   /* Instantiate intensities vector */
  
  this->nh_->advertise(*this->laserPub);    
  
  /* Address set PID motors service */
  this->setIRCalibTopic = this->heroName + String("/ir_calibration");                                                                                                 /* Update service name */
  this->setIRCalibService = new ros::ServiceServer<hero_common::SetIRCalibration::Request, hero_common::SetIRCalibration::Response, RangeSensor>(this->setIRCalibTopic.c_str(), &RangeSensor::setIRCalibCallback, this);               /* Instantiate service */
  this->nh_->advertiseService(*this->setIRCalibService);                                                                                                                          /* Address fix motors service *//* Address Laser */
}

void RangeSensor::setRate(unsigned long rate) {
  this->rate = rate;
}

void RangeSensor::update(unsigned long rate) {
  if ((millis() - this->timer) > (1000/rate)) {
    this->readSensor();
    /* Send laser message to be published into ROS */
    this->laserMessage.header.stamp = this->nh_->now();
    this->laserPub->publish( &laserMessage );
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

float RangeSensor::meterFromIntensity(int idx, float value){
  if (value > 6){
        value = (float) irCalib.alpha[idx]/sqrt(value) + this->laserMessage.range_min; // Transform the analog value to a distance value in meters (given from field tests).
    } else{
        value = this->laserMessage.range_max;
    }
    value = max(min(value, this->laserMessage.range_max), this->laserMessage.range_min);
    return value;
}


void RangeSensor::readSensor() {
  for (int count = 0; count <= 7; count++) {
    /* Select the input  */
    int r0 = count & 0x01;
    int r1 = (count >> 1) & 0x01;
    int r2 = (count >> 2) & 0x01;
    digitalWrite(MUX_A, r0);
    digitalWrite(MUX_B, r1);
    digitalWrite(MUX_C, r2);
    /* Photodiode needs sleep for while since all the emissors are turned on at same time
      1. Read A0 sensor light
      2. Turn on the emissors and wait 100 us
      3. Read A0 sensor proximity
      4. Wait until A1 Espera até A1 desaturate and repeat for A1 {until A7}
      PS. It seems that the darker emissors recover faster than the light ones during over the saturation
    */
    delayMicroseconds(500);  // diode should power up in 100 us
    float env = (float) analogRead(A0);
    analogWrite(MUX_EN, 1024); // turn on all diode and enable mux
    delayMicroseconds(100);  // diode should power up in 100 us -> 180 us

    this->laserMessage.ranges[real_pos_inter[count]] = this->meterFromIntensity(real_pos[count], (float)(analogRead(A0)) - env);
    this->laserMessage.intensities[real_pos_inter[count]] = (float)analogRead(A0) - (float)env;//env;

    analogWrite(MUX_EN, 0); /* Turn off all diode and enable mux */
  }
  #define RANGE_INTERPOLATION
  #ifdef RANGE_INTERPOLATION
  for (int i = 1; i < 16; i+=2){
   this->laserMessage.ranges[i] = 0.5 * this->laserMessage.ranges[i-1] + 0.5 * this->laserMessage.ranges[(i+1)%16];
   this->laserMessage.intensities[i] = 0.5 * this->laserMessage.intensities[i-1] + 0.5 * this->laserMessage.intensities[(i+1)%16];
  }  
  #endif
}


bool RangeSensor::configModeCheck() {
  for (int count = 0; count <= 7; count++) {
    /* Select the input  */
    int r0 = count & 0x01;
    int r1 = (count >> 1) & 0x01;
    int r2 = (count >> 2) & 0x01;
    digitalWrite(MUX_A, r0);
    digitalWrite(MUX_B, r1);
    digitalWrite(MUX_C, r2);
    /* Photodiode needs sleep for while since all the emissors are turned on at same time
      1. Read A0 sensor light
      2. Turn on the emissors and wait 100 us
      3. Read A0 sensor proximity
      4. Wait until A1 Espera até A1 desaturate and repeat for A1 {until A7}
      PS. It seems that the darker emissors recover faster than the light ones during over the saturation
    */
    delayMicroseconds(500);  // diode should power up in 100 us
    int env = analogRead(A0);
    analogWrite(MUX_EN, 1024); // turn on all diode and enable mux
    delayMicroseconds(100);  // diode should power up in 100 us -> 180 us

    if ((analogRead(A0) - env) < TOUCH_THRESHOLD)
      return false;

    analogWrite(MUX_EN, 0); /* Turn off all diode and enable mux */
  }
  return true;
}


/* Set Motor parameters for both motors */
void RangeSensor::setIRCalibCallback(const hero_common::SetIRCalibration::Request& req, hero_common::SetIRCalibration::Response& res) {
  irCalib.alpha[0] = req.IR0;
  irCalib.alpha[1] = req.IR1;
  irCalib.alpha[2] = req.IR2;
  irCalib.alpha[3] = req.IR3;
  irCalib.alpha[4] = req.IR4;
  irCalib.alpha[5] = req.IR5;
  irCalib.alpha[6] = req.IR6;
  irCalib.alpha[7] = req.IR7;
  
  sprintf(this->stream, "\33[92m[%s] Recording values in the flash... \33[0m", this->heroName.c_str());
  this->nh_->loginfo(this->stream);

  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.put(MEM_INIT_POS_IR_CALIB, irCalib);
  EEPROM.end();

  sprintf(this->stream,  "\33[92m[%s] IR calibration parameters has been succesfully recorded! \33[0m", this->heroName.c_str());
  this->nh_->loginfo(this->stream);
  res.success = 1;
  res.message = "IR Calibration parameters has been succesfully recorded!";
}
