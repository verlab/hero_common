/************************************************************************
   H E R O   M O T O R  T E S T
************************************************************************

  Paulo Rezeck <rezeck@dcc.ufmg.br>
  Mauricio Ferrari <mauferrari@dcc.ufmg.br>
  Hector Azpurua <hectorxxx@gmail.com>

  HeRo Project
  Computer Vision and Robotics Lab
  Federal University of Minas Gerais - Brazil
************************************************************************/
#include <ros.h>
#include <hero_common/Motor.h>
#include <Servo.h>                      /* https://www.arduino.cc/en/Reference/Servo */

#include <ESP8266WiFi.h>

#define HERO_ID "1"

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
String motor_topic;                                    /* Topic name */
ros::Subscriber<hero_common::Motor> *motor_sub;      /* Message type */
void motor_callback(const hero_common::Motor& msg);  /* Callback function */

char buf [100];

void setup() {
  /* Connect the ESP8266 the the wifi AP */
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  /* Start ROS communication module */
  uint16_t ROS_MASTER_PORT = 11411;
  nh.getHardware()->setConnection(ROS_MASTER_ADDRESS, ROS_MASTER_PORT);

  /* Setup laser publisher */
  hero_name = String("/hero_") + String(HERO_ID);
  /* Address command velocity subscribe */
  motor_topic = hero_name + String("/motor");                                                     /* Update topic name */
  motor_sub = new ros::Subscriber<hero_common::Motor>(motor_topic.c_str(), motor_callback);     /* Instantiate subscriber */
  nh.subscribe(*motor_sub);                                                                         /* Address Command Vel */

  /* Starting ros node */
  nh.initNode();

  /* Initiate Motors */
  r_motor.attach(MOTOR_RIGHT);
  l_motor.attach(MOTOR_LEFT);
  r_motor.writeMicroseconds(MOTOR_HALT_PWM);
  l_motor.writeMicroseconds(MOTOR_HALT_PWM);
  delayMicroseconds(100);
  r_motor.detach();
  l_motor.detach();
  //delay(1000);


  /* ROS LOG */
  sprintf(buf, "\33[96m[%s] Hero test mode - Motor Test! \33[0m", hero_name.c_str());
  nh.loginfo(buf);
}

unsigned long timer = 0, log_timer, rate = 10;

void loop() {

  if ((millis() - log_timer) > 1000) {
    log_timer = millis();
    sprintf(buf, "\33[96m[%s] Conected at time %d\33[0m", hero_name.c_str(), millis());
    nh.loginfo(buf);
  }

  /* ROS Loop */
  if (millis() - timer > 1000.0 / rate) {
    timer = millis();
    nh.spinOnce();
  }
}


/* Compute inverse kinematic of a Differential Drive Robot */
void motor_callback(const hero_common::Motor& msg) {
  /* Get PWM */
  float m_left = msg.left_motor_pwm;
  float m_right = msg.right_motor_pwm;

  if (m_left >= 1000 && m_left <= 2000) {
    l_motor.attach(MOTOR_LEFT);
  } else {
    l_motor.detach();
  }

  if (m_right >= 1000 && m_right <= 2000) {
    r_motor.attach(MOTOR_RIGHT);
  } else {
    r_motor.detach();
  }
  r_motor.writeMicroseconds((int)m_right);
  l_motor.writeMicroseconds((int)m_left);
}
