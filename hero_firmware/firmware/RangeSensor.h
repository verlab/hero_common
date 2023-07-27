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
 
#ifndef __RANGE_SENSOR_H__
#define __RANGE_SENSOR_H__

/* ROS Library */
#define ROSSERIAL_ARDUINO_TCP
#include <ros.h>

/* Message types */
#include <sensor_msgs/LaserScan.h>
#include <hero_common/SetIRCalibration.h>

#define MEM_INIT_POS_IR_CALIB 220
#define MEM_ALOC_SIZE 512

class RangeSensor {
  private:
    ros::NodeHandle *nh_;
    String heroName;
    /* Laser publisher */
    sensor_msgs::LaserScan laserMessage;   /* Message Type */
    String laserTopic;                 /* Topic name */
    ros::Publisher *laserPub;          /* Publisher */
    String laserFrame;                 /* Laser link frame */
    
    String setIRCalibTopic; 
    ros::ServiceServer<hero_common::SetIRCalibration::Request, hero_common::SetIRCalibration::Response, RangeSensor> *setIRCalibService;    /* Service Type */
    
    unsigned long rate = 20, timer;
    char stream[100];

    

  public:
    RangeSensor(unsigned long rate);
    void init(void);
    void init(ros::NodeHandle &nh, String heroName);
    void update();
    void update(unsigned long rate);
    void connect();
    void setRate(unsigned long rate);
    void selectInput(int input);
    void readSensor();
    float meterFromIntensity(int idx, float value);
    int configModeCheck();
    void storeIRCalibrationData(const float *alpha);
    void setIRCalibCallback(const hero_common::SetIRCalibration::Request& req, hero_common::SetIRCalibration::Response& res);

    sensor_msgs::LaserScan getMessage(void);
};


#endif
