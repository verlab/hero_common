/*
 * This sketch implements ping server
 * We intend to measure the delay among the esp and the PC.
 *
 */

#include <ESP8266WiFi.h>

//#define USE_UDP_PROTOCOL
#define ROSSERIAL_ARDUINO_TCP

#include <ros.h>
#include <std_msgs/Header.h>

const char* ssid     = "Rezeck";
const char* password = "cwtbvapx";

//const char* ssid     = "rezeck";
//const char* password = "s3cr3tp4ss";

// Set the rosserial socket server IP address
IPAddress server(192,168,18,31);
//IPAddress server(10,42,0,1);
// Set the rosserial socket server port
const uint16_t serverPort = 11411;




ros::NodeHandle nh;
// Make a chatter publisher
std_msgs::Header msg_;
ros::Publisher pub_("esp2pc", &msg_);

void messageCb( const std_msgs::Header& toggle_msg){
//  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
pub_.publish(&toggle_msg);
}

ros::Subscriber<std_msgs::Header> sub("pc2esp", messageCb);

void setup()
{
  // Use ESP8266 serial to monitor the process
//  Serial.begin(115200);
//  Serial.println();
//  Serial.print("Connecting to ");
//  Serial.println(ssid);

  // Connect the ESP8266 the the wifi AP
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
//    Serial.print(".");
  }
//  Serial.println("");
//  Serial.println("WiFi connected");
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());

  // Set the connection to rosserial socket server
  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();

  // Another way to get IP
//  Serial.print("IP = ");
//  Serial.println(nh.getHardware()->getLocalIP());

  // Start to be polite
  nh.advertise(pub_);
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  // Loop exproximativly at 10 Hz
//  delay(100);
}
