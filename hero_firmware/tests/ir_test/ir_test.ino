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
/* ROS Library */
#define ROSSERIAL_ARDUINO_TCP
#include <ros.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/ColorRGBA.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>

#include <ESP8266WiFi.h>

/* Timer */
double timer, log_timer, rate = 50;

/* Wifi setup */
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

  /* Setup Analog Multiplexer Pins */
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(enable, OUTPUT);
  readIR();
  
  pinMode(LED_BUILTIN, OUTPUT);
  
  /* ROS LOG */
  //Serial.println("\n\n Welcome to hero odometry test! ");
  sprintf(buf,"\33[96m Welcome to Hero test mode - IR Test! \33[0m");
  nh.loginfo(buf);
}



/************************************************************************
 * M A I N  L O 0 P
 ************************************************************************/
void loop() { 
    /* ROS INFOS */
    if ((millis() - log_timer) > 3000){
      log_timer = millis();
      sprintf(buf,"\33[96m[HERO-Test] Conected at time %d\33[0m", millis());
      nh.loginfo(buf);
    }

    /* ROS Loop */
    if (millis() - timer > rate){ 
      timer = millis();
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
