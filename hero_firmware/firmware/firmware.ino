/*
 ************************************************************************
 *  H E R O   F I R M W A R E
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
#include <ros.h>

/* Message types */
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/Imu.h>
#include <std_msgs/ColorRGBA.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>

/* Service types */
#include <hero_common/SetOdom.h>
#include <hero_common/SetFrequency.h>
#include <std_srvs/Trigger.h>

/* Parameter List */
#include "config.h"

/* ESP Library */
#include <ESP8266WiFi.h>
#include <Servo.h>                      /* https://www.arduino.cc/en/Reference/Servo */
#include <Encoder.h>                    /* https://github.com/PaulStoffregen/Encoder */
#include <PID_v1.h>                     /* http://playground.arduino.cc/Code/PIDLibrary */
#include <PID_AutoTune_v0.h>            /* https://playground.arduino.cc/Code/PIDAutotuneLibrary */
#include <EEPROM.h>                     /* https://www.arduino.cc/en/Reference/EEPROM */
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h" /* https://playground.arduino.cc/Main/MPU-6050 */
#include <NeoPixelBus.h>                /* https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use */
#include <NeoPixelBrightnessBus.h>      
#include "Wire.h" /* Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation */

/* WS2812 LEDs */
const uint16_t PixelCount = 7;
NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(PixelCount);
RgbColor red(COLOR_SATURATION, 0, 0);
RgbColor green(0, COLOR_SATURATION, 0);
RgbColor cyan(0, COLOR_SATURATION, COLOR_SATURATION);
RgbColor magenta(COLOR_SATURATION, 0, COLOR_SATURATION);
RgbColor black(0);


/* Motor Setup */
Servo l_motor;
Servo r_motor; 
boolean halt_motors = false; // utilizar attached() -- trocar depois


/* Encoder Setup */
#define INPUT_PULLUP
#define ENCODER_USE_INTERRUPTS
Encoder l_encoder(ENC_A_LEFT, ENC_B_LEFT);
Encoder r_encoder(ENC_A_RIGHT, ENC_B_RIGHT);


/* Motors Control */
double l_motor_speed = 0.0, l_motor_control = 0.0, l_encoder_speed = 0.0;
PID l_motor_pid(&l_encoder_speed, &l_motor_control, &l_motor_speed, DEFAULT_KP, DEFAULT_KI, DEFAULT_KD, DIRECT); // blue plot
PID_ATune l_aTune(&l_encoder_speed, &l_motor_control);

double r_motor_speed = 0.0, r_motor_control = 0.0, r_encoder_speed = 0.0;
PID r_motor_pid(&r_encoder_speed, &r_motor_control, &r_motor_speed, DEFAULT_KP, DEFAULT_KI, DEFAULT_KD, DIRECT); // red plot
PID_ATune r_aTune(&r_encoder_speed, &r_motor_control);


/* Autotuner Defaults */
double aTuneStep = 20;
double aTuneNoise = 0.001; 
unsigned int aTuneLookBack = 4;
boolean tuning = false;
extern Tuning tuningRule[];
long motorPositionRight = 0, motorPositionLeft = 0;
bool l_done, r_done;


/* Timer Control */
unsigned long timer = 0, currentTime, lastTime, log_timer = 0, tunning_steady_state = 0, rate = 50;


/* IMU I2C address is 0x68 */
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



/* Used to compute Odometry */
double xPos, yPos, theta, thetaYaw = 0;
double deltaSteps, deltaTheta, deltaYaw;
double leftStepsDiff = 0, rightStepsDiff = 0;
double leftStepsPrev = 0, rightStepsPrev = 0;


/* ROS Setup */
String hero_name;
ros::NodeHandle nh; /* ROS Node Instaciatation */

/* Command Velocity Callback */
void cmdvel_callback(const geometry_msgs::Twist& msg);
String cmdvel_topic;
ros::Subscriber<geometry_msgs::Twist> *cmdvel_sub;

/* TF to publish odom to base_link transformation */
tf::TransformBroadcaster broadcaster;
geometry_msgs::TransformStamped t;

/* Odometry Publisher */
nav_msgs::Odometry odom_msg;
nav_msgs::Odometry odom_fix_msg;
String odom_topic;
ros::Publisher *odom_pub;
String odom_fix_topic;
ros::Publisher *odom_fix_pub;

/* Frame definitions */
String base_frame, odom_frame,odom_fix_frame;
void update_odom(void);


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

/* Reset Odometry */
void set_odom_callback(const hero_common::SetOdom::Request& req, hero_common::SetOdom::Response& res);
String set_odom_topic;
ros::ServiceServer<hero_common::SetOdom::Request, hero_common::SetOdom::Response> *set_odom_srv;

/* Set loop-frequency */
void set_frequency_callback(const hero_common::SetFrequency::Request& req, hero_common::SetFrequency::Response& res);
String set_frequency_topic;
ros::ServiceServer<hero_common::SetFrequency::Request, hero_common::SetFrequency::Response> *set_frequency_srv;

/* Calibrate motors hero */
void fix_motors_callback(const std_srvs::Trigger::Request& req, std_srvs::Trigger::Response& res);
String fix_motors_topic;
ros::ServiceServer<std_srvs::Trigger::Request, std_srvs::Trigger::Response> *fix_motors_srv;

/* Autotune pid for motors */
void pid_calibration_callback(const std_srvs::Trigger::Request& req, std_srvs::Trigger::Response& res);
String pid_calibration_topic;
ros::ServiceServer<std_srvs::Trigger::Request, std_srvs::Trigger::Response> *pid_calibration_srv;


char buf [MAX_BUFFER_SIZE];



/* Setup */
void setup() {
  /* Connect the ESP8266 the the wifi AP */
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  EEPROM.begin(512); /* Define EEPROM */

  /* Turn the PID on */
  l_motor_pid.SetOutputLimits(-500, 500);
  l_motor_pid.SetSampleTime(10); /* 10 microseconds */
  l_motor_pid.SetMode(AUTOMATIC);
  
  r_motor_pid.SetOutputLimits(-500, 500);
  r_motor_pid.SetSampleTime(10); /* 10 microseconds */
  r_motor_pid.SetMode(AUTOMATIC);

  /* Setup autotuner for PID */
  l_aTune.SetControlType(PID_ATune::SOME_OVERSHOOT_PID); /* Set control type for autotuner */
  r_aTune.SetControlType(PID_ATune::SOME_OVERSHOOT_PID);

  l_aTune.SetNoiseBand(aTuneNoise); /* The autotune will ignore signal chatter smaller than this value this should be accurately set */
  l_aTune.SetOutputStep(aTuneStep); /* How far above and below the starting value will the output step? */
  l_aTune.SetLookbackSec((int)aTuneLookBack); /* how far back are we looking to identify peaks */
  
  r_aTune.SetNoiseBand(aTuneNoise); /* The autotune will ignore signal chatter smaller than this value this should be accurately set */
  r_aTune.SetOutputStep(aTuneStep); /* How far above and below the starting value will the output step? */
  r_aTune.SetLookbackSec((int)aTuneLookBack); /* How far back are we looking to identify peaks */

  /* Start ROS communication module */
  IPAddress ROS_MASTER_ADDRESS(IP_A, IP_B, IP_C, IP_D); /* Ros Master IP */
  nh.getHardware()->setConnection(ROS_MASTER_ADDRESS, ROS_MASTER_PORT);
  hero_name = String(ROBOT_NAME);

  /* Odometry*/
  odom_topic = hero_name + String("/odom");
  odom_pub = new ros::Publisher(odom_topic.c_str(), &odom_msg);
  odom_fix_topic = hero_name + String("/odom_fix");
  odom_fix_pub = new ros::Publisher(odom_fix_topic.c_str(), &odom_fix_msg);
  
  /* Command Velocity */
  cmdvel_topic = hero_name + String("/cmd_vel");
  cmdvel_sub = new ros::Subscriber<geometry_msgs::Twist>(cmdvel_topic.c_str(), cmdvel_callback);

  
  /* Setup laser publisher */
  laser_topic = hero_name + String("/laser");
  laser_pub = new ros::Publisher(laser_topic.c_str(), &laser_msg);

  /* Setup led subscriber */
  led_topic = hero_name + String("/led");
  led_sub = new ros::Subscriber<std_msgs::ColorRGBA>(led_topic.c_str(), led_callback);

  /* Setup IMU publisher */
  hero_name = String("/hero_1");
  imu_topic = hero_name + String("/imu");
  imu_pub = new ros::Publisher(imu_topic.c_str(), &imu_msg);

  /* Starting ros node */
  nh.initNode();

  /* Address TF */
  broadcaster.init(nh);
  
  /* Address Odometry */
  nh.advertise(*odom_pub);
  nh.advertise(*odom_fix_pub);
  odom_frame = hero_name + String("/odom");
  base_frame  = hero_name + String("/base_link");
  odom_msg.header.frame_id = odom_frame.c_str();
  odom_msg.header.seq = -1;
  odom_msg.child_frame_id = base_frame.c_str();

  odom_fix_frame = hero_name + String("/odom_fix");
  base_frame  = hero_name + String("/base_link");
  odom_fix_msg.header.frame_id = odom_fix_frame.c_str();
  odom_fix_msg.header.seq = -1;
  odom_fix_msg.child_frame_id = base_frame.c_str();

  /* Address Laser */
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
  
  /* Address Command Vel */
  nh.subscribe(*cmdvel_sub);

  /* Address RGBA LEDs */
  nh.subscribe(*led_sub);

  /* Service setup */
  set_odom_topic = hero_name + String("/set_odom");
  set_odom_srv = new ros::ServiceServer<hero_common::SetOdom::Request, hero_common::SetOdom::Response>(set_odom_topic.c_str(), &set_odom_callback);
  nh.advertiseService(*set_odom_srv);

  set_frequency_topic = hero_name + String("/set_frequency");
  set_frequency_srv = new ros::ServiceServer<hero_common::SetFrequency::Request, hero_common::SetFrequency::Response>(set_frequency_topic.c_str(), &set_frequency_callback);
  nh.advertiseService(*set_frequency_srv);

  fix_motors_topic = hero_name + String("/fix_motors");
  fix_motors_srv = new ros::ServiceServer<std_srvs::Trigger::Request, std_srvs::Trigger::Response>(fix_motors_topic.c_str(), &fix_motors_callback);
  nh.advertiseService(*fix_motors_srv);

  pid_calibration_topic = hero_name + String("/pid_calibration");
  pid_calibration_srv = new ros::ServiceServer<std_srvs::Trigger::Request, std_srvs::Trigger::Response>(pid_calibration_topic.c_str(), &pid_calibration_callback);
  nh.advertiseService(*pid_calibration_srv);

  /* Initiate IMU */
  Wire.pins(I2C_SDA, I2C_SCL); //3 as SDA and 1 as SCL
  Wire.begin(); //3 as SDA and 1 as SCL
  Wire.setClock(400000); // 400kHz I2C clock.
  /* Initialize device */
  delay(1);
  mpu.initialize();  
  /* load and configure the DMP */
  devStatus = mpu.dmpInitialize();
  /* supply your own gyro offsets here, scaled for min sensitivity */
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788); // 1688 factory default for my test chip
  /* Make sure it worked (returns 0 if so) */
  if (devStatus == 0) {
    /* turn on the DMP, now that it's ready */
    mpu.setDMPEnabled(true);
    /* enable Arduino interrupt detection */
    mpuIntStatus = mpu.getIntStatus();
    /* set our DMP Ready flag so the main loop() function knows it's okay to use it */
    dmpReady = true;
    /* get expected DMP packet size for later comparison */
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
  pinMode(MUX_A, OUTPUT); 
  pinMode(MUX_B, OUTPUT);
  pinMode(MUX_C, OUTPUT);
  pinMode(MUX_EN, OUTPUT);
  readIR();

  /* Initiate Motors */
  r_motor.attach(MOTOR_RIGHT);
  l_motor.attach(MOTOR_LEFT);
  r_motor.writeMicroseconds(1500);
  l_motor.writeMicroseconds(1500);
  delayMicroseconds(1000);
  r_motor.detach();
  l_motor.detach();

  /* Initiate Encoders */
  l_encoder.write(0);
  r_encoder.write(0);
  leftStepsPrev = l_encoder.read();
  rightStepsPrev = r_encoder.read();

  /* Setup complete esp LED message */
  /* this resets all the neopixels to an off state */
  strip.Begin();
  strip.Show();
  RgbColor color(0, COLOR_SATURATION, COLOR_SATURATION);
  if (laser_msg.ranges[0] > 900){
    color.R = COLOR_SATURATION;
    color.G = 0;
    color.B = COLOR_SATURATION;
  }
  for (int j = 0; j < 30; j++){
    for(int i = 0; i <= PixelCount; i++){
      if (j%2)
        strip.SetPixelColor(i, black);
      else
        strip.SetPixelColor(i, color);
    }
    strip.SetBrightness(64);
    strip.Show();
    delay(100);
  }

  /* ROS LOG */
  sprintf(buf,"\33[96m Founded %s! \33[0m", hero_name.c_str());
  nh.loginfo(buf);
}

/* Main loop */
void loop(){
    /* Autotuner */
    if (tuning){
      if ((millis() - tunning_steady_state) > 10000){ /* 10 seconds to steady state */
        if (!l_done) l_done = l_aTune.Runtime();
        if (!r_done) r_done = r_aTune.Runtime();
        if (l_done && r_done){
          tuning = false; // we're done, set the tuning parameters
          float lkp = l_aTune.GetKp() * 3.2;
          float lki = l_aTune.GetKi() * 0.07;
          float lkd = l_aTune.GetKd() * 0.002;
          if (lkp > 100 && lkp < 2500){ // * Tuning is successed
            l_motor_pid.SetTunings(lkp, lki, lkd);
            l_motor_pid.SetMode(l_motor_pid.GetMode());
            l_aTune.Cancel();
          } else{ // * Tuning is failure
            nh.loginfo("\33[91m Left Motor Tuning Failure! Using default values.\33[0m");
          }
          sprintf(buf,"\33[96m Left Motor Best PID params (%f, %f, %f) \33[0m", lkp, lki, lkd);
          nh.loginfo(buf);
          float rkp = r_aTune.GetKp() * 3.2;
          float rki = r_aTune.GetKi() * 0.07;
          float rkd = r_aTune.GetKd() * 0.002;
          if (rkp > 100 && rkp < 2500){ // * Tuning is successed
            r_motor_pid.SetTunings(rkp, rki, rkd);
            r_motor_pid.SetMode(r_motor_pid.GetMode());
            r_aTune.Cancel();
          } else{ // * Tuning is failure
            nh.loginfo("\33[91m Right Motor Tuning Failure! Using default values. \33[0m");
          }
          sprintf(buf,"\33[96m Right Motor Best PID params: (%f, %f, %f) \33[0m", rkp, rki, rkd);
            nh.loginfo(buf);
        }
      }
        l_motor.writeMicroseconds((int)l_motor_control + 1500);
        r_motor.writeMicroseconds((int)-r_motor_control + 1500);
    }
    else{
      /* PID control loop */
      if (r_motor.attached() & l_motor.attached()) control(); 
    }
    
    /* Update motor position */
    motorPositionRight = r_encoder.read();
    motorPositionLeft = l_encoder.read();
  
    /* ROS INFOS */
    if ((millis() - log_timer) > 3000){
      log_timer = millis();
      if (tuning)
        sprintf(buf,"\33[96m[%s] Tuning PID! Please wait (200 seconds)... %d ms\33[0m", hero_name.c_str(), (millis()-tunning_steady_state)/1000);
      else
        sprintf(buf,"\33[96m[%s] Conected at time %d\33[0m", hero_name.c_str(), millis());
      nh.loginfo(buf);
    }

    /* ROS Loop */
    if (millis() - timer > rate){ 
      timer = millis();
      readIR();
      readIMU();
      update_odom();
      nh.spinOnce();
    }  
}


/* PID Control loop for wheel speed */
void control(void){
  /* Update control loop and set the output to the motors */
  l_motor_pid.Compute();
  r_motor_pid.Compute();
  l_motor.writeMicroseconds((int)l_motor_control + 1500);
  r_motor.writeMicroseconds((int)(-r_motor_control) + 1500);
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
      //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      /* Send laser message to be published into ROS */
      imu_msg.header.stamp = nh.now();
      imu_pub->publish( &imu_msg ); 
   }
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
  l_encoder_speed = ((1.0 - ENCODER_SPEED_GAIN) * l_encoder_speed + ENCODER_SPEED_GAIN * (double) leftdist / ((double)(currentTime-lastTime)/1000000.0));
  l_encoder_speed *= 5/3;
  r_encoder_speed = ((1.0 - ENCODER_SPEED_GAIN) * r_encoder_speed + ENCODER_SPEED_GAIN * (double) rightdist / ((double)(currentTime-lastTime)/1000000.0));
  r_encoder_speed *= 5/3;

  odom_msg.twist.twist.linear.y = l_encoder_speed;
  odom_msg.twist.twist.linear.z = r_encoder_speed;
  
  odom_msg.twist.twist.angular.x = (double) leftdist / ((double)(currentTime-lastTime)/1000000.0);
  odom_msg.twist.twist.angular.y = (double) rightdist / ((double)(currentTime-lastTime)/1000000.0);

  odom_msg.twist.twist.angular.x = motorPositionLeft;
  odom_msg.twist.twist.angular.y = motorPositionRight;
  
  lastTime = micros();

  /* Compute Odometry */
  deltaTheta =  (rightdist - leftdist) / WHEEL_DISTANCE; /* Expressed in radiant. */ 
  deltaSteps = (rightdist + leftdist) / (2.0); /* meter pes seconds */ 
  xPos += deltaSteps * cos(theta + deltaTheta/2.0);
  yPos += deltaSteps * sin(theta + deltaTheta/2.0);

  /* Fusing Odometry */
  deltaYaw = ypr[0] - thetaYaw;
  thetaYaw = ypr[0];
  odom_fix_msg.pose.pose.position.x += deltaSteps * cos(thetaYaw + deltaYaw/2.0);
  odom_fix_msg.pose.pose.position.y += deltaSteps * sin(thetaYaw + deltaYaw/2.0);
  odom_fix_msg.pose.pose.position.z = thetaYaw;
   
    
  theta += deltaTheta; /* Expressed in radiant. */ 
  if (theta > M_PI) theta = theta - 2.0 * M_PI;
  if (theta < -M_PI) theta = theta + 2.0 * M_PI;

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

  odom_fix_msg.header.stamp = nh.now();
  odom_fix_msg.header.seq++;
  odom_fix_pub->publish( &odom_fix_msg );
  
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
    //nh.loginfo("\x1b[1;37;43m[HERO 1] Detach motors!\x1b[0m");
  }else{
    r_motor.attach(MOTOR_RIGHT);
    l_motor.attach(MOTOR_LEFT);
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

/* Set loop-frequency */
void set_frequency_callback( const hero_common::SetFrequency::Request& req, hero_common::SetFrequency::Response& res){
  rate = 1000/req.frequency;
  res.success = 1;
  res.message = "Odometry was changed!";
  sprintf(buf,"\33[96m[%s] Changing loop-frequency to %f Hz \33[0m", hero_name.c_str(), req.frequency);
  nh.loginfo(buf);
}


/* Fix motors halt position */
void fix_motors_callback(const std_srvs::Trigger::Request& req, std_srvs::Trigger::Response& res){
  EEPROM.begin(512);
  /*if (fabs(l_encoder_speed) <= 0.0001 && fabs(r_encoder_speed) <= 0.0001){
    l_motor_fix = l_motor.readMicroseconds();
    EEPROM.write(0, uint8_t(1500-l_motor.readMicroseconds()));
    r_motor_fix = r_motor.readMicroseconds();
    EEPROM.write(1, uint8_t(1500-r_motor.readMicroseconds()));
    EEPROM.commit();
  }
  sprintf(buf,"Left Motor Halt Position: %d, Right Motor Halt Position: %d", EEPROM.read(0), EEPROM.read(1));
  nh.loginfo(buf);
  res.success = 1;
  res.message = "Motors are calibrated!";*/
  EEPROM.end();
}


/* Autotune PID Motors */
void pid_calibration_callback(const std_srvs::Trigger::Request& req, std_srvs::Trigger::Response& res){
  sprintf(buf,"\33[96m[%s] Starting Motors Auto Tuning! Wait... \33[0m", hero_name.c_str());
  nh.loginfo(buf);
  r_motor.attach(MOTOR_RIGHT);
  l_motor.attach(MOTOR_LEFT);
  tuning = false;
  l_aTune.Cancel();
  r_aTune.Cancel();
  
  l_motor_control = 30; // this should be outputStart in Autotune
  r_motor_control = -30; // this should be outputStart in Autotune
  l_done = false;
  r_done = false;
  tunning_steady_state = millis();
  tuning = true;
  res.message = "PID Autotuning!";
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


void readIR(){
  for (int count = 0; count <= 7; count++) {
    /* select the input  */
    int r0 = count & 0x01;
    int r1 = (count>>1) & 0x01;
    int r2 = (count>>2) & 0x01;
    digitalWrite(MUX_A, r0);
    digitalWrite(MUX_B, r1);
    digitalWrite(MUX_C, r2);
    /* Receptor precisa descansar para pois o todos os emissores são ligados juntos 
      1. Ler A0 sensor light
      2. Emite todos emisores e espera 100 us
      3. Ler A0 sensor proximity
      4. Espera até A1 desaturar e repete para A1 {até A7}
      OBS. Parece que os Emisor mais escuro se recupera mais rapido da saturação
    */
    delayMicroseconds(500);  // diode should power up in 100 us
    float env = analogRead(A0);
    analogWrite(MUX_EN, 1024); // turn on all diode and enable mux
    delayMicroseconds(100);  // diode should power up in 100 us -> 180 us
   
    laser_msg.ranges[real_pos[count]] = analogRead(A0) - env;
    laser_msg.intensities[real_pos[count]] = env;
    
    analogWrite(MUX_EN, 0); // turn off all diode and enable mux
  } 
  
  /* Send laser message to be published into ROS */
  laser_msg.header.stamp = nh.now();
  laser_pub->publish( &laser_msg ); 

}








