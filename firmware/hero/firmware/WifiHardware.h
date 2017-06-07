/*
 ************************************************************************
 *  W I F I  H A R D W A R E
 ************************************************************************
 *
 * Paulo Rezeck <rezeck@dcc.ufmg.br>
 * Hector Azpurua <hectorxxx@gmail.com>
 * 
 * HeRo Project
 * Computer Vision and Robotics Lab
 * Federal University of Minas Gerais - Brazil
 ************************************************************************/

#ifndef __WIFIHARDWARE_H__
#define __WIFIHARDWARE_H__

#include <ESP8266WiFi.h>

#define DEBUG 1

class WifiHardware {
  public:
    WifiHardware()
    {
    }
    
    void setROSConnection(IPAddress &server, int port) {
      this->server = server;
      this->serverPort = port;
    }

    void connectWifi(const char* ssid, const char* password) {
      int WiFiCounter = 0;
      if(DEBUG){
        Serial.print("Connecting to: '");
        Serial.print(ssid);
        Serial.print("' WiFi network ");
      }
      
      WiFi.disconnect();
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED && WiFiCounter < 30) {
        delay(1000);
        WiFiCounter++;
        if(DEBUG){
          Serial.print(".");
        }
      }
    
      if(DEBUG){
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
      }
    }
    
    IPAddress getLocalIP() {
      return tcp.localIP();
    }

    void init() { 
      this->tcp.connect(this->server, this->serverPort);
    }

    int read() {
      if (this->tcp.connected()) {
        return tcp.read();
      } else {
        this->tcp.connect(this->server, this->serverPort);
      }
      return -1;
    };
    
    void write(const uint8_t* data, size_t length) {
      tcp.write(data, length);
    }

    unsigned long time() {return millis();}

  protected:
    WiFiClient tcp;
    IPAddress server; 
    uint16_t serverPort = 11411;
};

#endif  // __WIFIHARDWARE_H__
