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

#include "ROSHandle.h"

ROSHandle::ROSHandle(unsigned long sync_rate, unsigned long debug_rate) {
  this->sync_timer = millis();
  this->sync_rate = sync_rate;

  this->debug_timer = millis();
  this->debug_rate = debug_rate;
}

/* Setup ROS Communication */
void ROSHandle::init(LEDStatus& ledStatus) {
  this->ledStatus = &ledStatus;

  /* Read configuration from EEPROM */
  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.get(MEM_INIT_POS, configurationData);
  EEPROM.end();
  default_config = true;
  if (configurationData.robot_id != -1) {
    default_config = false;
  }

  /* Connect the ESP8266 the wifi AP */
  WiFi.mode(WIFI_STA);
  if (default_config) {
    WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  } else {
    WiFi.begin(configurationData.wifi_ssid, configurationData.wifi_pass);
  }

  bool led_toggle = true;
  while (WiFi.status() != WL_CONNECTED) {
    if (led_toggle == true) {
      ledStatus.setColors(*ledStatus.red, *ledStatus.black);
      led_toggle = false;
    } else {
      ledStatus.setColors(*ledStatus.black, *ledStatus.red);
      led_toggle = true;
    }
    delay(WIFI_CONNECT_LOOP);
  }
  ledStatus.reset();
  delay(WIFI_CONNECT_LOOP);


  /* Start ROS communication module */
  IPAddress ROS_MASTER_ADDRESS; /* Ros Master IP */
  if (default_config) {
    ROS_MASTER_ADDRESS.fromString(ROS_MASTER_IP);
  } else {
    ROS_MASTER_ADDRESS.fromString(configurationData.ros_master_address);
  }
  this->nh.getHardware()->setConnection(ROS_MASTER_ADDRESS, ROS_MASTER_PORT);

  /* Starting ros node */
  this->nh.initNode();

  /* Updating Robot name */
  if (default_config) {
    this->heroName = String(ROBOT_NAME) + String(ROBOT_ID);
  } else {
    this->heroName = String(ROBOT_NAME) + String(configurationData.robot_id);
  }

  sprintf(this->stream, "\33[94m[%s] Firmware: %s | Hardware: %s | Config: %s | IP: %s \33[0m", this->heroName.c_str(), FIRMWARE_VERSION, HARDWARE_VERSION, CONFIG_VERSION, this->nh.getHardware()->getLocalIP().toString().c_str());
  this->nh.loginfo(this->stream);
  this->nh.spinOnce();
}


ros::NodeHandle& ROSHandle::getNodeHandle(void) {
  return this->nh;
}

String ROSHandle::getNamespace(void) {
  return this->heroName;
}

void ROSHandle::sync() {
  this->sync(this->sync_rate);
}

bool ROSHandle::connected(void){
return this->nh.connected();
}

void ROSHandle::sync(unsigned long sync_rate) {
  if ((millis() - this->debug_timer) > (1000 / debug_rate)) {
    sprintf(this->stream, "\33[96m[%s] Conected at time %d\33[0m", this->heroName.c_str(), millis());
    this->nh.loginfo(this->stream);
    this->debug_timer = millis();
  }

  if ((millis() - this->sync_timer) > (1000 / sync_rate)) {
    this->nh.spinOnce();
    this->sync_timer = millis();
  }
}

void ROSHandle::debug(char const *format, ...) {
  va_list args;
  vsnprintf(this->stream, MAX_BUFFER_SIZE, format, args);
  this->nh.loginfo(this->stream);
}
