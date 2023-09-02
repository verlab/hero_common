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

#include "Odometry.h"

Odometry::Odometry(unsigned long rate) {
  this->timer = millis();
  this->setRate(rate);
}

#ifdef __IMU_SENSOR_H__
void Odometry::init(ros::NodeHandle &nh, String heroName, WheelEncoder &wheelEncoder, IMUSensor &imuSensor) {
  this->imuSensor = &imuSensor;
  this->imuSensor->readSensor();
  this->imuInitValue = this->imuSensor->get();
  this->imuLastYaw = this->imuSensor->get();
  this->imuBiasTimer = millis();
  this->wheelEncoder = &wheelEncoder;
  this->thetaKF = new SimpleKalmanFilter(0.002, 0.002, 0.2);

  this->nh_ = &nh; /* ROS Node Handle */
  this->heroName = (heroName.charAt(0) == '/') ? heroName.substring(1) : heroName;

  /* Address TF */
  this->broadcaster.init(nh);

  /* Address odometry publisher */
  this->odomTopic = String("/") + this->heroName + String("/odom");                /* Update topic name */
  this->odomPub = new ros::Publisher(this->odomTopic.c_str(), &this->odomMessage); /* Instantiate publisher */
  this->odomFrame = this->heroName + String("/odom");                              /* Update frame name */
  this->baseFrame = this->heroName + String("/base_link");                         /* Update frame name */
  this->leftWheelFrame = this->heroName + String("/left_wheel_link");              /* Update frame name */
  this->rightWheelFrame = this->heroName + String("/right_wheel_link");            /* Update frame name */
  this->hatFrame = this->heroName + String("/hat_link");                           /* Update frame name */
  this->laserFrame = this->heroName + String("/laser_link");                       /* Update frame name */
  this->odomMessage.header.frame_id = this->odomFrame.c_str();                     /* Set frame name */
  this->odomMessage.header.seq = -1;                                               /* Start message sequency */
  this->odomMessage.child_frame_id = this->baseFrame.c_str();                      /* Update frame name */
  this->nh_->advertise(*this->odomPub);

  /* Address set odom service */
  this->setOdomTopic = String("/") + this->heroName + String("/set_odom");                                                                                                              /* Update service name */
  this->setOdomService = new ros::ServiceServer<hero_common::SetOdom::Request, hero_common::SetOdom::Response, Odometry>(this->setOdomTopic.c_str(), &Odometry::setOdomCallback, this); /* Instantiate service */
  this->nh_->advertiseService(*this->setOdomService);                                                                                                                                   /* Address set odom service */
}
#endif

void Odometry::init(ros::NodeHandle &nh, String heroName, WheelEncoder &wheelEncoder) {
  this->wheelEncoder = &wheelEncoder;

  this->nh_ = &nh; /* ROS Node Handle */
  this->heroName = (heroName.charAt(0) == '/') ? heroName.substring(1) : heroName;

  /* Address TF */
  this->broadcaster.init(nh);

  /* Address odometry publisher */
  this->odomTopic = String("/") + this->heroName + String("/odom");                /* Update topic name */
  this->odomPub = new ros::Publisher(this->odomTopic.c_str(), &this->odomMessage); /* Instantiate publisher */
  this->odomFrame = this->heroName + String("/odom");                              /* Update frame name */
  this->baseFrame = this->heroName + String("/base_link");                         /* Update frame name */
  this->leftWheelFrame = this->heroName + String("/left_wheel_link");              /* Update frame name */
  this->rightWheelFrame = this->heroName + String("/right_wheel_link");            /* Update frame name */
  this->hatFrame = this->heroName + String("/hat_link");                           /* Update frame name */
  this->laserFrame = this->heroName + String("/laser_link");                       /* Update frame name */
  this->odomMessage.header.frame_id = this->odomFrame.c_str();                     /* Set frame name */
  this->odomMessage.header.seq = -1;                                               /* Start message sequency */
  this->odomMessage.child_frame_id = this->baseFrame.c_str();                      /* Update frame name */
  this->nh_->advertise(*this->odomPub);

  /* Address set odom service */
  this->setOdomTopic = String("/") + this->heroName + String("/set_odom");                                                                                                              /* Update service name */
  this->setOdomService = new ros::ServiceServer<hero_common::SetOdom::Request, hero_common::SetOdom::Response, Odometry>(this->setOdomTopic.c_str(), &Odometry::setOdomCallback, this); /* Instantiate service */
  this->nh_->advertiseService(*this->setOdomService);                                                                                                                                   /* Address set odom service */
}

void Odometry::setRate(unsigned long rate) {
  this->rate = rate;
}


void Odometry::update(void) {
  this->update(this->rate);
}

/* Update and publish odom data */
void Odometry::update(unsigned long rate) {
#ifdef __IMU_SENSOR_H__

  if (millis() - this->imuBiasTimer < 15000) {
    this->imuBias = this->imuSensor->get() - this->imuInitValue;
  }
#endif
  if ((millis() - this->timer) > (1000 / rate)) {
    this->compute();
    /* Publish odometry */
    this->odomMessage.header.stamp = this->nh_->now();
    this->odomPub->publish(&this->odomMessage);
    /* Tf tree */
    this->computeTf();
    this->timer = millis();
  }
}

/* Compute Odometry */
void Odometry::compute() {
  this->deltaTheta = (this->wheelEncoder->getMessage().right_dist - this->wheelEncoder->getMessage().left_dist) / WHEEL_SEPARATION; /* Expressed in radiant. */
  this->deltaSteps = (this->wheelEncoder->getMessage().right_dist + this->wheelEncoder->getMessage().left_dist) / (2.0);            /* meter per seconds */

  this->odomMessage.pose.pose.position.x += this->deltaSteps * cos(this->poseMessage.theta + this->deltaTheta / 2.0);
  this->poseMessage.x = this->odomMessage.pose.pose.position.x;
  this->odomMessage.pose.pose.position.y += this->deltaSteps * sin(this->poseMessage.theta + this->deltaTheta / 2.0);
  this->poseMessage.y = this->odomMessage.pose.pose.position.y;
  this->odomMessage.pose.pose.position.z = 0.0;

  this->poseMessage.theta += this->deltaTheta; /* Expressed in radiant. */
  if (this->poseMessage.theta > M_PI) this->poseMessage.theta -= 2.0 * M_PI;
  if (this->poseMessage.theta < -M_PI) this->poseMessage.theta += 2.0 * M_PI;

    /* Since all odometry is 6DOF we'll need a quaternion created from yaw. */
#ifdef __IMU_SENSOR_H__
  //  this->poseMessage.theta = 0.95 * (-this->imuSensor->get() + this->yaw_0) + 0.05 * this->poseMessage.theta;
  //this->odomMessage.twist.twist.linear.y = this->poseMessage.theta;
  if (this->imuSensor->isEnable()) {
    this->poseMessage.theta = -this->imuSensor->get() + this->imuBias;
  }
  //this->odomMessage.twist.twist.linear.z = this->poseMessage.theta;
#endif
  this->odomMessage.pose.pose.orientation = tf::createQuaternionFromYaw(this->poseMessage.theta);



  /* Robot linear speed in m/s */
  this->odomMessage.twist.twist.linear.x = (this->wheelEncoder->getMessage().right_speed_filtered + this->wheelEncoder->getMessage().left_speed_filtered) / 2.0f;
  /* Wheel speed in m/s */

  /* Robot angular speed in rad/s */
  this->odomMessage.twist.twist.angular.z = (this->wheelEncoder->getMessage().right_speed_filtered - this->wheelEncoder->getMessage().left_speed_filtered) / WHEEL_SEPARATION;
}

/* Compute Transformation tree */
void Odometry::computeTf() {
  /* tf odom -> base_link */
  this->t.header.frame_id = this->odomFrame.c_str();
  this->t.child_frame_id = this->baseFrame.c_str();
  this->t.transform.translation.x = this->odomMessage.pose.pose.position.x;
  this->t.transform.translation.y = this->odomMessage.pose.pose.position.y;
  this->t.transform.translation.z = 0;
  this->t.transform.rotation = tf::createQuaternionFromYaw(this->poseMessage.theta);
  this->t.header.stamp = this->odomMessage.header.stamp;
  this->broadcaster.sendTransform(this->t);

  /* tf base_link -> left_wheel_link */
  this->t.header.frame_id = this->baseFrame.c_str();
  this->t.child_frame_id = this->leftWheelFrame.c_str();
  this->t.transform.translation.x = 0;
  this->t.transform.translation.y = WHEEL_SEPARATION / 2.0;
  this->t.transform.translation.z = 0.01548f;
  double left_wheel_angle = (double)((((long)this->wheelEncoder->getMessage().left_ticks % 288) + 1) * 2 * M_PI / 288);
  this->t.transform.rotation.x = 0.0;
  this->t.transform.rotation.y = sin(left_wheel_angle / 2.0);  // Only pitch
  this->t.transform.rotation.z = 0.0;
  this->t.transform.rotation.w = cos(left_wheel_angle / 2.0);
  this->t.header.stamp = this->odomMessage.header.stamp;
  this->broadcaster.sendTransform(this->t);

  /* tf base_link -> right_wheel_link */
  this->t.header.frame_id = this->baseFrame.c_str();
  this->t.child_frame_id = this->rightWheelFrame.c_str();
  this->t.transform.translation.x = 0;
  this->t.transform.translation.y = -WHEEL_SEPARATION / 2.0;
  this->t.transform.translation.z = 0.01548;
  double right_wheel_angle = (double)((((long)this->wheelEncoder->getMessage().right_ticks % 288) + 1) * 2 * M_PI / 288);
  this->t.transform.rotation.x = 0.0;
  this->t.transform.rotation.y = sin(right_wheel_angle / 2.0);  // Only pitch
  this->t.transform.rotation.z = 0.0;
  this->t.transform.rotation.w = cos(right_wheel_angle / 2.0);
  this->t.header.stamp = this->odomMessage.header.stamp;
  this->broadcaster.sendTransform(this->t);

  /* tf base_link -> hat_link */
  this->t.header.frame_id = this->baseFrame.c_str();
  this->t.child_frame_id = this->hatFrame.c_str();
  this->t.transform.translation.x = -0.00245;
  this->t.transform.translation.y = -0.00216;
  this->t.transform.translation.z = 0.051;
  this->t.transform.rotation.x = 0.0;
  this->t.transform.rotation.y = 0.0;
  this->t.transform.rotation.z = 0.0;
  this->t.transform.rotation.w = 1.0;
  this->t.header.stamp = this->odomMessage.header.stamp;
  this->broadcaster.sendTransform(this->t);

  /* tf base_link -> laser_link */
  this->t.header.frame_id = this->baseFrame.c_str();
  this->t.child_frame_id = this->laserFrame.c_str();
  this->t.transform.translation.x = 0.0;
  this->t.transform.translation.y = 0.0;
  this->t.transform.translation.z = 0.051;
  this->t.transform.rotation.x = 0.0;
  this->t.transform.rotation.y = 0.0;
  this->t.transform.rotation.z = 0.0;
  this->t.transform.rotation.w = 1.0;
  this->t.header.stamp = this->odomMessage.header.stamp;
  this->broadcaster.sendTransform(this->t);
}


/* Set odometry initial position */
void Odometry::setOdomCallback(const hero_common::SetOdom::Request &req, hero_common::SetOdom::Response &res) {
  this->wheelEncoder->clear();

  this->odomMessage.pose.pose.position.x = req.x;
  this->odomMessage.pose.pose.position.y = req.y;
  this->odomMessage.pose.pose.position.z = req.theta;
  this->odomMessage.pose.pose.orientation = tf::createQuaternionFromYaw(req.theta);

  this->poseMessage.x = req.x;
  this->poseMessage.y = req.y;
  this->poseMessage.theta = req.theta;

  res.success = 1;
  res.message = "Odometry was changed!";
  this->nh_->loginfo("[HERO] Odometry was changed!");
}
