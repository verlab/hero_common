/*
 ********************************   
 *  R O B O T  F I R M W A R E
 ********************************
 *
 * Paulo Rezeck <rezeck@dcc.ufmg.br>
 * Hector Azpurua <hectorxxx@gmail.com>
 * 
 * Project Swarm
 * Computer Vision and Robotics Lab
 * Federal University of Minas Gerais - Brazil
 */

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

#include <Servo.h>
/*
 * Robot ID
 */
#define ID 007

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
unsigned long writeTime, timeout = 200;
Servo wheelR;

void setup() {
  Serial.begin(57600);
  printf_begin();
  printf("[Status] Starting Robot Node\n");
  wheelR.attach(6);

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
  //radio.openWritingPipe(write_pipe);
  //delay(15);
  
  radio.openReadingPipe(1, address[1]);
  delay(15);

  // Start listening
  radio.startListening();

  // Dump the configuration of the rf unit for debugging
  radio.printDetails();
  //delay(5000);

  // Get current time configuration to write
  writeTime = millis();
}

void loop() {
  // if there is data ready
  while ( radio.available()){ //&& (millis() - writeTime) <= timeout){
    Protocol msg;
    radio.read( &msg, sizeof(Protocol));
    if (msg.robotId != ID){ // msg isn't to me
      break;
    }
    printf("----------------------\n");
    printf("[Status] Become data:\n");  
    printf("[Status] Data: {%d, %d, %d}\n", msg.robotId, msg.data1, msg.data2);
    wheelR.write((int)msg.data1);
    printf("----------------------\n");
  }
  //else{
    // First, stop listening so we can talk.
//    radio.stopListening();
//
//     // Send the control data.
//     printf("Sending control datas...\n");
//     Protocol msg = {0, 0, 90, 90};
//     radio.write( &msg, sizeof(Protocol) );
//
//    // Now, resume listening so we catch the next packets.
//    radio.startListening();

    //writeTime = millis();
  //}
  // Sync time
  delay(2);
}
