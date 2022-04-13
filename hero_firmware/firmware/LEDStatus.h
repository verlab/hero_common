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

#ifndef __LED_STATUS_H__
#define __LED_STATUS_H__

/* ROS Library */
#define ROSSERIAL_ARDUINO_TCP
#include <ros.h>

#include <NeoPixelBus.h>                /* https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use */
#include <NeoPixelBrightnessBus.h>

/* Message types */
#include <std_msgs/ColorRGBA.h>

///* Addressable LED WS2812b */

//#define PIXEL_COUNT 7         /* NUMBER OF LED */
//#define COLOR_SATURATION 255  /* MAX SATURATION COLOR */

class LEDStatus {
  private:
    ros::NodeHandle *nh_;
    String heroName;

    /* LED callback */
    String ledTopic;                                     /* Topic name */
    ros::Subscriber<std_msgs::ColorRGBA, LEDStatus> *ledSub;        /* Message type */


    /* Addressable LEDs WS2812 Configuration */
    const uint16_t PixelCount = PIXEL_COUNT;
    NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp8266Uart1800KbpsMethod> *strip;

    bool reseted = false;
    unsigned long watchdogTimer = 0;
    unsigned long rate = 20, timer;

  public:
    LEDStatus(unsigned long rate);
    void init(ros::NodeHandle &nh, String heroName);

    void update();
    void update(unsigned long rate);
    void reset(void);

    void setRate(unsigned long rate);
    void welcome(RgbColor color, unsigned long timer);
    void setColors(RgbColor color0, RgbColor color1);

    /* Callback function */
    void ledCallback(const std_msgs::ColorRGBA& msg);

    RgbColor *red;
    RgbColor *green;
    RgbColor *cyan;
    RgbColor *magenta;
    RgbColor *black;
};


#endif
