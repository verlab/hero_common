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

#include "WebConfig.h"

WebConfig::WebConfig(unsigned long rate) {
  this->rate = rate;
  this->timer = millis();
}

void WebConfig::init(LEDStatus& ledStatus) {
  this->ledStatus = &ledStatus;
    this->server = new ESP8266WebServer(80);

  // Do a little work to get a unique-ish name.
  // Append the last two bytes of the MAC (HEX'd)
  WiFi.mode(WIFI_AP);

  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = "HERO_ROBOT_" + macID;

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i = 0; i < AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSK, 8);
  
  this->server->on("/", std::bind(&WebConfig::handleRoot, this));
  this->server->on("/icon.png", std::bind(&WebConfig::handleIcon, this));
  this->server->on("/style.css", std::bind(&WebConfig::handleCSS, this));
  this->server->on("/resetEEPROM", std::bind(&WebConfig::handleResetEEPROM, this));
  this->server->on("/saveParams", std::bind(&WebConfig::handleSaveParams, this));
  this->server->onNotFound(std::bind(&WebConfig::handleNotFound, this));
  this->server->begin();
  
  ledStatus.welcome(*ledStatus.magenta, 100);
}

void WebConfig::update() {
  this->update(this->rate);
}

void WebConfig::update(unsigned long rate) {
  this->server->handleClient();
  //  delay(1);
  if ((millis() - this->timer) > (1000 / rate)) {
    this->timer = millis();

    switch (config_status_led) {
      case 0: // Default state Web Configuration Mode
        if (blinky) {
          this->ledStatus->setColors(*ledStatus->magenta, *ledStatus->black);
        } else {
          this->ledStatus->setColors(*ledStatus->black, *ledStatus->magenta);
        }
        break;
      case 1: // Case web save buttom is pressed
        if (blinky) {
          this->ledStatus->setColors(*ledStatus->green, *ledStatus->black);
        } else {
          this->ledStatus->setColors(*ledStatus->black, *ledStatus->green);
        }
        config_status_led_count++;
        break;
      case 2: // Case web reset buttom is pressed
        if (blinky) {
          this->ledStatus->setColors(*ledStatus->red, *ledStatus->black);
        } else {
          this->ledStatus->setColors(*ledStatus->black, *ledStatus->red);
        }
        config_status_led_count++;
        break;
    }

    if (config_status_led_count >= config_status_led_times) {
      config_status_led = 0;
      config_status_led_count = 0;
    }
    blinky = !blinky;
  }
}


//root page can be accessed only if authentification is ok
void WebConfig::handleRoot(void) {

  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.get(MEM_INIT_POS, configurationData);
  EEPROM.end();

  String content = "<!doctype html><html><head> <meta charset=\"utf-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\"> <title>HeRo</title> <link href=\"/icon.png\" rel=\"icon\" type=\"image/x-icon\" /> <link rel=\"stylesheet\" href=\"/style.css\"> </head><body class=\"bg-light\"> <div class=\"container\"> <div class=\"py-5 text-center\"> <img class=\"d-block mx-auto mb-4\" alt=\"\" width=\"100\" height=\"93\" src=\"/icon.png\"/> <h2>HeRo Setup</h2> <p class=\"lead\">Edit basic robot configuration, Wifi credentials and robot identification.</p></div><div class=\"row\"> <div class=\"col-md-4 order-md-2 mb-4\"> <h4 class=\"d-flex justify-content-between align-items-center mb-3\"> <span class=\"text-muted\">Information</span> </h4> <ul class=\"list-group mb-3\"> <li class=\"list-group-item d-flex justify-content-between lh-condensed\"> <div> <h6 class=\"my-0\">Robot ID</h6> <small class=\"text-muted\"></small> </div><span class=\"text-muted\">$ROBOT_ID</span> </li><li class=\"list-group-item d-flex justify-content-between lh-condensed\"> <div> <h6 class=\"my-0\">Configuration Version</h6> <small class=\"text-muted\"></small> </div><span class=\"text-muted\">$CONFIG_VERSION</span> </li><li class=\"list-group-item d-flex justify-content-between lh-condensed\"> <div> <h6 class=\"my-0\">Firmware Version</h6> <small class=\"text-muted\"></small> </div><span class=\"text-muted\">$FIRMWARE_VERSION</span> </li><li class=\"list-group-item d-flex justify-content-between lh-condensed\"> <div> <h6 class=\"my-0\">Hardware Version</h6> <small class=\"text-muted\"></small> </div><span class=\"text-muted\">$HARDWARE_VERSION</span> </li></ul> <button class=\"btn btn-warning btn-lg btn-block\" type=\"submit\" id=\"btn-reset\">Reset memory</button> </div><div class=\"col-md-8 order-md-1\"> <h4 class=\"mb-3\">Configuration</h4> <form id=\"config-form\" class=\"needs-validation\" novalidate> <div class=\"mb-3\"> <label for=\"robotId\">Robot ID</label> <input type=\"number\" class=\"form-control\" name=\"robotId\" id=\"robotId\" placeholder=\"\" required value=\"$ROBOT_ID\" step=\"1\" max=\"999\"> <div class=\"invalid-feedback\"> Please a robot ID. </div></div><div class=\"mb-3\"> <label for=\"robotDescription\">Robot description (optional)</label> <input type=\"text\" class=\"form-control\" name=\"robotDescription\" id=\"robotDescription\" placeholder=\"Robot description...\" value=\"$ROBOT_DESC\" maxlength=\"19\"> </div><div class=\"row\"> <div class=\"col-md-6 mb-3\"> <label for=\"wificSSID\">Wifi client SSID</label> <input type=\"text\" class=\"form-control\" name=\"wificSSID\" id=\"wificSSID\" placeholder=\"Wifi SSID...\" required value=\"$WIFIC_SSID\" maxlength=\"19\"> <div class=\"invalid-feedback\"> Valid Wifi SSID is required. </div></div><div class=\"col-md-6 mb-3\"> <label for=\"wificPassword\">Wifi client password</label> <input type=\"text\" class=\"form-control\" name=\"wificPassword\" id=\"wificPassword\" placeholder=\"Wifi password...\" required value=\"$WIFIC_PASSWD\" maxlength=\"19\"> <div class=\"invalid-feedback\"> Valid Wifi client password is required. </div></div></div><div class=\"mb-3\"> <label for=\"rosMasterAddress\">ROS master address</label> <input type=\"text\" class=\"form-control\" name=\"rosMasterAddress\" id=\"rosMasterAddress\" placeholder=\"ROS Master hostname or IPv4 address...\" required value=\"$ROS_MASTER\" maxlength=\"19\"> <div class=\"invalid-feedback\"> Please enter the ROS master address. </div></div><hr class=\"mb-4\"> <button class=\"btn btn-primary btn-lg btn-block\" type=\"submit\">Save parameters</button> </form> </div></div><footer class=\"my-5 pt-5 text-muted text-center text-small\"> <p class=\"mb-1\">&copy; 2018 HeRo Robot \"The small and affordable swarm robot\"</p><ul class=\"list-inline\"> <li class=\"list-inline-item\"><a href=\"https://verlab.dcc.ufmg.br\">VeRLab</a></li> <li class=\"list-inline-item\"><a href=\"https://github.com/verlab/hero_common/\">GitHub</a></li></ul> </footer> </div><script>function ajax_post(url, post_data, callback){var xmlhttp=new XMLHttpRequest(); xmlhttp.onreadystatechange=function(){if (xmlhttp.readyState==4 && xmlhttp.status==200){console.log('responseText:' + xmlhttp.responseText); try{var data=JSON.parse(xmlhttp.responseText);console.log(xmlhttp.responseText);console.log(data);}catch (err){console.log(err.message + \" in \" + xmlhttp.responseText); return;}callback(data);}}; xmlhttp.open(\"POST\", url, true);  xmlhttp.setRequestHeader(\"Content-Type\", \"application/x-www-form-urlencoded; charset=UTF-8\"); xmlhttp.send(post_data);console.log(post_data);}document.getElementById(\"btn-reset\").addEventListener(\"click\", function(){ajax_post('/resetEEPROM', \"\", function(data){if (data.status==\"success\"){window.location.reload(true);}else{alert(\"An error happened, please check your internet connection, HeRo source power and test again.\")}});}); document.getElementById(\"config-form\").addEventListener(\"submit\", function(e){e.preventDefault(); e.stopPropagation(); this.classList.add('was-validated'); if (this.checkValidity()==false){return false;}xhr=new XMLHttpRequest(); console.log(this.elements); var params=[].filter.call(this.elements, function(el){return true;}).filter(function(el){return !!el.name;}).filter(function(el){return !el.disabled;}).map(function(el){return el.name + '=' + el.value;}).join('&'); ajax_post('/saveParams', params, function(data){if (data.status==\"success\"){window.location.reload(true);}else{alert(\"An error happened, please check your internet connection, HeRo source power and test again.\")}}); return false;}); </script></body></html>";
  char tmp_str[20] = "";

  itoa(configurationData.robot_id, tmp_str, 10);
  content.replace("$ROBOT_ID", tmp_str);

  content.replace("$CONFIG_VERSION", CONFIG_VERSION);
  content.replace("$FIRMWARE_VERSION", FIRMWARE_VERSION);
  content.replace("$HARDWARE_VERSION", HARDWARE_VERSION);

  content.replace("$ROBOT_DESC", configurationData.robot_desc);
  content.replace("$WIFIC_SSID", configurationData.wifi_ssid);
  content.replace("$WIFIC_PASSWD", configurationData.wifi_pass);
  content.replace("$ROS_MASTER", configurationData.ros_master_address);

  this->server->send(200, "text/html", content);
  delay(50);
}



void WebConfig::handleSaveParams(void) {

  String robot_id = this->server->arg("robotId");
  String robot_desc = this->server->arg("robotDescription");
  String wific_ssid = this->server->arg("wificSSID");
  String wific_pass = this->server->arg("wificPassword");
  String ros_master = this->server->arg("rosMasterAddress");

  char tmp_str[20] = "";

  configurationData.robot_id = robot_id.toInt();
  strcpy(configurationData.robot_desc, robot_desc.c_str());
  strcpy(configurationData.wifi_ssid, wific_ssid.c_str());
  strcpy(configurationData.wifi_pass, wific_pass.c_str());
  strcpy(configurationData.ros_master_address, ros_master.c_str());

  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.put(MEM_INIT_POS, configurationData);
  EEPROM.end();

  String content = "{\"status\":\"success\"}";
  this->server->send(200, "application/json", content);

  config_status_led = 1;
}

void WebConfig::handleCSS(void) {
  this->server->sendHeader("content-encoding", "gzip");
  this->server->send_P(200, "text/css", css_gzip, sizeof(css_gzip));
}

void WebConfig::handleIcon(void) {
  this->server->sendHeader("content-encoding", "gzip");
  this->server->send_P(200, "image/png", icon_gzip, sizeof(icon_gzip));
}

void WebConfig::handleResetEEPROM(void) {

  char tmp_str[20] = "";

  configurationData.robot_id = -1;
  strcpy(configurationData.robot_desc, tmp_str);
  strcpy(configurationData.ros_master_address, tmp_str);
  strcpy(configurationData.wifi_ssid, tmp_str);
  strcpy(configurationData.wifi_pass, tmp_str);

  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.put(MEM_INIT_POS, configurationData);
  EEPROM.end();

  String content = "{\"status\":\"success\"}";
  this->server->send(200, "application/json", content);

  config_status_led = 2;
}

//no need authentification
void WebConfig::handleNotFound(void) {

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += this->server->uri();
  message += "\nMethod: ";
  message += (this->server->method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += this->server->args();
  message += "\n";
  for (uint8_t i = 0; i < this->server->args(); i++) {
    message += " " + this->server->argName(i) + ": " + this->server->arg(i) + "\n";
  }
  this->server->send(404, "text/plain", message);

  config_status_led = 0;
}
