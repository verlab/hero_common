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
#include <std_msgs/UInt8.h>
/************************************************************************/
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
/************************************************************************/

/************************************************************************
 * Defines
 ************************************************************************/
#define SINK_ID 00
#define LED_PIN 8
/************************************************************************/

/************************************************************************
 * Protocol
 ************************************************************************/
 struct Protocol{
    uint8_t robotId;
    int8_t data1;
    int8_t data2;
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
 * Topology 
 * Radio pipe addresses for the 2 nodes to communicate.
 ************************************************************************/
const uint64_t address[] = {0xF0F0F0F0D2LL, 0xF0F0F0F0E1LL};
/************************************************************************/

/************************************************************************
 * ROS Setup
 ************************************************************************/
ros::NodeHandle nh;

void callback(const swarm_driver::Command& msg);
ros::Subscriber<swarm_driver::Command> sub("swarm/command", callback);

std_msgs::UInt8 receive_id;
ros::Publisher swarm_id("swarm/id", &receive_id);
/************************************************************************/

/************************************************************************
 * Arduino Setup
 ************************************************************************/
void setup() {
  /* Serial initialization */
  Serial.begin(57600);
  printf_begin();
  printf("[Status] Starting Sink Node\n");

  /* Pinout setup */
  pinMode(LED_PIN, OUTPUT);
  
  /* Starting ros node */
  nh.initNode();
  nh.advertise(swarm_id);
  nh.subscribe(sub);

  /* Setup and configure rf radio */
  radio.begin();

  /* Set the PA Level low to prevent power supply related issues since this is a
   * getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default. 
   */
  radio.setPALevel(RF24_PA_LOW);
  
  /* optionally, increase the delay between retries & # of retries */
  //radio.setRetries(15,15);

  radio.enableAckPayload();
  /* optionally, reduce the payload size.  seems to improve reliability */
  //radio.setPayloadSize(sizeof(Protocol));

  /* 
   * Open pipes to other nodes for communication 
   */
  radio.openWritingPipe(address[0]);
  delay(15);
  radio.openReadingPipe(1, address[1]);
  delay(15);

  /* Start listening */
  radio.startListening();

  /* Dump the configuration of the rf unit for debugging */
  radio.printDetails();
  
  /* Start led with high */
  digitalWrite(LED_PIN, HIGH);  
}
/************************************************************************/

/************************************************************************
 * M A I N  L O 0 P
 ************************************************************************/
void loop() {
  /* Check the read pipe for messages */
  if(radio.available()){    
    uint8_t data;
    radio.read( &data, sizeof(uint8_t));
    if (data > 0){
      receive_id.data = data;
      swarm_id.publish(&receive_id);
      //printf("[Status]Found robot number #%d\n", data);
    }
  }

  /* Sync ROS System */
  nh.spinOnce();
}
/************************************************************************/

/************************************************************************
 * C A L L B A C K S
 ************************************************************************/
void callback(const swarm_driver::Command& msg){
  /* First, stop listening so we can talk. */
  radio.stopListening();
  /* Copy datas from ROS interface */
  Protocol pkt = {msg.robot_id, msg.wheel_right, msg.wheel_left};
  /* Write to radio */
  bool ok = radio.write(&pkt, sizeof(Protocol));
  /* Now, resume listening so we catch the next packets. */
  radio.startListening();
  /* Blink once if message could be sent */
  if (ok){
    digitalWrite(LED_PIN, HIGH-digitalRead(LED_PIN));   
  }
}
/************************************************************************/
/* T H E  E N D */
/************************************************************************/
