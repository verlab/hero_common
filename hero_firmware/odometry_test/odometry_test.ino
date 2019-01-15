/* HeRo test odometry */
#include <ros.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <Servo.h>           /* https://www.arduino.cc/en/Reference/Servo */
#include <Encoder.h>         /* https://github.com/PaulStoffregen/Encoder */
#include <PID_v1.h>          /* http://playground.arduino.cc/Code/PIDLibrary */
#include <PID_AutoTune_v0.h> /* https://playground.arduino.cc/Code/PIDAutotuneLibrary */

#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <hero_driver/SetOdom.h>
#include <std_srvs/Trigger.h>

/* Used for encoders */
#define INPUT_PULLUP
#define ENCODER_USE_INTERRUPTS

/* Robot Params */
#define WHEEL_DIAMETER 4.955     // Wheel diameter in cm.
#define WHEEL_SEPARATION 6.335      // Separation between wheels (cm).
#define WHEEL_DISTANCE 0.06335    // Distance between wheels in meters (axis length); it's the same value as "WHEEL_SEPARATION" but expressed in meters.
#define WHEEL_CIRCUMFERENCE ((WHEEL_DIAMETER * M_PI)/100.0)    // Wheel circumference (meters).
#define MOT_STEP_DIST (WHEEL_CIRCUMFERENCE/288.0)      // Distance for each motor step (meters); a complete turn is 288 steps (0.000535598 meters per step (m/steps)).


/* Motors Setup */
boolean halt_motor = false;
Servo l_motor;
Encoder l_encoder(14, 10);
double encoder_gain = 0.06; // max 1.0
int l_motor_fix = 0.0;
double l_motor_speed = 0.0;
double l_motor_control = 0.0;
double l_encoder_speed = 0.0;
float kp = 1200, ki = 7.5, kd = 3.5; // default values for pid
PID l_motor_pid(&l_encoder_speed, &l_motor_control, &l_motor_speed, kp, ki, kd, DIRECT); // blue plot
PID_ATune l_aTune(&l_encoder_speed, &l_motor_control);

Servo r_motor;
Encoder r_encoder(12, 13);
int r_motor_fix = 0.0;
double r_motor_speed = 0.0;
double r_motor_control = 0.0;
double r_encoder_speed = 0.0;
PID r_motor_pid(&r_encoder_speed, &r_motor_control, &r_motor_speed, kp, ki, kd, DIRECT); // red plot
PID_ATune r_aTune(&r_encoder_speed, &r_motor_control);

// autotuner defaults
double aTuneStep = 20;
double aTuneNoise = 0.001; 
unsigned int aTuneLookBack = 4;
boolean tuning = false;

extern Tuning tuningRule[];

/* PID Control loop for motors PWM */
void control(void);

/* Wifi setup */
IPAddress ROS_MASTER_ADDRESS(10, 42, 0, 1); // ros master ip
char* WIFI_SSID = "epuck_net"; // network name
char* WIFI_PASSWD = "epuck_9895"; // network password

/* Used to compute Odometry */
unsigned long timer = 0, currentTime, lastTime, log_timer = 0, tunning_steady_state = 0, rate = 20;
double xPos, yPos, theta;
double deltaSteps, deltaTheta;
double leftStepsDiff = 0, rightStepsDiff = 0;
double leftStepsPrev = 0, rightStepsPrev = 0;

/* ROS Setup */
String hero_name;
/* ROS Node Instaciatation */
ros::NodeHandle nh;
/* Command velocity callback */
void cmdvel_callback(const geometry_msgs::Twist& msg);
String cmdvel_topic;
ros::Subscriber<geometry_msgs::Twist> *cmdvel_sub;
/* TF to publish odom to base_link transformation */
tf::TransformBroadcaster broadcaster;
geometry_msgs::TransformStamped t;
/* Odometry publisher */
nav_msgs::Odometry odom_msg;
/* Frame definitions */
String base_frame, odom_frame;
void update_odom(void);
String odom_topic;
ros::Publisher *odom_pub;
char buf [100];
/* Reset odometry hero */
void set_odom_callback(const hero_driver::SetOdom::Request& req, hero_driver::SetOdom::Response& res);
String set_odom_topic;
ros::ServiceServer<hero_driver::SetOdom::Request, hero_driver::SetOdom::Response> *set_odom_srv;
/* Calibrate motors hero */
void fix_motors_callback(const std_srvs::Trigger::Request& req, std_srvs::Trigger::Response& res);
String fix_motors_topic;
ros::ServiceServer<std_srvs::Trigger::Request, std_srvs::Trigger::Response> *fix_motors_srv;
/* Autotune pid for motors */
void pid_calibration_callback(const std_srvs::Trigger::Request& req, std_srvs::Trigger::Response& res);
String pid_calibration_topic;
ros::ServiceServer<std_srvs::Trigger::Request, std_srvs::Trigger::Response> *pid_calibration_srv;

void setup() {
  /* Connect the ESP8266 the the wifi AP */
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  
  EEPROM.begin(512);
  Serial.begin(115200);

  /* Turn the PID on */
  l_motor_pid.SetOutputLimits(-500, 500);
  l_motor_pid.SetSampleTime(10); // 10 microseconds
  l_motor_pid.SetMode(AUTOMATIC);
  
  r_motor_pid.SetOutputLimits(-500, 500);
  r_motor_pid.SetSampleTime(10); // 10 microseconds
  r_motor_pid.SetMode(AUTOMATIC);

  l_aTune.SetControlType(PID_ATune::SOME_OVERSHOOT_PID); // * set control type for autotuner
  r_aTune.SetControlType(PID_ATune::SOME_OVERSHOOT_PID); // * set control type for autotuner

  l_aTune.SetNoiseBand(aTuneNoise); // * the autotune will ignore signal chatter smaller than this value this should be accurately set
  l_aTune.SetOutputStep(aTuneStep); // * how far above and below the starting value will the output step?   
  l_aTune.SetLookbackSec((int)aTuneLookBack); // * how far back are we looking to identify peaks
  
  r_aTune.SetNoiseBand(aTuneNoise); // * the autotune will ignore signal chatter smaller than this value this should be accurately set
  r_aTune.SetOutputStep(aTuneStep); // * how far above and below the starting value will the output step?   
  r_aTune.SetLookbackSec((int)aTuneLookBack); // * how far back are we looking to identify peaks

  /* Start ROS communication module */
  uint16_t ROS_MASTER_PORT = 11411;
  nh.getHardware()->setConnection(ROS_MASTER_ADDRESS, ROS_MASTER_PORT);

  hero_name = String("/hero_1");
  odom_topic = hero_name + String("/odom");
  odom_pub = new ros::Publisher(odom_topic.c_str(), &odom_msg);

  cmdvel_topic = hero_name + String("/cmd_vel");
  cmdvel_sub = new ros::Subscriber<geometry_msgs::Twist>(cmdvel_topic.c_str(), cmdvel_callback);

  /* Starting ros node */
  nh.initNode();
  
  /* Address Publishers */
  broadcaster.init(nh);
  nh.advertise(*odom_pub);
  odom_frame = hero_name + String("/odom");
  base_frame  = hero_name + String("/base_link");
  odom_msg.header.frame_id = odom_frame.c_str();
  odom_msg.header.seq = -1;
  odom_msg.child_frame_id = base_frame.c_str();
  
  /* Address Subscribers */
  nh.subscribe(*cmdvel_sub);

  /* Service setup */
  set_odom_topic = hero_name + String("/set_odom");
  set_odom_srv = new ros::ServiceServer<hero_driver::SetOdom::Request, hero_driver::SetOdom::Response>(set_odom_topic.c_str(), &set_odom_callback);
  nh.advertiseService(*set_odom_srv);

  fix_motors_topic = hero_name + String("/fix_motors");
  fix_motors_srv = new ros::ServiceServer<std_srvs::Trigger::Request, std_srvs::Trigger::Response>(fix_motors_topic.c_str(), &fix_motors_callback);
  nh.advertiseService(*fix_motors_srv);

  pid_calibration_topic = hero_name + String("/pid_calibration");
  pid_calibration_srv = new ros::ServiceServer<std_srvs::Trigger::Request, std_srvs::Trigger::Response>(pid_calibration_topic.c_str(), &pid_calibration_callback);
  nh.advertiseService(*pid_calibration_srv);

  /* Setup complete esp LED message */
  pinMode(LED_BUILTIN, OUTPUT);
  for(int i = 0; i <= 20; i++){
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(100);                   
  }
  
  /* Attach motors */
  //l_motor.attach(5);
  //r_motor.attach(16);

  /* Halt motors */
  l_motor_fix = 1500 - (int) EEPROM.read(1);
  l_motor.writeMicroseconds(l_motor_fix);
  r_motor_fix = 1500 - (int) EEPROM.read(0);
  r_motor.writeMicroseconds(r_motor_fix);
  
  /* Initiate encoder */
  l_encoder.write(0);
  r_encoder.write(0);
  leftStepsPrev = l_encoder.read();
  rightStepsPrev = r_encoder.read();
  
  /* ROS LOG */
  //Serial.println("\n\n Welcome to hero odometry test! ");
  sprintf(buf,"\x1b[1;37;43m Welcome to Hero #1 odometry test! \x1b[0m");
  nh.loginfo(buf);
  lastTime = micros();
}



/************************************************************************
 * M A I N  L O 0 P
 ************************************************************************/
long motorPositionRight = 0;
long motorPositionLeft = 0;
bool l_done, r_done;
void loop() {
    if (tuning){
      if ((millis() - tunning_steady_state) > 10000){ // 10 secons to steady state
        if (!l_done) l_done = l_aTune.Runtime();
        if (!r_done) r_done = r_aTune.Runtime();
        if (l_done && r_done){
          tuning = false; // we're done, set the tuning parameters
          kp = l_aTune.GetKp()*3.2;
          ki = l_aTune.GetKi()*0.07;
          kd = l_aTune.GetKd()*0.002;
          if (kp > 100 && kp < 2500){ // * Tuning is successed
            l_motor_pid.SetTunings(kp, ki, kd);
            l_motor_pid.SetMode(l_motor_pid.GetMode());
            l_aTune.Cancel();
          } else{ // * Tuning is failure
            nh.loginfo("\x1b[1;31;41m Left Motor Tuning Failure! \x1b[0m");
          }
          sprintf(buf,"\x1b[1;37;43m Left Motor Best PID params: kp, %f, ki, %f, kd,%f\x1b[0m", kp, ki, kd);
          nh.loginfo(buf);
          kp = r_aTune.GetKp()*3.2;
          ki = r_aTune.GetKi()*0.07;
          kd = r_aTune.GetKd()*0.002;
          if (kp > 100 && kp < 2500){ // * Tuning is successed
            r_motor_pid.SetTunings(kp, ki, kd);
            r_motor_pid.SetMode(r_motor_pid.GetMode());
            r_aTune.Cancel();
          } else{ // * Tuning is failure
            nh.loginfo("\x1b[1;31;41m Right Motor Tuning Failure! \x1b[0m");
          }
          sprintf(buf,"\x1b[1;37;43m Right Motor Best PID params: kp, %f, ki, %f, kd,%f\x1b[0m", kp, ki, kd);
            nh.loginfo(buf);
        }
      }
        l_motor.writeMicroseconds((int)l_motor_control + l_motor_fix);
        r_motor.writeMicroseconds((int)-r_motor_control + r_motor_fix);
    }
    else{
      /* PID control loop */
      if (!halt_motor) control(); 
    }
    
    /* Update motor position */
    motorPositionRight = r_encoder.read();
    motorPositionLeft = l_encoder.read();
    
    /* ROS INFOS */
    if ((millis() - log_timer) > 200){
      log_timer = millis();
      /*if (tuning && (millis() - tunning_steady_state) > 10000) {
        nh.loginfo("Tuning! Waiting... ");
        sprintf(buf,"left motor control: %f", l_motor_control);
        nh.loginfo(buf);
      }*/
      //sprintf(buf,"lmc, %f, tlmc, %d", l_motor_control, speed2pwm((float)l_motor_control));
      //nh.loginfo(buf);
    }

    /* ROS Loop */
    if (millis() - timer > rate){ 
      timer = millis();
      update_odom();
      nh.spinOnce();
    }
}

/* pid control loop for wheel speed */
void control(void){
  /* Update control loop and set the output to the motors */
  l_motor_pid.Compute();
  r_motor_pid.Compute();
  l_motor.writeMicroseconds((int)l_motor_control + l_motor_fix);
  r_motor.writeMicroseconds((int)(-r_motor_control) + r_motor_fix);
}

/************************************************************************
 * P U B L I S H E R S
 ************************************************************************/
/* Update and publish odom data */
void update_odom(void){
   currentTime = micros();
  
  /* Compute the difference of ticks */
  leftStepsDiff = motorPositionLeft - leftStepsPrev; // Expressed in tickes.
  rightStepsDiff = motorPositionRight - rightStepsPrev;   // Expressed in tickes.

  /* Update last encoder ticks*/
  leftStepsPrev = motorPositionLeft;   // Expressed in meters.
  rightStepsPrev = motorPositionRight; // Expressed in meters.

  /* Transform ticks to distance in meters */
  double leftdist = MOT_STEP_DIST * leftStepsDiff;
  double rightdist = MOT_STEP_DIST * rightStepsDiff;
  
  /* Get encoder speed in m/s */
  /* Complementary filter */
  l_encoder_speed = ((1.0 - encoder_gain) * l_encoder_speed + encoder_gain * (double) leftdist / ((double)(currentTime-lastTime)/1000000.0));
  l_encoder_speed *= 5/3;
  r_encoder_speed = ((1.0 - encoder_gain) * r_encoder_speed + encoder_gain * (double) rightdist / ((double)(currentTime-lastTime)/1000000.0));
  r_encoder_speed *= 5/3;

  odom_msg.twist.twist.linear.y = l_encoder_speed;
  odom_msg.twist.twist.linear.z = r_encoder_speed;
  
  odom_msg.twist.twist.angular.x = (double) leftdist / ((double)(currentTime-lastTime)/1000000.0);
  odom_msg.twist.twist.angular.y = (double) rightdist / ((double)(currentTime-lastTime)/1000000.0);
  
  lastTime = micros();

  /* Compute Odometry */
  /*if (rightStepsDiff == leftStepsDiff){
    deltaSteps = leftdist;
    deltaTheta = 0.0;
    xPos += deltaSteps * cos(theta);
    yPos += deltaSteps * sin(theta);
  } 
  else{*/
    deltaTheta =  (rightdist - leftdist) / WHEEL_DISTANCE; /* Expressed in radiant. */ 
    //deltaSteps = WHEEL_DISTANCE * (rightdist + leftdist) / (2*(rightdist - leftdist)); /* Expressed in meters. */ 
    
    //xPos += deltaSteps * (sin(theta + deltaTheta) - sin(theta)); /* Expressed in meters. */ 
    //yPos += deltaSteps * (-cos(theta + deltaTheta) + cos(theta)); /* Expressed in meters. */ 
    
    deltaSteps = (rightdist + leftdist) / (2.0); /* epuck-like. */ 
    xPos += deltaSteps * cos(theta + deltaTheta/2.0);
    yPos += deltaSteps * sin(theta + deltaTheta/2.0);
    
    theta += deltaTheta; /* Expressed in radiant. */ 
    if (theta > M_PI) theta = theta - 2.0 * M_PI;
    if (theta < -M_PI) theta = theta + 2.0 * M_PI;
    
  //}

  /* Update odom topic */
  odom_msg.pose.pose.position.x = xPos;       
  odom_msg.pose.pose.position.y = yPos;
  odom_msg.pose.pose.position.z = theta;

  /* Since all odometry is 6DOF we'll need a quaternion created from yaw. */
  odom_msg.pose.pose.orientation = tf::createQuaternionFromYaw(theta);

  /* Robot linear speed in m/s */
  odom_msg.twist.twist.linear.x = (r_encoder_speed + l_encoder_speed)/2.0;   
  /* Wheel speed in m/s */
  
  /* Robot angular speed in rad/s */                                                                                      
  odom_msg.twist.twist.angular.z = (r_encoder_speed - l_encoder_speed)/ WHEEL_DISTANCE;  

  /* publish odometry */
  odom_msg.header.stamp = nh.now();
  odom_msg.header.seq++;
  odom_pub->publish( &odom_msg );
  
  /* tf odom->base_link */
  t.header.frame_id = odom_frame.c_str();
  t.child_frame_id = base_frame.c_str();
  t.transform.translation.x = xPos;
  t.transform.translation.y = yPos;
  t.transform.translation.z = 0;
  t.transform.rotation = tf::createQuaternionFromYaw(theta);
  t.header.stamp = nh.now();
  broadcaster.sendTransform(t);
  
 }


/************************************************************************
 * C A L L B A C K S
 ************************************************************************/
void cmdvel_callback(const geometry_msgs::Twist& msg){
  /* Get robot velocities */
  float linear = max(min((double)msg.linear.x, 0.25), -0.25); // max linear speed 0.25 m/s
  float angular = max(min((double)msg.angular.z, 0.08), -0.08); // max angular speed 0.08 rad/s
  
  /* Inverse Kinematic of a Differential Drive Robot */
  l_motor_speed = (double)(2.0 * linear - WHEEL_SEPARATION * angular) / 2.0;
  r_motor_speed = (double)(2.0 * linear + WHEEL_SEPARATION * angular) / 2.0;

  if (linear == 0.0 && angular == 0.0){
    l_motor.detach();
    r_motor.detach();
    l_motor_control = 0;
    r_motor_control = 0;
    halt_motor = true;
    //nh.loginfo("\x1b[1;37;43m[HERO 1] Detach motors!\x1b[0m");
  }else{
    l_motor.attach(5);
    r_motor.attach(16);
    halt_motor = false;
    //nh.loginfo("\x1b[1;37;43m[HERO 1] Attach motors!\x1b[0m");
  }
  // Disable tunning if still receiving commands
  tuning = false;
  l_aTune.Cancel();
  r_aTune.Cancel();
}


/* Set odometry initial position */
void set_odom_callback( const hero_driver::SetOdom::Request& req, hero_driver::SetOdom::Response& res){
  l_encoder.write(0);
  r_encoder.write(0);

  leftStepsPrev = l_encoder.read();
  rightStepsPrev = r_encoder.read();
  
  xPos = req.x;
  yPos = req.y;
  theta = req.theta;
  res.success = 1;
  res.message = "Odometry was changed!";
  nh.loginfo("[HERO] Odometry was changed!");
}


/* Fix motors halt position */
void fix_motors_callback(const std_srvs::Trigger::Request& req, std_srvs::Trigger::Response& res){
  EEPROM.begin(512);
  if (fabs(l_encoder_speed) <= 0.0001 && fabs(r_encoder_speed) <= 0.0001){
    l_motor_fix = l_motor.readMicroseconds();
    EEPROM.write(0, uint8_t(1500-l_motor.readMicroseconds()));
    r_motor_fix = r_motor.readMicroseconds();
    EEPROM.write(1, uint8_t(1500-r_motor.readMicroseconds()));
    EEPROM.commit();
  }
  sprintf(buf,"Left Motor Halt Position: %d, Right Motor Halt Position: %d", EEPROM.read(0), EEPROM.read(1));
  nh.loginfo(buf);
  res.success = 1;
  res.message = "Motors are calibrated!";
  EEPROM.end();
}


/* Autotune PID Motors */
void pid_calibration_callback(const std_srvs::Trigger::Request& req, std_srvs::Trigger::Response& res){
  nh.loginfo("\x1b[1;37;43m[HERO 1] Starting Motors Auto Tuning! Wait... \x1b[0m");
  l_motor.attach(5);
  r_motor.attach(16);
  tuning = false;
  l_aTune.Cancel();
  r_aTune.Cancel();
  
  l_motor_control = 50; // this should be outputStart in Autotune
  r_motor_control = 50; // this should be outputStart in Autotune
  l_done = false;
  r_done = false;
  tunning_steady_state = millis();
  tuning = true;
  res.message = "PID Autotuning!";
}



