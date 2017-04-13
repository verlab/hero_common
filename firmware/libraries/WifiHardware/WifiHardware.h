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

#ifndef __WIFIHARDWARE_H__
#define __WIFIHARDWARE_H__

#include <ESP8266WiFi.h>

class WifiHardware{
	char* ssid;
	char* password;
	/* ROS Master IP */
	IPAddress server;
	WiFiClient client;

	public:
	WifiHardware(void);

	/* Connecting to ROS server. This probably includes TCP server/client setup. */
	void init();

	/* This method reads a byte from the TCP connection and returns it you may 
	* return -1 is there is an error; for example if the TCP connection is not open */
	int read();

	/* This method takes the arguments and writes or prints them to the TCP connection. */
	void write(uint8_t* data, int length);

	/* Returns milliseconds since start of program */
	unsigned long time();
};


#endif //__WIFIHARDWARE_H__

