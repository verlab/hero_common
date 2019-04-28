 /************************************************************************
 *  H E R O   I R   T E S T
 ************************************************************************
 *
 * Paulo Rezeck <rezeck@dcc.ufmg.br>
 * Mauricio Ferrari <mauferrari@dcc.ufmg.br>
 * Hector Azpurua <hectorxxx@gmail.com>
 * 
 * HeRo Project
 * Computer Vision and Robotics Lab
 * Federal University of Minas Gerais - Brazil
 ************************************************************************/
#include <ros.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/ColorRGBA.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>

#include <ESP8266WiFi.h>

#include <NeoPixelBus.h>
#include <NeoPixelBrightnessBus.h>
#define colorSaturation 128

const uint16_t PixelCount = 7; // this example assumes 4 pixels, making it smaller will cause a failure
NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(PixelCount);
RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor black(0);

/* Timer */
double timer, log_timer, rate = 50;

/* Wifi setup */
IPAddress ROS_MASTER_ADDRESS(10, 42, 0, 1); // ros master ip
char* WIFI_SSID = "epuck_net"; // network name
char* WIFI_PASSWD = "epuck_9895"; // network password

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

/* LED callback */
void led_callback(const std_msgs::ColorRGBA& msg);
String led_topic;
ros::Subscriber<std_msgs::ColorRGBA> *led_sub;

char buf [100];

/* Analog Multiplexer 4051 */
const int s0 = 12; // D6 Blue
const int s1 = 13; // D7 Green
const int s2 = 15; // D8 Yellow
const int enable = 2;

/* Setup */
void setup() {
  /* Connect the ESP8266 the the wifi AP */
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  
  Serial.begin(115200);

  /* Start ROS communication module */
  uint16_t ROS_MASTER_PORT = 11411;
  nh.getHardware()->setConnection(ROS_MASTER_ADDRESS, ROS_MASTER_PORT);

  /* Setup laser publisher */
  hero_name = String("/hero_1");
  laser_topic = hero_name + String("/laser");
  laser_pub = new ros::Publisher(laser_topic.c_str(), &laser_msg);

  led_topic = hero_name + String("/led");
  led_sub = new ros::Subscriber<std_msgs::ColorRGBA>(led_topic.c_str(), led_callback);

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

  /* Address Subscribers */
  nh.subscribe(*led_sub);

  /* Setup Analog Multiplexer Pins */
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(enable, OUTPUT);
  readIR();

  /* Setup complete esp LED message */
  // this resets all the neopixels to an off state
  strip.Begin();
  strip.Show();
  for(int i = 0; i < PixelCount; i++){
    strip.SetPixelColor(i, black);
  }
  strip.SetBrightness(64);
  strip.Show();
  
  pinMode(LED_BUILTIN, OUTPUT);
  for(int i = 0; i <= 7 * 4; i++){
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    if (i % 8 == 0) continue;
    if (laser_msg.ranges[0] > 900)
      strip.SetPixelColor(i % 8, green);
    else
      strip.SetPixelColor(i % 8, red);
    strip.SetBrightness(16);
    strip.Show();
    delay(100);                   
    strip.SetPixelColor(i % 8, black);
  }
  strip.Show();
  
  /* ROS LOG */
  //Serial.println("\n\n Welcome to hero odometry test! ");
  sprintf(buf,"\33[96m Welcome to Hero #1 - IR Test! \33[0m");
  nh.loginfo(buf);
}



/************************************************************************
 * M A I N  L O 0 P
 ************************************************************************/
void loop() { 
    /* ROS INFOS */
    if ((millis() - log_timer) > 3000){
      log_timer = millis();
      sprintf(buf,"\33[96m[HERO-1] Conected at time %d\33[0m", millis());
      nh.loginfo(buf);
    }

    /* ROS Loop */
    if (millis() - timer > rate){ 
      timer = millis();
      //update_odom();
      readIR();
      nh.spinOnce();
    }
}


void readIR(){
  for (int count = 0; count <= 7; count++) {
    /* select the input  */
    int r0 = count & 0x01;
    int r1 = (count>>1) & 0x01;
    int r2 = (count>>2) & 0x01;
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
  laser_msg.header.stamp = nh.now();
  laser_pub->publish( &laser_msg ); 

}


void led_callback(const std_msgs::ColorRGBA& msg){
  strip.Begin();
  RgbColor color(msg.r, msg.g, msg.b);
  for(int i = 0; i <= 7; i++){
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    strip.SetPixelColor(i, color);
  }
  strip.SetBrightness(msg.a);
  strip.Show();
}

