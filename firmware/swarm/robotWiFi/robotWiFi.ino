/*
 ************************************************************************
 *  R O B O T  F I R M W A R E
 ************************************************************************
 *
 * Paulo Rezeck <rezeck@dcc.ufmg.br>
 * Hector Azpurua <hectorxxx@gmail.com>
 * 
 * Project Swarm
 * Computer Vision and Robotics Lab
 * Federal University of Minas Gerais - Brazil
 ************************************************************************/
 
/************************************************************************/
#include <ros.h>
#include <WifiHardware.h>
#include <Servo.h>
/* Message types */
#include <swarm_driver/Velocity.h>
#include <swarm_driver/Proximity.h>
#include <swarm_driver/Led.h>
/************************************************************************/

/************************************************************************
 * Defines
 ************************************************************************/
/* Robot Identification Setup */
#define ROBOT_NAME  "/hero_1"

/* Wheel pinout Setup */
#define WHEEL_R_PIN 6     /* Pin to connect right motor */
#define WHEEL_R_MID 1545  /* Neutral position of right motor */
#define WHEEL_L_PIN 7     /* Pin to connect left motor */
#define WHEEL_L_MID 1500  /* Neutral position of left motor */
/************************************************************************/

/************************************************************************
 * Servo motor driver
 ************************************************************************/
Servo wheel_right, wheel_left;
/************************************************************************/

/************************************************************************
 * ROS Setup
 ************************************************************************/
ros::NodeHandle_<WifiHardware> nh;

void velocity_cb(const swarm_driver::Velocity& msg);
void led_cb(const swarm_driver::Led& msg);

ros::Subscriber<swarm_driver::Velocity> velocity_sub("swarm/cmd_vel", velocity_cb);
ros::Subscriber<swarm_driver::Led> led_sub("swarm/led", led_cb);

swarm_driver::Proximity proximity_msg;
ros::Publisher proximity_pub("/swarm/proximity", &proximity_msg);
/************************************************************************/

/************************************************************************
 * Arduino Setup
 ************************************************************************/
void setup() {
  /* Starting ros node */
  nh.initNode();
  nh.advertise(proximity_pub);
  nh.subscribe(velocity_sub);
  nh.subscribe(led_sub);
}
/************************************************************************/

/************************************************************************
 * M A I N  L O 0 P
 ************************************************************************/
void loop(){
  proximity_msg.proximity_1 = 190;
  proximity_msg.proximity_2 = 100;
  proximity_msg.proximity_3 = 10;
  proximity_pub.publish( &proximity_msg );
  
  nh.spinOnce();
  delayMicroseconds(10);
}
/************************************************************************/

/************************************************************************
 * C A L L B A C K S
 ************************************************************************/
void velocity_cb(const swarm_driver::Velocity& msg){
}

void led_cb(const swarm_driver::Led& msg){
  /* set led with respective colors */
}
/************************************************************************/
/* T H E  E N D */
/************************************************************************/
