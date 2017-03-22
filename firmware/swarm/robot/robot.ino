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
#include "printf.h"
#include <Servo.h>
/************************************************************************/

/************************************************************************
 * Robot ID
 ************************************************************************/
uint8_t id = 11;
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
 * Interrupt handler, check the radio because we got an IRQ
 ************************************************************************/
void check_radio(void);
/************************************************************************/

/************************************************************************
 * Servo motor driver
 ************************************************************************/
Servo empty, wheel_right, wheel_left;
int wheel_right_m = 1545;
int wheel_left_m = 1500;
/************************************************************************/

/************************************************************************
 * Arduino Setup
 ************************************************************************/
void setup() {
  /* Serial initialization */
  Serial.begin(115200);
  printf_begin();
  printf("[Status] Starting Robot Node\n");

  /* Setup servo motor */
  wheel_right.attach(6);
  wheel_left.attach(7);
 
  wheel_right.writeMicroseconds(wheel_right_m);
  wheel_left.writeMicroseconds(wheel_left_m);
  
  /* Setup and configure rf radio */
  radio.begin();

  /* Set the PA Level low to prevent power supply related issues since this is a
   * getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
   */
  radio.setPALevel(RF24_PA_LOW);
  
  /* optionally, increase the delay between retries & # of retries */
  //radio.setRetries(15,15);

  /* optionally, reduce the payload size.  seems to improve reliability */
  //radio.setPayloadSize(sizeof(Protocol));
  
  /* Enable custom payloads on the acknowledge packets.
   * Ack payloads are a handy way to return data back to senders without manually changing the radio modes on both units.
   */
  radio.enableAckPayload();

  /* Open pipes to other nodes for communication */
  radio.openWritingPipe(address[1]);
  delay(15);
  radio.openReadingPipe(1, address[0]);
  delay(15);

  /* Start listening */
  radio.startListening();

  /* Dump the configuration of the rf unit for debugging */
  radio.printDetails();

  /* Attach interrupt handler to interrupt #0 (using pin 2) on BOTH the sender and receiver */
  attachInterrupt(0, check_radio, FALLING);

  /* Publish to the sink the id of this robot */
  radio.stopListening();
  radio.write(&id, sizeof(uint8_t));
  radio.startListening();
}
/************************************************************************/

/************************************************************************
 * M A I N  L O 0 P
 ************************************************************************/
void loop() {
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
  printf("[Status] %d %d %d %d\n", tx_ok, tx_fail, rx_ready, radio.available());

  /* Check the read pipe for message */
  if (rx_ready || radio.available()){
    /* Read the message */
    Protocol msg;
    radio.read( &msg, sizeof(Protocol));

    /* Check if it is to this robot */
    if (msg.robotId != id){ // message isn't to me
      printf("[Status] Msg isn't to me!\n");
      return;
    }
    
    /* Control the wheels */
    int wheel_right_data = wheel_right_m + map((int)msg.data1, -127, 127, -500, 500);
    int wheel_left_data = wheel_left_m + map((int)msg.data2, -127, 127, -500, 500);
    wheel_right.writeMicroseconds(wheel_right_data);
    wheel_left.writeMicroseconds(wheel_left_data);
    
    printf("----------------------\n");
    printf("[Status] Become data:\n");  
    printf("[Status] Data: {%d, %d, %d}\n", msg.robotId, wheel_right_data, wheel_left_data);
    printf("----------------------\n");
    
    radio.stopListening();
    radio.write(&id, sizeof(uint8_t));
    radio.startListening();
  }
  
}
/************************************************************************/
/* T H E  E N D */
/************************************************************************/
