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
#define VELOCITY_TOPIC "/hero_1/cmd_vel"
#define LED_TOPIC "/hero_1/led"
#define PROXIMITY_TOPIC "/hero_1/proximity"

/* Wheel pinout Setup */
#define WHEEL_R_PIN 4     /* Pin to connect right motor pin D1*/
#define WHEEL_R_MID 1585  /* Neutral position of right motor */
#define WHEEL_L_PIN 5     /* Pin to connect left motor pin D2*/
#define WHEEL_L_MID 1565  /* Neutral position of left motor  */

#define WHEEL_DIAMETER 6.64
#define WHEEL_SEPARATION 6.6

#define IR1_PIN 0 /* Proximity sensor 1 Pin D3 */
#define IR2_PIN 2 /* Proximity sensor 1 Pin D4 */
#define IR3_PIN 14 /* Proximity sensor 1 Pin D5 */
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


ros::Subscriber<swarm_driver::Velocity> velocity_sub(VELOCITY_TOPIC, velocity_cb);
ros::Subscriber<swarm_driver::Led> led_sub(LED_TOPIC, led_cb);

swarm_driver::Proximity proximity_msg;
ros::Publisher proximity_pub(PROXIMITY_TOPIC, &proximity_msg);
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

  proximity_msg.header.frame_id = ROBOT_NAME;

  /* Setup servo motor */
  wheel_right.attach(WHEEL_R_PIN);
  wheel_left.attach(WHEEL_L_PIN);
 
  wheel_right.writeMicroseconds(WHEEL_R_MID);
  wheel_left.writeMicroseconds(WHEEL_L_MID);

  pinMode(IR1_PIN, INPUT); /* Connect the proximities sensors */
  pinMode(IR2_PIN, INPUT);
  pinMode(IR3_PIN, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  delay(1000);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);                      // Wait for two seconds (to demonstrate the active low LED)
}
/************************************************************************/

/************************************************************************
 * M A I N  L O 0 P
 ************************************************************************/
void loop(){
  proximity_msg.header.stamp = nh.now();
  proximity_msg.proximity_1 = (int8_t)readIR(IR1_PIN);
  proximity_msg.proximity_2 = (int8_t)readIR(IR2_PIN);
  proximity_msg.proximity_3 = (int8_t)readIR(IR3_PIN);
  proximity_pub.publish( &proximity_msg );
  
  nh.spinOnce();
  //delayMicroseconds(1000);
}
/************************************************************************/

/************************************************************************
 * C A L L B A C K S
 ************************************************************************/
void velocity_cb(const swarm_driver::Velocity& msg){
  /* set motor velocities */
  float linear = _max(_min(msg.linear, WHEEL_DIAMETER), -WHEEL_DIAMETER);
  float angular = _max(_min(msg.angular, 2*WHEEL_DIAMETER/WHEEL_SEPARATION), -2*WHEEL_DIAMETER/WHEEL_SEPARATION);

  float wl = (linear - ((float)WHEEL_SEPARATION/2.0) * angular) / (float)WHEEL_DIAMETER;
  float wr = (linear + ((float)WHEEL_SEPARATION/2.0) * angular) / (float)WHEEL_DIAMETER;

  wr = _map(wr, -2.0, 2.0, -500, 500);
  wl = _map(wl, -2.0, 2.0, -500, 500);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   // Turn the LED on (Note that LOW is the voltage level
  
  /* Control the wheels */
  wheel_right.writeMicroseconds(int(WHEEL_R_MID) + (int)wr);
  wheel_left.writeMicroseconds(int(WHEEL_L_MID) + (int)wl);
}

void led_cb(const swarm_driver::Led& msg){
  /* set led with respective colors */
}

int _map(float x, float xmin, float xmax, float ymin, float ymax){
  return (int)((ymax-ymin)*x/(xmax-xmin) + ymin);
}


int readIR(int pin){
  analogWrite(pin, 1024);  // lit the diode
  delayMicroseconds(5);  // diode should power up in 100 us  
  int data = analogRead(A0);
  analogWrite(pin, 0);  // dim the diode
  return data;
}
/************************************************************************/
/* T H E  E N D */
/************************************************************************/
