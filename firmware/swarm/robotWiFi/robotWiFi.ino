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
 
#include <ros.h>
#include "WifiHardware.h"
#include <Servo.h>

/* Message types */
#include <geometry_msgs/Twist.h>
#include <swarm_driver/Proximity.h>
#include <swarm_driver/Led.h>

/************************************************************************
 * Defines
 ************************************************************************/
/* Basic setup */
#define DEBUG 1
IPAddress ROS_MASTER_ADDRESS(192, 168, 1, 10);
uint16_t ROS_MASTER_PORT = 11412;
char* WIFI_SSID = "hero";
char* WIFI_PASSWD = "hero_network";
#define ROBOT_ID "1"
#define WHEEL_DIAMETER 4.9
#define WHEEL_SEPARATION 8
float WHEEL_CIRCUNFERENCE = 3.14 * WHEEL_DIAMETER;
#define WHEEL_R_MID 1595  // Neutral position of right motor
#define WHEEL_L_MID 1585  // Neutral position of left motor
#define GAMMA_GAIN_MOTORS 15

/* Robot Identification Setup */
#define ROBOT_NAME  "/hero_" ROBOT_ID
#define VELOCITY_TOPIC "/hero_" ROBOT_ID "/cmd_vel"
#define LED_TOPIC "/hero_" ROBOT_ID "/led"
#define PROXIMITY_TOPIC "/hero_" ROBOT_ID "/proximity"

/* Wheel Setup */
#define WHEEL_R_PIN 16 //4 // Pin to connect right motor pin D1
#define WHEEL_L_PIN 5 // Pin to connect left motor pin D2

/* LED Setup */
#define IR1_PIN 4//0 /* Proximity sensor 1 Pin D3 */
#define IR2_PIN 13//2 /* Proximity sensor 1 Pin D4 */
#define IR3_PIN 12//14 /* Proximity sensor 1 Pin D5 */
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

void velocity_cb(const geometry_msgs::Twist& msg);
void led_cb(const swarm_driver::Led& msg);

ros::Subscriber<geometry_msgs::Twist> velocity_sub(VELOCITY_TOPIC, velocity_cb);
ros::Subscriber<swarm_driver::Led> led_sub(LED_TOPIC, led_cb);

swarm_driver::Proximity proximity_msg;
ros::Publisher proximity_pub(PROXIMITY_TOPIC, &proximity_msg);
/************************************************************************/

/************************************************************************
 * Arduino Setup
 ************************************************************************/
void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("      ___           ___           ___           ___     ");
  Serial.println("     /  /\\         /  /\\         /  /\\         /  /\\    ");
  Serial.println("    /  /:/        /  /::\\       /  /::\\       /  /::\\   ");
  Serial.println("   /  /:/        /  /:/\\:\\     /  /:/\\:\\     /  /:/\\:\\  ");
  Serial.println("  /  /::\\ ___   /  /::\\ \\:\\   /  /::\\ \\:\\   /  /:/  \\:\\ ");
  Serial.println(" /__/:/\\:\\  /\\ /__/:/\\:\\ \\:\\ /__/:/\\:\\_\\:\\ /__/:/ \\__\\:\\");
  Serial.println(" \\__\\/  \\:\\/:/ \\  \\:\\ \\:\\_\\/ \\__\\/~|::\\/:/ \\  \\:\\ /  /:/");
  Serial.println("      \\__\\::/   \\  \\:\\ \\:\\      |  |:|::/   \\  \\:\\  /:/ ");
  Serial.println("      /  /:/     \\  \\:\\_\\/      |  |:|\\/     \\  \\:\\/:/  ");
  Serial.println("     /__/:/       \\  \\:\\        |__|:|~       \\  \\::/   ");
  Serial.println("     \\__\\/         \\__\\/         \\__\\|         \\__\\/    ");
  Serial.println("");
  Serial.println("                                 The little swarm robot");
  Serial.println("");
  Serial.println("");
  Serial.print("Node name: ");
  Serial.println(ROBOT_ID);
  Serial.print("ROS MASTER: ");
  Serial.print(ROS_MASTER_ADDRESS);
  Serial.print(":");
  Serial.println(ROS_MASTER_PORT);
  Serial.println("HeRo authors:");
  Serial.println("\t-Paulo Rezeck rezeck@dcc.ufmg.br");
  Serial.println("\t-Hector Azpurua hector.azpurua@dcc.ufmg.br");
  Serial.println("");

  /* Setup servo motor */
  if(DEBUG) Serial.println("Setup servos ...");
  wheel_right.attach(WHEEL_R_PIN);
  wheel_left.attach(WHEEL_L_PIN);
 
  wheel_right.writeMicroseconds(WHEEL_R_MID);
  wheel_left.writeMicroseconds(WHEEL_L_MID);

  /* Connect the proximities sensors */
  if(DEBUG) Serial.println("Setup proximity sensors ...");
  pinMode(IR1_PIN, INPUT); 
  pinMode(IR2_PIN, INPUT);
  pinMode(IR3_PIN, INPUT);

  if(DEBUG) Serial.println("Init networking ...");
  nh.getHardware()->setROSConnection(ROS_MASTER_ADDRESS, ROS_MASTER_PORT);
  nh.getHardware()->connectWifi(WIFI_SSID, WIFI_PASSWD);
  
  /* Starting ros node */
  if(DEBUG) Serial.println("Init ros node ...");
  nh.initNode();
  nh.advertise(proximity_pub);
  nh.subscribe(velocity_sub);
  nh.subscribe(led_sub);

  proximity_msg.header.frame_id = ROBOT_NAME;

  /* Setup complete LED message */
  pinMode(LED_BUILTIN, OUTPUT);
  for(int i=0; i<= 6; i++){
    digitalWrite(LED_BUILTIN, LOW);
    delay(150);                   
    digitalWrite(LED_BUILTIN, HIGH);
    delay(150);        
  }
  if(DEBUG) Serial.println("Setup finished");
  delay(2000);
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
void velocity_cb(const geometry_msgs::Twist& msg){
  /* set motor velocities */

  float linear = _max(_min(msg.linear.x, WHEEL_DIAMETER), -WHEEL_DIAMETER);
  float angular = _max(_min(msg.angular.z, 2*WHEEL_DIAMETER/WHEEL_SEPARATION), -2*WHEEL_DIAMETER/WHEEL_SEPARATION);

  float wl0 = (linear - ((float) WHEEL_SEPARATION/2.0) * angular) / (float) WHEEL_DIAMETER;
  float wr0 = (linear + ((float) WHEEL_SEPARATION/2.0) * angular) / (float) WHEEL_DIAMETER;

  float wr = _map2(wr0, -2.0, 2.0, -500, 500);
  float wl = _map2(wl0, -2.0, 2.0, -500, 500);
  
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   // Turn the LED on (Note that LOW is the voltage level

  /* Control the wheels */
  wheel_right.writeMicroseconds(int(WHEEL_R_MID) - (int) wr);
  wheel_left.writeMicroseconds(int(WHEEL_L_MID) + (int) wl);
}

float _map2(float x, int xmin, int xmax, int ymin, int ymax){
  float v = (((x -xmin) / float (xmax-xmin)) * (abs(ymax) + abs(ymin))) - abs(ymin);
  if(v < ymin) v = ymin;
  if(v > ymax) v = ymax;
  return v;
}

void led_cb(const swarm_driver::Led& msg){
  /* set led with respective colors */
}

int readIR(int pin){
  analogWrite(pin, 1024);  // lit the diode
  delayMicroseconds(200);  // diode should power up in 100 us  
  int data = analogRead(A0);
  analogWrite(pin, 0);  // dim the diode
  return data;
}
/************************************************************************/
/* T H E  E N D */
/************************************************************************/
