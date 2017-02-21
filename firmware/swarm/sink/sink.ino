/*
 ********************************   
 *  S I N K  F I R M W A R E
 ********************************
 *
 * Paulo Rezeck <rezeck@dcc.ufmg.br>
 * Hector Azpurua <hectorxxx@gmail.com>
 * 
 * Project Swarm
 * Computer Vision and Robotics Lab
 * Federal University of Minas Gerais - Brazil
 */

#include <ros.h>
#include <swarm_driver/Command.h>

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

/*
 * Device ID
 */
#define ID 00

/*
 * Protocol
 */
 struct Protocol{
    uint8_t robotId;
    uint8_t data1;
    uint8_t data2;
  };

/*
 * Hardware Configuration
 * Set up nRF24L01 radio on SPI bus plus pins 9 & 10
 */
RF24 radio(9,10);

/* 
 * Topology 
 * Radio pipe addresses for the 2 nodes to communicate.
 */
const uint64_t address[] = {0xF0F0F0F0D2LL, 0xF0F0F0F0E1LL};

/*
 * Setup time to write data to the pipe
 */
byte msgCounter = 0;
unsigned long writeTime, timeout = 200;


/*
 * ROS Setup
 */
ros::NodeHandle nh;

void callback(const swarm_driver::Command& msg){
  radio.stopListening();

  // Send the control data.
  Protocol p = {msg.robot_id, msg.wheel_right, msg.wheel_left};
  bool ok = radio.write(&p, sizeof(Protocol));    
  
  // Now, resume listening so we catch the next packets.
  radio.startListening();
}
ros::Subscriber<swarm_driver::Command> sub("swarm/command", callback);


void setup() {
  //Serial.begin(57600);
  //printf_begin();
  //printf("[Status] Starting Sink Node\n");
  // Starting ros node
  nh.initNode();
  nh.subscribe(sub);

  // Setup and configure rf radio
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  
  // optionally, increase the delay between retries & # of retries
  //radio.setRetries(15,15);

  // optionally, reduce the payload size.  seems to improve reliability
  radio.setPayloadSize(sizeof(Protocol));

  // Open pipes to other nodes for communication
  delay(150);
  radio.openWritingPipe(address[1]);
  delay(15);
  
  //radio.openReadingPipe(1, read_pipe);
  //delay(15);

  // Start listening
  //radio.startListening();

  // Dump the configuration of the rf unit for debugging
  radio.printDetails();
  //delay(5000);

  // Get current time configuration to write
  //writeTime = millis();
}

void loop() {
  // if there is data ready
  //if ( radio.available() && (millis() - writeTime) <= timeout){
    //Protocol msg;
    //radio.read( &msg, sizeof(Protocol));
    //printf("Become %b\n", msg.RobotId);  
  //}
  //else{
     // First, stop listening so we can talk.
     //radio.stopListening();

     // Send the control data.
     //printf("----------------------\n");
     //printf("Sending control datas:\n");
     //Protocol msg = {7, wheelR, wheelL};
     //printf("[Status] Created Data: {%d, %d, %d, %d}\n", msg.robotId, msg.msgId, msg.data1, msg.data2);
     //bool ok = radio.write(&msg, sizeof(Protocol));
     
     //if (ok){
      //printf("[Status] Message sent.\n");
      //msgCounter++;
     //}else{
      //printf("[Status] Cannot send this message.\n");
     //}
     //printf("----------------------\n");

    // Now, resume listening so we catch the next packets.
    //radio.startListening();

    //writeTime = millis();
  // Sync time
  nh.spinOnce();
  delay(10);
}
