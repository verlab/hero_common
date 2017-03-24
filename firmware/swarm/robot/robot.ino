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
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h" // 
//#include "printf.h"
#include <Servo.h>
/************************************************************************/

/************************************************************************
 * Defines
 ************************************************************************/
/* Robot Identification Setup */
#define ROBOT_ID  11      /* Robot ID */

/* Wheel Setup */
#define WHEEL_R_PIN 6     /* Pin to connect right motor */
#define WHEEL_R_MID 1545  /* Neutral position of right motor */
#define WHEEL_L_PIN 7     /* Pin to connect left motor */
#define WHEEL_L_MID 1500  /* Neutral position of left motor */

/* Radio Setup */
#define READ_ADDRESS 0xF0F0F0F0D2LL  /* Radio pipe address to read */
#define WRITE_ADDRESS 0xF0F0F0F0E1LL /* Radio pipe address to write */

/* Messages types */
#define COMMAND_TYPE 50         /* Describe the type of message */
#define SENSOR_TYPE 100         /* Describe the type of message */
#define REQUEST_TYPE 150        /* Describe the type of message */
#define IDENTIFICATION_TYPE 200 /* Describe the type of message */
/************************************************************************/

/************************************************************************
 * Protocols
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
 * Interrupt handler, check the radio because we got an IRQ
 ************************************************************************/
void check_radio(void);
/************************************************************************/

/************************************************************************
 * Servo motor driver
 ************************************************************************/
Servo wheel_right, wheel_left;
/************************************************************************/

/************************************************************************
 * Arduino Setup
 ************************************************************************/
void setup() {
  /* Serial initialization */
  //Serial.begin(115200);
  //printf_begin();
  //printf("[Robot] Starting Robot Node\n");

  /* Setup servo motor */
  wheel_right.attach(WHEEL_R_PIN);
  wheel_left.attach(WHEEL_L_PIN);
 
  wheel_right.writeMicroseconds(WHEEL_R_MID);
  wheel_left.writeMicroseconds(WHEEL_L_MID);
  
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

  /* Open pipes to other nodes for communication */
  radio.openWritingPipe(WRITE_ADDRESS);
  delayMicroseconds(150);
  radio.openReadingPipe(1, READ_ADDRESS);
  delayMicroseconds(150);

  /* Start listening */
  radio.startListening();

  /* Dump the configuration of the rf unit for debugging */
  radio.printDetails();

  /* Attach interrupt handler to interrupt #0 (using pin 2) on BOTH the sender and receiver */
  attachInterrupt(0, check_radio, FALLING);

  /* Publish to the sink the id of this robot */
  radio.stopListening();
  Message_t msg = {ROBOT_ID, IDENTIFICATION_TYPE, 0, 0};
  while (!radio.write(&msg, sizeof(Message_t))) delayMicroseconds(500);
  radio.startListening();
}
/************************************************************************/

/************************************************************************
 * M A I N  L O 0 P
 ************************************************************************/
void loop() {
  /* Do nothing */
  /* Non-blocking write to the open writing pipe. */
  //radio.startWrite(&id, sizeof(uint8_t));
}
/************************************************************************/

/************************************************************************
 * C A L L B A C K S
 ************************************************************************/
void check_radio(void){
  /* Call this when you get an interrupt to find out why. 
   * Tells you what caused the interrupt, and clears the state of interrupts. 
   */
  bool tx_ok, tx_fail, rx_ready;
  radio.whatHappened ( tx_ok, tx_fail, rx_ready );

  /* Check the read pipe for message */
  if (rx_ready || radio.available()){
    /* Read the message */
    Message_t msg;
    radio.read( &msg, sizeof(Message_t));
    
    //printf("[ROBOT] Message type %d\n", msg._type);

    /* Check if it is to this robot */
    if (msg._id != ROBOT_ID){ // message isn't to me
      //printf("[Status] Msg isn't to me!\n");
      return;
    }
    
    switch(msg._type){
      case COMMAND_TYPE:
        /* Control the wheels */
        wheel_right.writeMicroseconds(WHEEL_R_MID + map((int)msg._data1, -127, 127, -500, 500));
        wheel_left.writeMicroseconds(WHEEL_L_MID + map((int)msg._data2, -127, 127, -500, 500));
        
        //printf("----------------------\n");
        //printf("[Status] Become data:\n");  
        //printf("[Status] Data: {%d, %d, %d}\n", msg._id, msg._data1, msg._data2);
        //printf("----------------------\n");
      break;
      case REQUEST_TYPE:
        // Send data requested
        msg = {ROBOT_ID, SENSOR_TYPE, 16, 0};
        radio.stopListening();
        radio.write(&msg, sizeof(Message_t));
        radio.startListening();
      break;
      default:
      break;
    }
  }
  
}
/************************************************************************/
/* T H E  E N D */
/************************************************************************/
