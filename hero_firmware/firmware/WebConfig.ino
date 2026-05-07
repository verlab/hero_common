/*
  ******************************************************************************
                      H E R O   F I R M W A R E  —  Web configuration
  ******************************************************************************
*/

#include "WebConfig.h"
#include "web_config_embed.h"
#include "config.h"
#include "WheelEncoder.h"
#include "MotorDriver.h"
#include "RangeSensor.h"
#include "IMUSensor.h"
#include <sensor_msgs/LaserScan.h>
#include <string.h>
#include <math.h>

WebConfig::WebConfig(unsigned long rate) {
  this->rate = rate;
  this->timer = millis();
  this->wheelEncoder = nullptr;
  this->motorDriver = nullptr;
  this->rangeSensor = nullptr;
  this->imuSensor = nullptr;
}

void WebConfig::init(LEDStatus& ledStatus, WheelEncoder& enc, MotorDriver& mot, RangeSensor& range, IMUSensor* imu) {
  this->ledStatus = &ledStatus;
  this->wheelEncoder = &enc;
  this->motorDriver = &mot;
  this->rangeSensor = &range;
  this->imuSensor = imu;
  this->server = new ESP8266WebServer(80);

  WiFi.mode(WIFI_AP);

  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) + String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = "HERO_ROBOT_" + macID;

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);
  for (unsigned i = 0; i < AP_NameString.length(); i++) AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSK, 8);

  this->server->on("/", std::bind(&WebConfig::handleRoot, this));
  this->server->on("/api/telemetry", HTTP_GET, std::bind(&WebConfig::handleApiTelemetry, this));
  this->server->on("/api/constants", HTTP_GET, std::bind(&WebConfig::handleApiConstants, this));
  this->server->on("/api/motor", HTTP_POST, std::bind(&WebConfig::handleMotorCmd, this));
  this->server->on("/saveParams", HTTP_POST, std::bind(&WebConfig::handleSaveParams, this));
  this->server->on("/saveHardware", HTTP_POST, std::bind(&WebConfig::handleSaveHardware, this));
  this->server->on("/resetEEPROM", HTTP_POST, std::bind(&WebConfig::handleResetEEPROM, this));
  this->server->on("/api/ir_autocalib", HTTP_GET, std::bind(&WebConfig::handleIrAutocalibGet, this));
  this->server->on("/api/ir_autocalib", HTTP_POST, std::bind(&WebConfig::handleIrAutocalibPost, this));
  this->server->on("/api/led", HTTP_POST, std::bind(&WebConfig::handleLedPost, this));
  this->server->onNotFound(std::bind(&WebConfig::handleNotFound, this));
  this->server->begin();

  this->motorDriver->setAutoHaltEnabled(false);
  this->ledSlowLastMs = millis();

  ledStatus.welcome(*ledStatus.magenta, 100);
}

void WebConfig::update() {
  this->update(this->rate);
}

void WebConfig::update(unsigned long rate) {
  this->server->handleClient();
  this->tickIrAutocalib();

  if (this->wheelEncoder) this->wheelEncoder->update(40);
  if (this->rangeSensor) this->rangeSensor->update(8);
#if IMU_ENABLE
  if (this->imuSensor) this->imuSensor->update(25);
#endif
  if (this->motorDriver) this->motorDriver->update(10);

  if ((millis() - this->timer) > (1000 / rate)) {
    this->timer = millis();

    if (config_status_led == 0) {
      /* ~3 s full blink cycle (1.5 s per half) for idle magenta */
      if ((millis() - this->ledSlowLastMs) >= 1500) {
        this->ledSlowLastMs = millis();
        blinky = !blinky;
        if (blinky) {
          this->ledStatus->setColors(*ledStatus->magenta, *ledStatus->black);
        } else {
          this->ledStatus->setColors(*ledStatus->black, *ledStatus->magenta);
        }
      }
    } else {
      switch (config_status_led) {
        case 1:
          if (blinky) {
            this->ledStatus->setColors(*ledStatus->green, *ledStatus->black);
          } else {
            this->ledStatus->setColors(*ledStatus->black, *ledStatus->green);
          }
          config_status_led_count++;
          break;
        case 2:
          if (blinky) {
            this->ledStatus->setColors(*ledStatus->red, *ledStatus->black);
          } else {
            this->ledStatus->setColors(*ledStatus->black, *ledStatus->red);
          }
          config_status_led_count++;
          break;
        default:
          break;
      }

      if (config_status_led_count >= config_status_led_times) {
        config_status_led = 0;
        config_status_led_count = 0;
        this->ledSlowLastMs = millis();
      }
      blinky = !blinky;
    }
  }
}

void WebConfig::handleRoot(void) {
  heroWebSendRootPage(this->server);
  delay(10);
}

static void jsonAppendFloat(String& s, const char* key, float v, bool comma) {
  char b[32];
  dtostrf(v, 1, 5, b);
  s += '"';
  s += key;
  s += "\":";
  s += b;
  if (comma) s += ',';
}

static void jsonAppendInt(String& s, const char* key, long v, bool comma) {
  s += '"';
  s += key;
  s += "\":";
  s += String(v);
  if (comma) s += ',';
}

void WebConfig::handleApiTelemetry(void) {
  struct PID_CONFIG pv, pp;
  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.get(MEM_INIT_POS, configurationData);
  EEPROM.get(MEM_INIT_POS_PID_VELOCITY, pv);
  EEPROM.get(MEM_INIT_POS_PID_POSITION, pp);
  EEPROM.get(MEM_INIT_POS_MOTOR_POSITION, motorData);
  EEPROM.get(MEM_INIT_POS_IR_CALIB, irCalib);
  EEPROM.end();

  if (this->rangeSensor) this->rangeSensor->readSensor();
  if (this->wheelEncoder) this->wheelEncoder->readSensor();

  hero_common::Encoder em{};
  if (this->wheelEncoder) em = this->wheelEncoder->getMessage();
  sensor_msgs::LaserScan ls;
  if (this->rangeSensor) ls = this->rangeSensor->getMessage();

  String j = "{";
  j += "\"versions\":{\"firmware\":\"" FIRMWARE_VERSION "\",\"hardware\":\"" HARDWARE_VERSION "\",\"config\":\"" CONFIG_VERSION "\"},";

  j += "\"conn\":{";
  j += "\"robot_id\":" + String((int)configurationData.robot_id) + ",";
  j += "\"robot_desc\":\"";
  j += configurationData.robot_desc;
  j += "\",\"wifi_ssid\":\"";
  j += configurationData.wifi_ssid;
  j += "\",\"wifi_pass\":\"";
  j += configurationData.wifi_pass;
  j += "\",\"ros_master\":\"";
  j += configurationData.ros_master_address;
  j += "\"},";

  j += "\"pidVel\":{";
  jsonAppendFloat(j, "lkp", pv.lkp, true);
  jsonAppendFloat(j, "lki", pv.lki, true);
  jsonAppendFloat(j, "lkd", pv.lkd, true);
  jsonAppendFloat(j, "rkp", pv.rkp, true);
  jsonAppendFloat(j, "rki", pv.rki, true);
  jsonAppendFloat(j, "rkd", pv.rkd, false);
  j += "},";

  j += "\"pidPos\":{";
  jsonAppendFloat(j, "lkp", pp.lkp, true);
  jsonAppendFloat(j, "lki", pp.lki, true);
  jsonAppendFloat(j, "lkd", pp.lkd, true);
  jsonAppendFloat(j, "rkp", pp.rkp, true);
  jsonAppendFloat(j, "rki", pp.rki, true);
  jsonAppendFloat(j, "rkd", pp.rkd, false);
  j += "},";

  j += "\"motor\":{\"left\":";
  j += String(motorData.leftMotorDeadzone);
  j += ",\"right\":";
  j += String(motorData.rightMotorDeadzone);
  j += ",\"ramp_us_per_s\":";
  j += String((int)motorData.pwm_ramp_us_per_s);
  j += "},";

  j += "\"irAlpha\":[";
  for (int i = 0; i < 8; i++) {
    if (i) j += ',';
    j += String(irCalib.alpha[i], 4);
  }
  j += "],";

  j += "\"enc\":{";
  jsonAppendInt(j, "l", (long)em.left_ticks, true);
  jsonAppendInt(j, "r", (long)em.right_ticks, true);
  jsonAppendFloat(j, "vLf", (float)em.left_speed_filtered, true);
  jsonAppendFloat(j, "vRf", (float)em.right_speed_filtered, false);
  j += "},";

  j += "\"ir\":{\"i\":[";
  for (int k = 0; k < 8; k++) {
    if (k) j += ',';
    int idx = laser_scan_slot_angle_order[k];
    float v = 0;
    if (ls.intensities && ls.intensities_length > (unsigned)idx) v = ls.intensities[idx];
    j += String(v, 2);
  }
  j += "]},";

  j += "\"irMm\":{\"capMm\":";
  j += String(ls.range_max * 1000.0f, 1);
  j += ",\"slot\":[";
  for (int k = 0; k < 8; k++) {
    if (k) j += ',';
    j += String(laser_scan_slot_angle_order[k]);
  }
  j += "],\"mm\":[";
  for (int k = 0; k < 8; k++) {
    if (k) j += ',';
    int idx = laser_scan_slot_angle_order[k];
    float mm = 0;
    if (ls.ranges && ls.ranges_length > (unsigned)idx) mm = ls.ranges[idx] * 1000.0f;
    j += String(mm, 1);
  }
  j += "]},";

  j += "\"imu\":{";
#if IMU_ENABLE
  if (this->imuSensor && this->imuSensor->isEnable()) {
    j += "\"enabled\":true,\"yaw\":";
    j += String(this->imuSensor->get(), 4);
    j += "}";
  } else {
    j += "\"enabled\":false,\"note\":\"IMU disabled\"}";
  }
#else
  j += "\"enabled\":false,\"note\":\"IMU_ENABLE false in build\"}";
#endif
  j += "}";

  this->server->send(200, "application/json", j);
}

void WebConfig::handleApiConstants(void) {
  String j = "{";
  j += "\"CONFIG_VERSION\":\"" CONFIG_VERSION "\",";
  j += "\"HARDWARE_VERSION\":\"" HARDWARE_VERSION "\",";
  j += "\"FIRMWARE_VERSION\":\"" FIRMWARE_VERSION "\",";
  j += "\"ROBOT_NAME\":\"" ROBOT_NAME "\",";
  j += "\"ROBOT_ID_COMPILE\":\"" ROBOT_ID "\",";
  j += "\"ROS_MASTER_IP\":\"" ROS_MASTER_IP "\",";
  j += "\"ROS_MASTER_PORT\":" + String(ROS_MASTER_PORT) + ",";
  j += "\"WIFI_SSID_DEFAULT\":\"" WIFI_SSID "\",";
  j += "\"DEBUG\":" + String(DEBUG ? "true" : "false") + ",";
  j += "\"DEBUG_RATE\":" + String(DEBUG_RATE) + ",";
  j += "\"SYNC_RATE\":" + String(SYNC_RATE) + ",";
  j += "\"MAX_BUFFER_SIZE\":" + String(MAX_BUFFER_SIZE) + ",";
  j += "\"WIFI_CONNECT_LOOP\":" + String(WIFI_CONNECT_LOOP) + ",";
  jsonAppendFloat(j, "ROBOT_DIAMETER", ROBOT_DIAMETER, true);
  jsonAppendFloat(j, "WHEEL_DIAMETER", WHEEL_DIAMETER, true);
  jsonAppendFloat(j, "WHEEL_SEPARATION", WHEEL_SEPARATION, true);
  jsonAppendFloat(j, "MOT_STEP_DIST", MOT_STEP_DIST, true);
  jsonAppendFloat(j, "MAX_LINEAR_VEL", MAX_LINEAR_VEL, true);
  jsonAppendFloat(j, "MAX_ANGULAR_VEL", MAX_ANGULAR_VEL, true);
  j += "\"ENC_A_LEFT\":" + String(ENC_A_LEFT) + ",";
  j += "\"ENC_B_LEFT\":" + String(ENC_B_LEFT) + ",";
  j += "\"ENC_A_RIGHT\":" + String(ENC_A_RIGHT) + ",";
  j += "\"ENC_B_RIGHT\":" + String(ENC_B_RIGHT) + ",";
  jsonAppendFloat(j, "ENCODER_SPEED_GAIN", ENCODER_SPEED_GAIN, true);
  jsonAppendFloat(j, "ENCODER_SPEED_GAIN_AGGRESSIVE", ENCODER_SPEED_GAIN_AGGRESSIVE, true);
  j += "\"MOTOR_RIGHT\":" + String(MOTOR_RIGHT) + ",";
  j += "\"MOTOR_LEFT\":" + String(MOTOR_LEFT) + ",";
  j += "\"MOTOR_RIGHT_HALT_PWM\":" + String(MOTOR_RIGHT_HALT_PWM) + ",";
  j += "\"MOTOR_LEFT_HALT_PWM\":" + String(MOTOR_LEFT_HALT_PWM) + ",";
  j += "\"MOTOR_STIFFNESS\":" + String(MOTOR_STIFFNESS) + ",";
  j += "\"MOTOR_PWM_DEFAULT_RAMP_US_S\":" + String(MOTOR_PWM_DEFAULT_RAMP_US_S) + ",";
  j += "\"MOTOR_PWM_RAMP_MIN_US_S\":" + String(MOTOR_PWM_RAMP_MIN_US_S) + ",";
  j += "\"MOTOR_PWM_RAMP_MAX_US_S\":" + String(MOTOR_PWM_RAMP_MAX_US_S) + ",";
  j += "\"MUX_A\":" + String(MUX_A) + ",";
  j += "\"MUX_B\":" + String(MUX_B) + ",";
  j += "\"MUX_C\":" + String(MUX_C) + ",";
  j += "\"MUX_EN\":" + String(MUX_EN) + ",";
  j += "\"TOUCH_THRESHOLD\":" + String(TOUCH_THRESHOLD) + ",";
  j += "\"I2C_SDA\":" + String(I2C_SDA) + ",";
  j += "\"I2C_SCL\":" + String(I2C_SCL) + ",";
  j += "\"IMU_ENABLE\":" + String(IMU_ENABLE ? "true" : "false") + ",";
  j += "\"XGYRO_OFFSET\":" + String(XGYRO_OFFSET) + ",";
  j += "\"YGYRO_OFFSET\":" + String(YGYRO_OFFSET) + ",";
  j += "\"ZGYRO_OFFSET\":" + String(ZGYRO_OFFSET) + ",";
  j += "\"ZACC_OFFSET\":" + String(ZACC_OFFSET) + ",";
  j += "\"PIXEL_COUNT\":" + String(PIXEL_COUNT) + ",";
  j += "\"COLOR_SATURATION\":" + String(COLOR_SATURATION) + ",";
  jsonAppendFloat(j, "DEFAULT_KP", DEFAULT_KP, true);
  jsonAppendFloat(j, "DEFAULT_KI", DEFAULT_KI, true);
  jsonAppendFloat(j, "DEFAULT_KD", DEFAULT_KD, true);
  j += "\"OUTPUT_LIMIT\":" + String(OUTPUT_LIMIT) + ",";
  j += "\"SAMPLE_TIME\":" + String(SAMPLE_TIME) + ",";
  jsonAppendFloat(j, "SOME_OVERSHOOT_RULE_P", SOME_OVERSHOOT_RULE_P, true);
  jsonAppendFloat(j, "SOME_OVERSHOOT_RULE_I", SOME_OVERSHOOT_RULE_I, true);
  jsonAppendFloat(j, "SOME_OVERSHOOT_RULE_D", SOME_OVERSHOOT_RULE_D, true);
  j += "\"TUNING_SUCCESSED_THRESHOLD_MIN\":" + String(TUNING_SUCCESSED_THRESHOLD_MIN) + ",";
  j += "\"TUNING_SUCCESSED_THRESHOLD_MAX\":" + String(TUNING_SUCCESSED_THRESHOLD_MAX) + ",";
  jsonAppendFloat(j, "TUNE_STEP", (float)TUNE_STEP, true);
  jsonAppendFloat(j, "TUNE_NOISE", TUNE_NOISE, true);
  j += "\"TUNE_LOOK_BACK\":" + String(TUNE_LOOK_BACK) + ",";
  j += "\"TUNE_STEADY_STATE_TIME\":" + String(TUNE_STEADY_STATE_TIME) + ",";
  j += "\"TUNE_STEADY_STATE\":" + String(TUNE_STEADY_STATE);
  j += "}";
  this->server->send(200, "application/json", j);
}

void WebConfig::handleMotorCmd(void) {
  if (!this->motorDriver) {
    this->server->send(500, "application/json", "{\"ok\":false}");
    return;
  }
  if (this->server->hasArg("stop")) {
    this->motorDriver->halt();
  } else {
    int l = this->server->arg("l").toInt();
    int r = this->server->arg("r").toInt();
    l = constrain(l, 1000, 2000);
    r = constrain(r, 1000, 2000);
    this->motorDriver->command(l, r);
  }
  this->server->send(200, "application/json", "{\"ok\":true}");
}

void WebConfig::handleSaveHardware(void) {
  struct PID_CONFIG pv, pp;
  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.get(MEM_INIT_POS_PID_VELOCITY, pv);
  EEPROM.get(MEM_INIT_POS_PID_POSITION, pp);
  EEPROM.get(MEM_INIT_POS_MOTOR_POSITION, motorData);
  EEPROM.get(MEM_INIT_POS_IR_CALIB, irCalib);

#define PF(name, field) if (this->server->hasArg(name)) { field = this->server->arg(name).toFloat(); }

  PF("v_lkp", pv.lkp);
  PF("v_lki", pv.lki);
  PF("v_lkd", pv.lkd);
  PF("v_rkp", pv.rkp);
  PF("v_rki", pv.rki);
  PF("v_rkd", pv.rkd);
  PF("p_lkp", pp.lkp);
  PF("p_lki", pp.lki);
  PF("p_lkd", pp.lkd);
  PF("p_rkp", pp.rkp);
  PF("p_rki", pp.rki);
  PF("p_rkd", pp.rkd);
#undef PF

  if (this->server->hasArg("m_l")) {
    int v = this->server->arg("m_l").toInt();
    if (v >= 1000 && v <= 2000) motorData.leftMotorDeadzone = v;
  }
  if (this->server->hasArg("m_r")) {
    int v = this->server->arg("m_r").toInt();
    if (v >= 1000 && v <= 2000) motorData.rightMotorDeadzone = v;
  }
  if (this->server->hasArg("m_ramp")) {
    int v = this->server->arg("m_ramp").toInt();
    v = constrain(v, MOTOR_PWM_RAMP_MIN_US_S, MOTOR_PWM_RAMP_MAX_US_S);
    motorData.pwm_ramp_us_per_s = (uint16_t)v;
  }
  /* Backward compatibility: old web sent 0–1 as m_stiff */
  if (this->server->hasArg("m_stiff") && !this->server->hasArg("m_ramp")) {
    float f = this->server->arg("m_stiff").toFloat();
    if (f < 0.0f) f = 0.0f;
    if (f > 1.0f) f = 1.0f;
    int v = (int)lround((double)f * (double)MOTOR_PWM_RAMP_MAX_US_S);
    v = constrain(v, MOTOR_PWM_RAMP_MIN_US_S, MOTOR_PWM_RAMP_MAX_US_S);
    motorData.pwm_ramp_us_per_s = (uint16_t)v;
  }

  for (int i = 0; i < 8; i++) {
    String k = "ir" + String(i);
    if (this->server->hasArg(k)) {
      float a = this->server->arg(k).toFloat();
      if (a > 0.01f && a < 10.0f) irCalib.alpha[i] = a;
    }
  }

  EEPROM.put(MEM_INIT_POS_PID_VELOCITY, pv);
  EEPROM.put(MEM_INIT_POS_PID_POSITION, pp);
  EEPROM.put(MEM_INIT_POS_MOTOR_POSITION, motorData);
  EEPROM.put(MEM_INIT_POS_IR_CALIB, irCalib);
  EEPROM.end();

  if (this->motorDriver) {
    this->motorDriver->applyMotorDataFromGlobals();
  }

  this->server->send(200, "application/json", "{\"status\":\"success\"}");
  config_status_led = 1;
}

void WebConfig::tickIrAutocalib(void) {
  if (this->irCalibPhase != 1 || !this->rangeSensor) return;
  if (this->irCalibN >= 100) return;

  this->rangeSensor->readSensor();
  sensor_msgs::LaserScan ls = this->rangeSensor->getMessage();
  for (int i = 0; i < 8; i++) {
    if (ls.intensities && ls.intensities_length > (unsigned)real_pos_inter[i])
      this->irCalibSum[i] += ls.intensities[real_pos_inter[i]];
  }
  this->irCalibN++;
  if (this->irCalibN < 100) return;

  float d2 = this->irCalibDistanceM * this->irCalibDistanceM;
  for (int i = 0; i < 8; i++) {
    float mean = this->irCalibSum[i] / 100.0f;
    irCalib.alpha[i] = mean * d2;
    if (irCalib.alpha[i] < 0.01f) irCalib.alpha[i] = 0.01f;
    if (irCalib.alpha[i] > 50.0f) irCalib.alpha[i] = 50.0f;
  }
  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.put(MEM_INIT_POS_IR_CALIB, irCalib);
  EEPROM.end();
  this->irCalibPhase = 2;
}

void WebConfig::handleIrAutocalibPost(void) {
  if (this->server->hasArg("cancel")) {
    this->irCalibPhase = 0;
    this->irCalibN = 0;
    this->server->send(200, "application/json", "{\"ok\":true,\"phase\":0}");
    return;
  }
  if (!this->server->hasArg("start")) {
    this->server->send(400, "application/json", "{\"ok\":false,\"err\":\"missing start\"}");
    return;
  }
  if (!this->rangeSensor) {
    this->server->send(500, "application/json", "{\"ok\":false}");
    return;
  }
  float d_m = 0.10f;
  if (this->server->hasArg("d_mm")) {
    int dmm = this->server->arg("d_mm").toInt();
    if (dmm >= 20 && dmm <= 500) d_m = dmm / 1000.0f;
  } else if (this->server->hasArg("d_m")) {
    d_m = this->server->arg("d_m").toFloat();
    if (d_m < 0.02f || d_m > 0.5f) d_m = 0.10f;
  }
  memset(this->irCalibSum, 0, sizeof(this->irCalibSum));
  this->irCalibN = 0;
  this->irCalibDistanceM = d_m;
  this->irCalibPhase = 1;
  this->server->send(200, "application/json", "{\"ok\":true,\"phase\":1}");
}

void WebConfig::handleIrAutocalibGet(void) {
  String j = "{\"phase\":";
  j += String((int)this->irCalibPhase);
  j += ",\"n\":";
  j += String((int)this->irCalibN);
  j += ",\"distance_m\":";
  j += String(this->irCalibDistanceM, 4);
  if (this->irCalibPhase == 2) {
    j += ",\"alpha\":[";
    for (int i = 0; i < 8; i++) {
      if (i) j += ',';
      j += String(irCalib.alpha[i], 4);
    }
    j += "]";
  }
  j += "}";
  this->server->send(200, "application/json", j);
}

void WebConfig::handleLedPost(void) {
  if (!this->ledStatus) {
    this->server->send(500, "application/json", "{\"ok\":false}");
    return;
  }
  int r = constrain(this->server->arg("r").toInt(), 0, 255);
  int g = constrain(this->server->arg("g").toInt(), 0, 255);
  int b = constrain(this->server->arg("b").toInt(), 0, 255);
  int a = this->server->hasArg("a") ? constrain(this->server->arg("a").toInt(), 0, 255) : COLOR_SATURATION;
  this->ledStatus->showWebColor((uint8_t)r, (uint8_t)g, (uint8_t)b, (uint8_t)a);
  this->server->send(200, "application/json", "{\"ok\":true}");
}

void WebConfig::handleSaveParams(void) {
  String robot_id = this->server->arg("robotId");
  String robot_desc = this->server->arg("robotDescription");
  String wific_ssid = this->server->arg("wificSSID");
  String wific_pass = this->server->arg("wificPassword");
  String ros_master = this->server->arg("rosMasterAddress");

  configurationData.robot_id = (uint)robot_id.toInt();
  strncpy(configurationData.robot_desc, robot_desc.c_str(), sizeof(configurationData.robot_desc) - 1);
  configurationData.robot_desc[sizeof(configurationData.robot_desc) - 1] = 0;
  strncpy(configurationData.wifi_ssid, wific_ssid.c_str(), sizeof(configurationData.wifi_ssid) - 1);
  configurationData.wifi_ssid[sizeof(configurationData.wifi_ssid) - 1] = 0;
  strncpy(configurationData.wifi_pass, wific_pass.c_str(), sizeof(configurationData.wifi_pass) - 1);
  configurationData.wifi_pass[sizeof(configurationData.wifi_pass) - 1] = 0;
  strncpy(configurationData.ros_master_address, ros_master.c_str(), sizeof(configurationData.ros_master_address) - 1);
  configurationData.ros_master_address[sizeof(configurationData.ros_master_address) - 1] = 0;

  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.put(MEM_INIT_POS, configurationData);
  EEPROM.end();

  this->server->send(200, "application/json", "{\"status\":\"success\"}");
  config_status_led = 1;
}

void WebConfig::handleResetEEPROM(void) {
  char tmp_str[20] = "";
  memset(tmp_str, 0, sizeof(tmp_str));

  configurationData.robot_id = (uint)-1;
  strcpy(configurationData.robot_desc, tmp_str);
  strcpy(configurationData.ros_master_address, tmp_str);
  strcpy(configurationData.wifi_ssid, tmp_str);
  strcpy(configurationData.wifi_pass, tmp_str);

  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.put(MEM_INIT_POS, configurationData);
  EEPROM.end();

  this->server->send(200, "application/json", "{\"status\":\"success\"}");
  config_status_led = 2;
}

void WebConfig::handleNotFound(void) {
  String message = "404\nURI: ";
  message += this->server->uri();
  this->server->send(404, "text/plain", message);
  config_status_led = 0;
}
