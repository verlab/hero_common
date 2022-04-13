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
 
#include "LEDStatus.h"

LEDStatus::LEDStatus(unsigned long rate) {
  this->timer = millis();
  this->setRate(rate);

  this->strip = new NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp8266Uart1800KbpsMethod>(this->PixelCount);

  this->red = new  RgbColor(COLOR_SATURATION, 0, 0);
  this->green = new  RgbColor(0, COLOR_SATURATION, 0);
  this->cyan = new  RgbColor(0, COLOR_SATURATION, COLOR_SATURATION);
  this->magenta = new  RgbColor(COLOR_SATURATION, 0, COLOR_SATURATION);
  this->black = new  RgbColor(0, 0, 0);
}

void LEDStatus::init(ros::NodeHandle &nh, String heroName) {
  this->nh_ = &nh;   /* ROS Node Handle */
  this->heroName = heroName;

  /* Address led subscriber */
  this->ledTopic = this->heroName + String("/led");                                                 /* Update topic name */
  this->ledSub = new ros::Subscriber<std_msgs::ColorRGBA, LEDStatus>(this->ledTopic.c_str(), &LEDStatus::ledCallback, this);    /* Instantiate subscriber */
  this->nh_->subscribe(*this->ledSub);
}

/* This resets all the neopixels to an off state */
void LEDStatus::reset(void) {
  this->reseted = true;
  this->strip->Begin();
  delayMicroseconds(500);
  for (int i = 0; i <= PixelCount; i++) {
    this->strip->SetPixelColor(i, *this->black);
  }
  this->strip->SetBrightness(0);
  this->strip->Show();
  delayMicroseconds(500);
}

void LEDStatus::setRate(unsigned long rate) {
  this->rate = rate;
}

void LEDStatus::update() {
  this->update(this->rate);
}

/* LED update */
void LEDStatus::update(unsigned long rate) {
  if (((millis() - this->timer) > (1000 / rate)) && ((millis() - this->watchdogTimer) > 15000) && !this->reseted) {
    this->reset();
    this->timer = millis();
  }
}

void LEDStatus::setColors(RgbColor color0, RgbColor color1) {
  this->reseted = false;
  this->strip->Begin();
  delayMicroseconds(500);
  this->strip->SetPixelColor(0, color0);
  this->strip->SetPixelColor(1, color1);
  this->strip->SetBrightness(COLOR_SATURATION);
  this->strip->Show();
  delayMicroseconds(500);
}

void LEDStatus::welcome(RgbColor color, unsigned long wait) {
  this->reseted = false;
  this->strip->Begin();
  delayMicroseconds(500);
  for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) {
      this->setColors(color, *this->black);
    } else {
      this->setColors(*this->black, color);
    }
    this->strip->SetBrightness(COLOR_SATURATION);
    this->strip->Show();
    delay(wait);
  }
  this->reset();
}

void LEDStatus::ledCallback(const std_msgs::ColorRGBA& msg) {
  this->reseted = false;
  this->strip->Begin();
  delayMicroseconds(500);
  RgbColor color(msg.r * 255, msg.g * 255, msg.b * 255);
  for (int i = 0; i <= PixelCount; i++) {
    this->strip->SetPixelColor(i, color);
  }
  this->strip->SetBrightness(msg.a * 255);
  this->strip->Show();
  delayMicroseconds(500);
  this->watchdogTimer = millis();
}
