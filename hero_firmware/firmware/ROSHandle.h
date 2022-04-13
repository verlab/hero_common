/*
  ******************************************************************************
                      H E R O   F I R M W A R E
  ******************************************************************************
  Paulo Rezeck        <rezeck@dcc.ufmg.br>
  Mauricio Ferrari    <mauferrari@dcc.ufmg.br>
  Hector Azpurua      <hectorxxx@gmail.com>


                Computer Vision and Robotics Lab (VeRLab)
               Universidade Federal de Minas Gerais - Brazil
  ******************************************************************************
  Copyright (c) 2021 Paulo Rezeck.  All right reserved.
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  ******************************************************************************/

#ifndef __ROS_HANDLE_H__
#define __ROS_HANDLE_H__

#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

/* ROS Library */
#define ROSSERIAL_ARDUINO_TCP
#include <ros.h>

#include "LEDStatus.h"

class ROSHandle {
  private:
    LEDStatus *ledStatus;

    /* Timer Control */
    unsigned long debug_timer = 0; /* Debug timer */
    unsigned long debug_rate = DEBUG_RATE;

    /* Timer Control */
    unsigned long sync_timer = 0; /* Communication timer */
    unsigned long sync_rate = SYNC_RATE;

    /* Debug string size */
    char stream [MAX_BUFFER_SIZE];

  public:
    ros::NodeHandle nh; /* ROS Node Instantiation */
    String heroName;
    ROSHandle(unsigned long sync_rate, unsigned long debug_rate);
    void init(LEDStatus& ledStatus);
    void sync(void);
    void sync(unsigned long rate);
    bool connected(void);
    void debug(char const *format, ...);

    ros::NodeHandle& getNodeHandle(void);
    String getNamespace(void);
};

#endif
