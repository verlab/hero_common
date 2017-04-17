/*
 ************************************************************************
 *  W I F I  H A R D W A R E
 ************************************************************************
 *
 * Paulo Rezeck <rezeck@dcc.ufmg.br>
 * Hector Azpurua <hectorxxx@gmail.com>
 * 
 * Project Swarm
 * Computer Vision and Robotics Lab
 * Federal University of Minas Gerais - Brazil
 ************************************************************************/
#include "WifiHardware.h"
#include "Arduino.h"

/* Do nothing */
WifiHardware::WifiHardware(void){
	this->ssid = "******";
	this->password = "**********";
	this->server = IPAddress(150, 164, 212, 68);
}

/* Connecting to ROS server. This probably includes TCP server/client setup. */
void WifiHardware::init(){
	Serial.begin(115200);
	WiFi.begin(this->ssid, this->password);
  	Serial.print("\nConnecting to "); 
  	Serial.println(this->ssid);

  	uint8_t i = 0;
  	while (WiFi.status() != WL_CONNECTED && i++ < 20) delay(500);
  	if(i == 21){
    	Serial.print("Could not connect to"); Serial.println(this->ssid);
    	while(1) delay(500);
  	}

  	Serial.print("Ready! Use ");
  	Serial.println(WiFi.localIP());
  	delay(2000);
	client.connect(this->server, 11411);
}

/* This method reads a byte from the TCP connection and returns it you may 
return -1 is there is an error; for example if the TCP connection is not open */
int WifiHardware::read(){
	return this->client.read(); /* Will return -1 when it will works */
}

/* This method takes the arguments and writes or prints them to the TCP connection. */
void WifiHardware::write(uint8_t* data, int length) {
    for(int i=0; i<length; i++){
      this->client.write(data[i]);
  }
}

 /* Returns milliseconds since start of program */
unsigned long WifiHardware::time() {
	return millis();
}

