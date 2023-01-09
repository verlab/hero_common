/************************************************************************
   H E R O   N E O   P I X E L   A N D   I R   T E S T
************************************************************************

  Paulo Rezeck <rezeck@dcc.ufmg.br>
  Mauricio Ferrari <mauferrari@dcc.ufmg.br>
  Hector Azpurua <hectorxxx@gmail.com>

  HeRo Project
  Computer Vision and Robotics Lab
  Federal University of Minas Gerais - Brazil
************************************************************************/
/* ROS Library */
#define ROSSERIAL_ARDUINO_TCP
#include <ros.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/ColorRGBA.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <hero_common/SetFrequency.h>

/* Service types */
#include <hero_common/SetOdom.h>
#include <hero_common/SetFrequency.h>
#include <hero_common/SetPID.h>
#include <hero_common/Encoder.h>
#include <hero_common/Motor.h>
#include <std_srvs/Trigger.h>

#include <ESP8266WiFi.h>

#include <NeoPixelBus.h>
#include <NeoPixelBrightnessBus.h>
#define colorSaturation 255

#define HERO_ID "0"

const uint16_t PixelCount = 7; // this example assumes 4 pixels, making it smaller will cause a failure
NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp8266Uart1800KbpsMethod> strip(PixelCount);
RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor black(0, 0, 0);

/* Timer */
double timer, log_timer, rate = 10;

///* Wifi setup */
IPAddress ROS_MASTER_ADDRESS(10, 42, 0, 1); // ros master ip
char* WIFI_SSID = "rezeck"; // network name
char* WIFI_PASSWD = "s3cr3tp4ss"; // network password

/* ROS Setup */
String hero_name;
/* ROS Node Instaciatation */
ros::NodeHandle nh;

/* Laser publisher */
sensor_msgs::LaserScan laser_msg;

/* Frame definitions */
String laser_frame;
void update_laser(void);
String laser_topic;
ros::Publisher *laser_pub;

/* Analog Multiplexer 4051 */
const int s0 = 12; // D6 Blue
const int s1 = 13; // D7 Green
const int s2 = 15; // D8 Yellow
const int enable = 2;

/* LED callback */
void led_callback(const std_msgs::ColorRGBA& msg);
String led_topic;
ros::Subscriber<std_msgs::ColorRGBA> *led_sub;

/* Set loop-frequency */
ros::ServiceServer<hero_common::SetFrequency::Request, hero_common::SetFrequency::Response> *set_frequency_srv;         /* Service Type */
String set_frequency_topic;                                                                                             /* Service name */
void set_frequency_callback(const hero_common::SetFrequency::Request& req, hero_common::SetFrequency::Response& res);   /* Callback function */

char buf [100];

/* Setup */
void setup() {
  pinMode(enable, OUTPUT);
  analogWrite(enable, 0);
  /* Connect the ESP8266 the the wifi AP */
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  Serial.begin(115200);

  /* Start ROS communication module */
  uint16_t ROS_MASTER_PORT = 11411;
  nh.getHardware()->setConnection(ROS_MASTER_ADDRESS, ROS_MASTER_PORT);

  /* Setup laser publisher */
  hero_name = String("/hero_") + String(HERO_ID);

  led_topic = hero_name + String("/led");
  led_sub = new ros::Subscriber<std_msgs::ColorRGBA>(led_topic.c_str(), led_callback);

  /* Setup laser publisher */
  laser_topic = hero_name + String("/laser");
  laser_pub = new ros::Publisher(laser_topic.c_str(), &laser_msg);

  /* Starting ros node */
  nh.initNode();

  /* Address Publishers */
  nh.advertise(*laser_pub);
  laser_frame = hero_name + String("/laser");
  laser_msg.header.frame_id = laser_frame.c_str();
  laser_msg.header.seq = -1;
  laser_msg.range_min = 0.0;
  laser_msg.range_max = 1024.0;
  laser_msg.angle_min = 0.0;
  laser_msg.angle_max = 2 * M_PI;
  laser_msg.angle_increment = 0.79; // radians
  laser_msg.ranges_length = 8;
  laser_msg.ranges = (float *)malloc(8 * sizeof(float));
  laser_msg.intensities_length = 8;
  laser_msg.intensities = (float *)malloc(8 * sizeof(float));
  laser_msg.header.seq = 0;

  /* Address set frequency service */
  set_frequency_topic = hero_name + String("/set_frequency");                                                                                                                 /* Update service name */
  set_frequency_srv = new ros::ServiceServer<hero_common::SetFrequency::Request, hero_common::SetFrequency::Response>(set_frequency_topic.c_str(), &set_frequency_callback);  /* Instantiate service */
  nh.advertiseService(*set_frequency_srv);
  
  /* Setup Analog Multiplexer Pins */
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(enable, OUTPUT);
  analogWrite(enable, 0);
  readIR();

  /* Address Subscribers */
  nh.subscribe(*led_sub);

  /* Setup complete esp LED message */
  // this resets all the neopixels to an off state
  strip.Begin();
  strip.Show();
  for (int i = 0; i <= PixelCount; i++) {
    strip.SetPixelColor(i, black);
  }
  strip.SetBrightness(64);
  strip.Show();

  //pinMode(LED_BUILTIN, OUTPUT);
  for (int i = 0; i <= PixelCount * 6; i++) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    if (i % 8 > 2) continue;
    strip.SetPixelColor(i % 8, green);
    strip.SetBrightness(16);
    strip.Show();
    delay(100);
    strip.SetPixelColor(i % 8, black);
  }
  strip.Show();

  /* ROS LOG */
  sprintf(buf, "\33[96m[%s] Hero test mode - NeoPixel and IR Test! \33[0m", hero_name.c_str());
  nh.loginfo(buf);
}



/************************************************************************
   M A I N  L O 0 P
 ************************************************************************/
void loop() {
  /* ROS INFOS */
  if ((millis() - log_timer) > 1000) {
    log_timer = millis();
    sprintf(buf, "\33[96m[%s] Conected at time %d\33[0m", hero_name.c_str(), millis());
    nh.loginfo(buf);
  }

  /* ROS Loop */
  if (millis() - timer > 1000 / rate) {
    timer = millis();
    readIR();
    nh.spinOnce();

  }
}

void readIR() {
  pinMode(enable, OUTPUT);
  for (int count = 0; count <= 7; count++) {
    /* select the input  */
    int r0 = count & 0x01;
    int r1 = (count >> 1) & 0x01;
    int r2 = (count >> 2) & 0x01;
    digitalWrite(s0, r0);
    digitalWrite(s1, r1);
    digitalWrite(s2, r2);
    /* Receptor precisa descansar para pois o todos os emissores são ligados juntos
      1. Ler A0 sensor light
      2. Emite todos emisores e espera 100 us
      3. Ler A0 sensor proximity
      4. Espera até A1 desaturar e repete para A1 {até A7}
      OBS. Parece que os Emisor mais escuro se recupera mais rapido da saturação
    */
    delayMicroseconds(500);  // diode should power up in 100 us
    float env = analogRead(A0);
    analogWrite(enable, 1024); // turn on all diode and enable mux
    delayMicroseconds(100);  // diode should power up in 100 us -> 180 us

    laser_msg.ranges[count] = analogRead(A0) - env;
    laser_msg.intensities[count] = env;

    analogWrite(enable, 0); // turn off all diode and enable mux
  }

  /* Send laser message to be published into ROS */
  laser_msg.header.seq++;
  laser_msg.header.stamp = nh.now();
  laser_pub->publish( &laser_msg );

}

void led_callback(const std_msgs::ColorRGBA& msg) {
  strip.Begin();
  delay(50);
  RgbColor color(msg.r * 255, msg.g * 255, msg.b * 255);
  for (int i = 0; i <= PixelCount; i++) {
    //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    strip.SetPixelColor(i, color);
  }
  strip.SetBrightness(msg.a * 255);
  strip.Show();
}

/* Set loop-frequency */
void set_frequency_callback( const hero_common::SetFrequency::Request& req, hero_common::SetFrequency::Response& res) {
  rate = req.frequency;
  res.success = 1;
  res.message = "Changing the loop-frequency.";
  sprintf(buf, "\33[96m[%s] Changing loop-frequency to %f Hz \33[0m", hero_name.c_str(), req.frequency);
  nh.loginfo(buf);
}
