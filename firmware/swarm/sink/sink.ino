/*
 ************************************************************************
 *  S I N K  F I R M W A R E
 ************************************************************************
 *
 * Paulo Rezeck <rezeck@dcc.ufmg.br>
 * Hector Azpurua <hectorxxx@gmail.com>
 * 
 * Project Swarm
 * Computer Vision and Robotics Lab - VERLAB
 * Federal University of Minas Gerais - Brazil
 ************************************************************************/
 
/************************************************************************/
#include <ros.h>
#include <swarm_driver/Command.h>
#include <swarm_driver/Sensors.h>
#include <std_msgs/UInt8.h>
/************************************************************************/
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
//#include "printf.h"
/************************************************************************/

/************************************************************************
 * Defines
 ************************************************************************/
/* Sink Identification */
#define SINK_ID 00

/* LED PINOUT */
#define RED_LED_PIN 8

/* Radio Setup */
#define READ_ADDRESS 0xF0F0F0F0E1LL  /* Radio pipe address to read */
#define WRITE_ADDRESS 0xF0F0F0F0D2LL /* Radio pipe address to write */

/* Messages types */
#define COMMAND_TYPE 50         /* Describe the type of message */
#define SENSOR_TYPE 100         /* Describe the type of message */
#define REQUEST_TYPE 150        /* Describe the type of message */
#define IDENTIFICATION_TYPE 200 /* Describe the type of message */
/************************************************************************/

/************************************************************************
 * Protocol
 ************************************************************************/
struct Message_t{
  uint8_t _id;
  uint8_t _type;
  int8_t _data1;
  int8_t _data2;
};
/************************************************************************/

/************************************************************************
 * Hardware Configuration
 * Set up nRF24L01 radio on SPI bus plus pins 9 & 10
 * <http://maniacbug.github.io/RF24/classRF24.html>
 ************************************************************************/
RF24 radio(9,10);
/************************************************************************/

/************************************************************************
 * ROS Setup
 * <http://wiki.ros.org/rosserial_arduino/Tutorials>
 ************************************************************************/
ros::NodeHandle nh;

void command_cb(const swarm_driver::Command& cmd);
void request_cb(const std_msgs::UInt8& _id);

ros::Subscriber<swarm_driver::Command> command_sub("swarm/command", command_cb);
ros::Subscriber<std_msgs::UInt8> request_sub("swarm/request", request_cb);

std_msgs::UInt8 id_msg;
ros::Publisher id_pub("swarm/id", &id_msg);

swarm_driver::Sensors sensor_msg;
ros::Publisher sensor_pub("swarm/sensor", &sensor_msg);

/************************************************************************/

/************************************************************************
 * Arduino Setup
 ************************************************************************/
void setup() {
  /* Serial initialization */
  //Serial.begin(57600);
  //printf_begin();
  //printf("[Status] Starting Sink Node\n");

  /* Pinout setup */
  pinMode(RED_LED_PIN, OUTPUT);
  
  /* Starting ros node */
  nh.initNode();
  nh.advertise(id_pub);
  nh.advertise(sensor_pub);
  
  nh.subscribe(command_sub);
  nh.subscribe(request_sub);

  /* Change the rosserial baud rate - Not working */
  //nh.getHardware()->setBaud(115200);
  
  /* Setup and configure rf radio */
  radio.begin();

  /* Set the PA Level low to prevent power supply related issues since this is a
   * getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default. 
   */
  radio.setPALevel(RF24_PA_LOW);

  /* Set speed rate RF24_250KBPS for 250kbs, RF24_1MBPS for 1Mbps, or RF24_2MBPS for 2Mbps */
  radio.setDataRate(RF24_2MBPS);
  
  /* optionally, increase the delay between retries & # of retries */
  radio.setRetries(15,15);

  /* optionally, reduce the payload size.  seems to improve reliability */
  radio.setPayloadSize(sizeof(Message_t));

  /* Enable custom payloads on the acknowledge packets.
   * Ack payloads are a handy way to return data back to senders without manually changing the radio modes on both units.
   */
  radio.enableAckPayload();

  /* 
   * Open pipes to other nodes for communication 
   */
  radio.openWritingPipe(WRITE_ADDRESS);
  delayMicroseconds(150);
  radio.openReadingPipe(0, READ_ADDRESS);
  radio.openReadingPipe(1, READ_ADDRESS);
  radio.openReadingPipe(2, READ_ADDRESS);
  radio.openReadingPipe(3, READ_ADDRESS);
  radio.openReadingPipe(4, READ_ADDRESS);
  radio.openReadingPipe(5, READ_ADDRESS);
  delayMicroseconds(150);

  /* Start listening */
  radio.startListening();

  /* Dump the configuration of the rf unit for debugging */
  radio.printDetails();
  
  /* Start led with high */
  digitalWrite(RED_LED_PIN, HIGH);  
}
/************************************************************************/

/************************************************************************
 * M A I N  L O 0 P
 ************************************************************************/
void loop() {
  /* Check the read pipe for messages and publish to ROS environment */
  if(radio.available()){
    Message_t msg;
    radio.read(&msg, sizeof(Message_t));
    switch(msg._type){
      case SENSOR_TYPE:
        sensor_msg.robot_id = msg._id;
        sensor_msg.data = msg._data1;
        sensor_pub.publish(&sensor_msg);
      break;
      case IDENTIFICATION_TYPE:
        id_msg.data = msg._id;
        id_pub.publish(&id_msg);
        digitalWrite(RED_LED_PIN, HIGH-digitalRead(RED_LED_PIN));   
      break;
      default:
      break;
    }
  }
  
  /* Sync ROS System */
  nh.spinOnce();
}
/************************************************************************/

/************************************************************************
 * C A L L B A C K S
 ************************************************************************/
void command_cb(const swarm_driver::Command& cmd){
  /* First, stop listening so we can talk. */
  radio.stopListening();
  /* Copy datas from ROS interface */
  Message_t msg = {cmd.robot_id, COMMAND_TYPE, cmd.wheel_right, cmd.wheel_left};
  /* Write to radio */
  bool ok = radio.write(&msg, sizeof(Message_t));
  /* Now, resume listening so we catch the next packets. */
  radio.startListening();
  /* Blink once if message could be sent */
  if (ok){
    digitalWrite(RED_LED_PIN, HIGH-digitalRead(RED_LED_PIN));   
  }
}

void request_cb(const std_msgs::UInt8& _id){
  /* First, stop listening so we can talk. */
  radio.stopListening();
  /* Copy datas from ROS interface */
  Message_t msg = {_id.data, REQUEST_TYPE, 0, 0};
  /* Write to radio */
  bool ok = radio.write(&msg, sizeof(Message_t));
  /* Now, resume listening so we catch the next packets. */
  radio.startListening();
  /* Blink once if message could be sent */
  if (ok){
    digitalWrite(RED_LED_PIN, HIGH-digitalRead(RED_LED_PIN));   
  }
}
/************************************************************************/
/* T H E  E N D */
/************************************************************************/
