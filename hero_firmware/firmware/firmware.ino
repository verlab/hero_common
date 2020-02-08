/*
 ************************************************************************
    H E R O   F I R M W A R E
 ************************************************************************

   Paulo Rezeck <rezeck@dcc.ufmg.br>
   Mauricio Ferrari <mauferrari@dcc.ufmg.br>
   Hector Azpurua <hectorxxx@gmail.com>

   HeRo Project
   Computer Vision and Robotics Lab - VeRLab/DCC
   University Federal de Minas Gerais - UFMG/Brazil
 ************************************************************************/

/* ESP Library */
#include <ESP8266WiFi.h>

/* ROS Library */
#include <ros.h>

/* Libraries */
#include "config.h"
#include "config_via_wifi.h"
#include "firmware.h"
#include "rosnode.h"


/* Main Setup */
void setup() {
  /* Read configuration from EEPROM */
  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.get(MEM_INIT_POS, configurationData);
  EEPROM.end();
  default_config = true;
  if (configurationData.robot_id != -1) {
    default_config = false;
  }
  /* Setup laser Readings */
  setup_laser();

  /* This resets all the neopixels to an off state */
  setup_led();
  config_mode = is_config_mode();
  //config_mode = true;
  default_config = true;
  if (config_mode) {
    setupWiFi();
    server.on("/", handleRoot);
    server.on("/resetEEPROM", handleResetEEPROM);
    server.on("/saveParams", handleSaveParams);
    server.on("/css", handleCSS);
    server.onNotFound(handleNotFound);
    server.begin();
    hello(magenta, 100);
    strip.Begin();
  }
  else {
    /* Connect the ESP8266 the the wifi AP */
    bool led_toggle = true;
    strip.Begin();
    strip.Show();
    if (default_config) {
      WiFi.begin(WIFI_SSID, WIFI_PASSWD);
    } else {
      WiFi.begin(configurationData.wifi_ssid, configurationData.wifi_pass);
    }
    while (WiFi.status() != WL_CONNECTED) {
      if (led_toggle == true) {
        strip.SetPixelColor(0, red);
        strip.SetPixelColor(1, black);
        led_toggle = false;
      } else {
        strip.SetPixelColor(0, black);
        strip.SetPixelColor(1, red);
        led_toggle = true;
      }
      strip.SetBrightness(COLOR_SATURATION);
      strip.Show();
      delay(WIFI_CONNECT_LOOP);
    }
    strip.SetPixelColor(0, black);
    strip.SetPixelColor(1, black);
    strip.SetBrightness(COLOR_SATURATION);
    strip.Show();
    delay(WIFI_CONNECT_LOOP);

    /* Setup PID Controller and Autotuner */
    setup_pid();

    /* Setup ROS Communication */
    setup_ros();

    /* Setup IMU I2C communication */
#if IMU_ENABLE == true
    setup_imu();
#endif

    /* Initiate motors and encoders */
    setup_motors();

    /* ROS LOG */
    sprintf(buf, "\33[96m Founded %s! \33[0m", hero_name.c_str());
    nh.loginfo(buf);
    hello(cyan, 100);
  }
}


/* Main loop */
void loop() {
  if (config_mode) { // Web Configuration Mode
    static int config_status_led_count = 0;
    server.handleClient();
    delay(1);
    if ((millis() - led_blinky) > 300) {
      led_blinky = millis();

      switch (config_status_led) {
        case 0: // Default state Web Configuration Mode
          if (blinky) {
            strip.SetPixelColor(0, magenta);
            strip.SetPixelColor(1, black);
          } else {
            strip.SetPixelColor(0, black);
            strip.SetPixelColor(1, magenta);
          }
          break;
        case 1: // Case web save buttom is pressed
          if (blinky) {
            strip.SetPixelColor(0, green);
            strip.SetPixelColor(1, black);
          } else {
            strip.SetPixelColor(0, black);
            strip.SetPixelColor(1, green);
          }
          config_status_led_count++;
          break;
        case 2: // Case web reset buttom is pressed
          if (blinky) {
            strip.SetPixelColor(0, red);
            strip.SetPixelColor(1, black);
          } else {
            strip.SetPixelColor(0, black);
            strip.SetPixelColor(1, red);
          }
          config_status_led_count++;
          break;
      }

      if (config_status_led_count >= config_status_led_times) {
        config_status_led = 0;
        config_status_led_count = 0;
      }
      blinky = !blinky;

      strip.SetBrightness(COLOR_SATURATION);
      strip.Show();
    }

  }
  else { // ROS Mode

    if (tuning) { /* Autotuner; this process disable PID controller for while */
      tune_motors();
    }
    else { /* PID control loop */
      if (r_motor.attached() && l_motor.attached() && !pwm_only) control();
    }

    /* ROS Debugs */
#if DEBUG == true
    if ((millis() - ros_debug_timer) > 1000 / debug_rate) {
      ros_debug_timer = millis();
      if (tuning) {
        sprintf(buf, "\33[96m[%s] Tuning PID! Please wait (200 seconds)... %d ms\33[0m", hero_name.c_str(), (millis() - tunning_steady_state) / 1000);
        nh.loginfo(buf);
      }
      else {
        sprintf(buf, "\33[96m[%s] Conected at time %d\33[0m", hero_name.c_str(), millis());
        nh.loginfo(buf);
      }

    }
#endif

    /* Sensors update loop */
    if ((millis() - loop_timer) > 1000 / loop_rate) {
      loop_timer = millis();
      update_laser();
      update_encoder();
      update_odom();
#if IMU_ENABLE == true
      readIMU();
#endif
      nh.spinOnce();
    }
  }
}
