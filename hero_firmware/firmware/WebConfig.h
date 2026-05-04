/*
  ******************************************************************************
                      H E R O   F I R M W A R E  —  Web configuration (AP mode)
  ******************************************************************************
*/

#ifndef __WEB_CONFIG_H__
#define __WEB_CONFIG_H__

#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "LEDStatus.h"

class WheelEncoder;
class MotorDriver;
class RangeSensor;
class IMUSensor;

#define MEM_ALOC_SIZE 512
#define MEM_INIT_POS 0
/* Keep in sync with VelocityControl.h / PositionControl.h / MotorDriver.h / RangeSensor.h */
#define MEM_INIT_POS_MOTOR_POSITION 100
#define MEM_INIT_POS_PID_VELOCITY 110
#define MEM_INIT_POS_PID_POSITION 150
#define MEM_INIT_POS_IR_CALIB 220

const char WiFiAPPSK[] = "s3cr3tp4ss";

class WebConfig {
  private:
    LEDStatus *ledStatus;
    WheelEncoder *wheelEncoder;
    MotorDriver *motorDriver;
    RangeSensor *rangeSensor;
    IMUSensor *imuSensor;

    ESP8266WebServer *server;
    unsigned long timer = 0;
    unsigned long rate = 1;

    int config_status_led = 0;
    int config_status_led_times = 12;
    bool blinky = true;
    int config_status_led_count = 0;

    void handleApiTelemetry(void);
    void handleApiConstants(void);
    void handleMotorCmd(void);
    void handleSaveHardware(void);
    void handleIrAutocalibGet(void);
    void handleIrAutocalibPost(void);
    void handleLedPost(void);
    void tickIrAutocalib(void);

    uint8_t irCalibPhase = 0;
    uint16_t irCalibN = 0;
    float irCalibSum[8];
    float irCalibDistanceM = 0.10f;

    unsigned long ledSlowLastMs = 0;

  public:
    WebConfig(unsigned long rate);
    void init(LEDStatus& ledStatus, WheelEncoder& enc, MotorDriver& mot, RangeSensor& range, IMUSensor* imu);
    void update();
    void update(unsigned long rate);

    void handleRoot(void);
    void handleSaveParams(void);
    void handleResetEEPROM(void);
    void handleNotFound(void);
};

#endif
