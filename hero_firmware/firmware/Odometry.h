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
 
#ifndef __ODOMETRY_H__
#define __ODOMETRY_H__

/* ROS Library */
#define ROSSERIAL_ARDUINO_TCP
#include <ros.h>

/* Message types */
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose2D.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <hero_common/SetOdom.h>

#include "WheelEncoder.h"
#include <SimpleKalmanFilter.h>         /* https://github.com/denyssene/SimpleKalmanFilter */

#ifdef __IMU_SENSOR_H__
#include "IMUSensor.h"
#endif


class Odometry {
  private:
    ros::NodeHandle *nh_;
    String heroName;
    /* Encoder-base Odometry */
    WheelEncoder *wheelEncoder;
    SimpleKalmanFilter *thetaKF;
    #ifdef __IMU_SENSOR_H__
    IMUSensor *imuSensor;
    unsigned long imuBiasTimer = 0.0;
    double imuBias = 0;
    double imuInitValue = 0;
    double imuLastYaw = 0;
    #endif
    
    /** TF to publish transformation **/
    tf::TransformBroadcaster broadcaster;
    geometry_msgs::TransformStamped t;
    
    /* Odometry publisher */
    nav_msgs::Odometry odomMessage;        /* Message Type */
    String odomTopic;                      /* Topic name */
    ros::Publisher *odomPub;               /* Publisher */
    String baseFrame;                      /* Base link frame */
    String leftWheelFrame;                 /* left wheel link frame */
    String rightWheelFrame;                /* right wheel link frame */
    String hatFrame;                       /* hat link frame */
    String laserFrame;                     /* laser link frame */
    String odomFrame;                      /* Odom link frame */

    /* Pose2d publish */
    geometry_msgs::Pose2D poseMessage; /* Message Type */
    
    /* Reset Odometry Service */
    ros::ServiceServer<hero_common::SetOdom::Request, hero_common::SetOdom::Response, Odometry> *setOdomService;        /* Service Type */
    String setOdomTopic;                                                                                  /* Service name */

    unsigned long rate = 20, timer;

    double deltaSteps, deltaTheta, deltaYaw;

  public:
    Odometry(unsigned long rate);
    #ifdef __IMU_SENSOR_H__
    void init(ros::NodeHandle &nh, String heroName, WheelEncoder &wheelEncoder, IMUSensor &imuSensor);
    #endif
    void init(ros::NodeHandle &nh, String heroName, WheelEncoder &wheelEncoder);
    void update();
    void update(unsigned long rate);
    void compute();
    void computeTf();
    void setRate(unsigned long rate);
    void readSensor();
    
    /* Callback function */
    void setOdomCallback(const hero_common::SetOdom::Request& req, hero_common::SetOdom::Response& res);  
};


#endif
