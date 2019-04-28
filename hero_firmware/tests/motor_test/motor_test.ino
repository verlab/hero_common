 /************************************************************************
 *  H E R O   M O T O R  T E S T 
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
#include <geometry_msgs/Twist.h>
#include <Servo.h>                      /* https://www.arduino.cc/en/Reference/Servo */

#include <ESP8266WiFi.h>

/* Motor Configuration */
#define MOTOR_RIGHT 16        /* PIN D3 */
#define MOTOR_LEFT 0          /* PIN D0 */
#define MOTOR_HALT_PWM 1300   /* PWM Range 1000-2000*/

/* Motor Configuration */
Servo dummy;
Servo l_motor; /* Left Motor Control */
Servo r_motor; /* Right Motor Control */

/* Wifi setup */
IPAddress ROS_MASTER_ADDRESS(10, 42, 0, 1); // ros master ip
char* WIFI_SSID = "hero_network"; // network name
char* WIFI_PASSWD = "s3cr3tp4ss"; // network password

/* ROS Setup */
String hero_name;
/* ROS Node Instaciatation */
ros::NodeHandle nh;
/** Subscribers **/
/* Command Velocity Callback */
String cmdvel_topic;                                    /* Topic name */
ros::Subscriber<geometry_msgs::Twist> *cmdvel_sub;      /* Message type */
void cmdvel_callback(const geometry_msgs::Twist& msg);  /* Callback function */

void setup() {
     /* Connect the ESP8266 the the wifi AP */
    WiFi.begin(WIFI_SSID, WIFI_PASSWD);
    while (WiFi.status() != WL_CONNECTED) delay(500);
  
    /* Start ROS communication module */
    uint16_t ROS_MASTER_PORT = 11411;
    nh.getHardware()->setConnection(ROS_MASTER_ADDRESS, ROS_MASTER_PORT);
  
    /* Setup laser publisher */
    hero_name = String("/hero_1");
    /* Address command velocity subscribe */
    cmdvel_topic = hero_name + String("/cmd_vel");                                                     /* Update topic name */
    cmdvel_sub = new ros::Subscriber<geometry_msgs::Twist>(cmdvel_topic.c_str(), cmdvel_callback);     /* Instantiate subscriber */
    nh.subscribe(*cmdvel_sub);                                                                         /* Address Command Vel */
  
    /* Starting ros node */
    nh.initNode();

     /* Initiate Motors */
    r_motor.attach(MOTOR_RIGHT);
    l_motor.attach(MOTOR_LEFT);
    r_motor.writeMicroseconds(MOTOR_HALT_PWM);
    l_motor.writeMicroseconds(MOTOR_HALT_PWM);
    delayMicroseconds(100);
    //r_motor.detach();
    //l_motor.detach();
    //delay(1000);
}

unsigned long timer = 0;

void loop() {
    /* ROS Loop */
    if (millis() - timer > 50){ 
      timer = millis();
      nh.spinOnce();
    }
}


/* Compute inverse kinematic of a Differential Drive Robot */
void cmdvel_callback(const geometry_msgs::Twist& msg){
  /* Get PWM */
  float m_left = msg.linear.x;
  float m_right = msg.linear.y;
  r_motor.writeMicroseconds((int)m_right);
  l_motor.writeMicroseconds((int)m_left);
}

