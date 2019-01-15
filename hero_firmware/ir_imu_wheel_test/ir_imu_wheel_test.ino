 /************************************************************************
 *  H E R O   I R   A N D   I M U   ODOMETRY T E S T
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
#include <sensor_msgs/Imu.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <Servo.h>           /* https://www.arduino.cc/en/Reference/Servo */
#include <Encoder.h>         /* https://github.com/PaulStoffregen/Encoder */
#include <PID_v1.h>          /* http://playground.arduino.cc/Code/PIDLibrary */
#include <PID_AutoTune_v0.h> /* https://playground.arduino.cc/Code/PIDAutotuneLibrary */

#include <EEPROM.h>

#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <hero_common/SetOdom.h>
#include <std_srvs/Trigger.h>

#include <ESP8266WiFi.h>

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include "Wire.h"


#include <NeoPixelBus.h>
#include <NeoPixelBrightnessBus.h>
#define colorSaturation 128


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
Encoder l_encoder(10, 5);
double encoder_gain = 0.06; // max 1.0
int l_motor_fix = 0.0;
double l_motor_speed = 0.0;
double l_motor_control = 0.0;
double l_encoder_speed = 0.0;
float kp = 1200, ki = 7.5, kd = 3.5; // default values for pid
PID l_motor_pid(&l_encoder_speed, &l_motor_control, &l_motor_speed, kp, ki, kd, DIRECT); // blue plot
PID_ATune l_aTune(&l_encoder_speed, &l_motor_control);

Servo r_motor;
Encoder r_encoder(4, 14);
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

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
MPU6050 mpu;
// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 gy;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector


const uint16_t PixelCount = 7; // this example assumes 4 pixels, making it smaller will cause a failure
NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(PixelCount);
RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor black(0);

/* Timer */
/* Used to compute Odometry */
unsigned long timer = 0, currentTime, lastTime, log_timer = 0, tunning_steady_state = 0, rate = 50;
double xPos, yPos, theta;
double deltaSteps, deltaTheta;
double leftStepsDiff = 0, rightStepsDiff = 0;
double leftStepsPrev = 0, rightStepsPrev = 0;

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

/* IMU publisher */
sensor_msgs::Imu imu_msg;
/* Frame definitions */
String imu_frame;
void update_imu(void);
String imu_topic;
ros::Publisher *imu_pub;

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

/* Reset odometry hero */
void set_odom_callback(const hero_common::SetOdom::Request& req, hero_common::SetOdom::Response& res);
String set_odom_topic;
ros::ServiceServer<hero_common::SetOdom::Request, hero_common::SetOdom::Response> *set_odom_srv;
/* Calibrate motors hero */
void fix_motors_callback(const std_srvs::Trigger::Request& req, std_srvs::Trigger::Response& res);
String fix_motors_topic;
ros::ServiceServer<std_srvs::Trigger::Request, std_srvs::Trigger::Response> *fix_motors_srv;
/* Autotune pid for motors */
void pid_calibration_callback(const std_srvs::Trigger::Request& req, std_srvs::Trigger::Response& res);
String pid_calibration_topic;
ros::ServiceServer<std_srvs::Trigger::Request, std_srvs::Trigger::Response> *pid_calibration_srv;


char buf [100];

/* Analog Multiplexer 4051 */
const int s0 = 15; // D6 Blue
const int s1 = 13; // D7 Green
const int s2 = 12; // D8 Yellow
const int enable = 2;
const int real_pos[8] = {6,7,5,3,0,1,2,4};

/* Setup */
void setup() {
  /* Connect the ESP8266 the the wifi AP */
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  EEPROM.begin(512);

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

  /* Setup laser publisher */
  hero_name = String("/hero_1");
  laser_topic = hero_name + String("/laser");
  laser_pub = new ros::Publisher(laser_topic.c_str(), &laser_msg);

  /* Setup led subscriber */
  led_topic = hero_name + String("/led");
  led_sub = new ros::Subscriber<std_msgs::ColorRGBA>(led_topic.c_str(), led_callback);

  /* Setup IMU publisher */
  hero_name = String("/hero_1");
  imu_topic = hero_name + String("/imu");
  imu_pub = new ros::Publisher(imu_topic.c_str(), &imu_msg);

  /* Odometry*/
  odom_topic = hero_name + String("/odom");
  odom_pub = new ros::Publisher(odom_topic.c_str(), &odom_msg);

  cmdvel_topic = hero_name + String("/cmd_vel");
  cmdvel_sub = new ros::Subscriber<geometry_msgs::Twist>(cmdvel_topic.c_str(), cmdvel_callback);


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

  nh.advertise(*imu_pub);
  imu_frame = hero_name + String("/imu");
  imu_msg.header.frame_id = imu_frame.c_str();
  imu_msg.header.seq = -1;
  imu_msg.linear_acceleration_covariance[0] = 2.51605824e-03;
  imu_msg.linear_acceleration_covariance[1] = -7.08956399e-04;
  imu_msg.linear_acceleration_covariance[2] = -1.45457923e-04;
  imu_msg.linear_acceleration_covariance[3] = -7.08956399e-04;
  imu_msg.linear_acceleration_covariance[4] = 2.00625688e-03;
  imu_msg.linear_acceleration_covariance[5] = 3.71079569e-05;
  imu_msg.linear_acceleration_covariance[6] = -1.45457923e-04;
  imu_msg.linear_acceleration_covariance[7] = 3.71079569e-05;
  imu_msg.linear_acceleration_covariance[8] = 5.77742340e-05;

  imu_msg.angular_velocity_covariance[0] = 0.61750543;
  imu_msg.angular_velocity_covariance[1] = -0.22783495;
  imu_msg.angular_velocity_covariance[2] = -0.32218393;
  imu_msg.angular_velocity_covariance[3] = -0.22783495;
  imu_msg.angular_velocity_covariance[4] = 1.71576496;
  imu_msg.angular_velocity_covariance[5] = 0.24605797;
  imu_msg.angular_velocity_covariance[6] = -0.32218393;
  imu_msg.angular_velocity_covariance[7] = 0.24605797;
  imu_msg.angular_velocity_covariance[8] = 0.63667265;

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

  /* Address Subscribers */
  nh.subscribe(*led_sub);

/* Service setup */
  set_odom_topic = hero_name + String("/set_odom");
  set_odom_srv = new ros::ServiceServer<hero_common::SetOdom::Request, hero_common::SetOdom::Response>(set_odom_topic.c_str(), &set_odom_callback);
  nh.advertiseService(*set_odom_srv);

  fix_motors_topic = hero_name + String("/fix_motors");
  fix_motors_srv = new ros::ServiceServer<std_srvs::Trigger::Request, std_srvs::Trigger::Response>(fix_motors_topic.c_str(), &fix_motors_callback);
  nh.advertiseService(*fix_motors_srv);

  pid_calibration_topic = hero_name + String("/pid_calibration");
  pid_calibration_srv = new ros::ServiceServer<std_srvs::Trigger::Request, std_srvs::Trigger::Response>(pid_calibration_topic.c_str(), &pid_calibration_callback);
  nh.advertiseService(*pid_calibration_srv);


  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.pins(3, 1); //3 as SDA and 1 as SCL
  Wire.begin(); //3 as SDA and 1 as SCL
  Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
 

  // initialize device
  delay(1);
  mpu.initialize();  

  // verify connection
  //sprintf(buf,"\33[96m %s \33[0m", mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  // load and configure the DMP
  devStatus = mpu.dmpInitialize();

  // supply your own gyro offsets here, scaled for min sensitivity
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
    // turn on the DMP, now that it's ready
    mpu.setDMPEnabled(true);
    // enable Arduino interrupt detection
    mpuIntStatus = mpu.getIntStatus();
    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    dmpReady = true;
    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
    sprintf(buf,"\33[91m %s \33[0m DMP Initialization failed!\33[0m");
    nh.loginfo(buf);
    nh.spinOnce();
  }

  /* Setup Analog Multiplexer Pins */
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(enable, OUTPUT);
  readIR();

  r_motor.attach(0);
  r_motor.writeMicroseconds(1200);

  /* Setup complete esp LED message */
  // this resets all the neopixels to an off state
  strip.Begin();
  strip.Show();
  for(int i = 0; i <= PixelCount; i++){
    strip.SetPixelColor(i, black);
  }
  strip.SetBrightness(64);
  strip.Show();
  
  pinMode(LED_BUILTIN, OUTPUT);
  for(int i = 0; i <= 7; i++){
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    if (laser_msg.ranges[0] > 900)
      strip.SetPixelColor(i, green);
    else
      strip.SetPixelColor(i, red);
  }
  strip.SetBrightness(16);
  strip.Show();

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
  sprintf(buf,"\33[96m Welcome to Hero #1 - IR & IMU Odometry Test! \33[0m");
  nh.loginfo(buf);
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
      readIMU();
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
   
    laser_msg.ranges[real_pos[count]] = analogRead(A0) - env;
    laser_msg.intensities[real_pos[count]] = env;
    
    analogWrite(enable, 0); // turn off all diode and enable mux
  } 
  
  /* Send laser message to be published into ROS */
  laser_msg.header.stamp = nh.now();
  laser_pub->publish( &laser_msg ); 

}


void led_callback(const std_msgs::ColorRGBA& msg){
  strip.Begin();
  RgbColor color(msg.r, msg.g, msg.b);
  for(int i = 0; i <= PixelCount; i++){
    //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    strip.SetPixelColor(i, color);
  }
  strip.SetBrightness(msg.a);
  strip.Show();
}

void readIMU(){
    if (!dmpReady) return;

    // wait for MPU interrupt or extra packet(s) available
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
      // reset so we can continue cleanly
      mpu.resetFIFO();
      //sprintf(buf,"\33[91m %s \33[0m FIFO overflow!\33[0m");
      //nh.loginfo(buf);
      //nh.spinOnce();

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x02) {
      // wait for correct available data length, should be a VERY short wait
      while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
  
      // read a packet from FIFO
      mpu.getFIFOBytes(fifoBuffer, packetSize);
  
      // track FIFO count here in case there is > 1 packet available
      // (this lets us immediately read more without waiting for an interrupt)
      fifoCount -= packetSize;

      // display quaternion values in easy matrix form: w x y z
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
      mpu.dmpGetAccel(&aa, fifoBuffer);
      mpu.dmpGetGyro(&gy, fifoBuffer);
      


      // these methods (and a few others) are also available
      imu_msg.orientation.x = q.x;
      imu_msg.orientation.y = q.y;
      imu_msg.orientation.z = q.z;
      imu_msg.orientation.w = q.w;
      
      imu_msg.angular_velocity.x = gy.x;
      imu_msg.angular_velocity.y = gy.y;
      imu_msg.angular_velocity.z = gy.z;
  
      imu_msg.linear_acceleration.x = aa.x/1000.0;
      imu_msg.linear_acceleration.y = aa.y/1000.0;
      imu_msg.linear_acceleration.z = aa.z/1000.0;
      
      // blink LED to indicate activity
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      /* Send laser message to be published into ROS */
      imu_msg.header.stamp = nh.now();
      imu_pub->publish( &imu_msg ); 
   }
}

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
    l_motor.attach(16);
    r_motor.attach(0);
    halt_motor = false;
    //nh.loginfo("\x1b[1;37;43m[HERO 1] Attach motors!\x1b[0m");
  }
  // Disable tunning if still receiving commands
  tuning = false;
  l_aTune.Cancel();
  r_aTune.Cancel();
}


/* Set odometry initial position */
void set_odom_callback( const hero_common::SetOdom::Request& req, hero_common::SetOdom::Response& res){
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
  l_motor.attach(16);
  r_motor.attach(0);
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




