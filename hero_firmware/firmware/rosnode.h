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

#ifndef __ROSNODE_H__
#define __ROSNODE_H__

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
#include <hero_common/SetPID.h>
#include <hero_common/Encoder.h>
#include <hero_common/Motor.h>
#include <std_srvs/Trigger.h>

/** ROS Setup **/
String hero_name;
ros::NodeHandle nh; /* ROS Node Instantiation */

/** TF to publish transformation **/
tf::TransformBroadcaster broadcaster;
geometry_msgs::TransformStamped t;

/** Subscribers **/
/* Command Velocity Callback */
String cmdvel_topic;                                    /* Topic name */
ros::Subscriber<geometry_msgs::Twist> *cmdvel_sub;      /* Message type */
void cmdvel_callback(const geometry_msgs::Twist& msg);  /* Callback function */

#if MOTOR_PWM_SUBSCRIBER_ENABLE == true
  /* Motor PWM Callback */
  String motor_topic;                                     /* Topic name */
  ros::Subscriber<hero_common::Motor> *motor_sub;         /* Message type */
  void motor_callback(const hero_common::Motor& msg);     /* Callback function */
  bool pwm_only = false;
#endif

/* LED callback */
String led_topic;                                     /* Topic name */
ros::Subscriber<std_msgs::ColorRGBA> *led_sub;        /* Message type */
void led_callback(const std_msgs::ColorRGBA& msg);    /* Callback function */

/** Publishers **/
/* Odometry publisher */
nav_msgs::Odometry odom_msg;  /* Message Type */
String odom_topic;            /* Topic name */
ros::Publisher *odom_pub;     /* Publisher */
void update_odom(void);       /* Update Loop */
String base_frame;            /* Base link frame */
String odom_frame;            /* Odom link frame */

/* Laser publisher */
sensor_msgs::LaserScan laser_msg;   /* Message Type */
String laser_topic;                 /* Topic name */
ros::Publisher *laser_pub;          /* Publisher */
void update_laser(void);            /* Update Loop */
String laser_frame;                 /* Laser link frame */


/* Encoder publisher */
hero_common::Encoder encoder_msg;     /* Message Type */
String encoder_topic;                 /* Topic name */
ros::Publisher *encoder_pub;          /* Publisher */
void update_encoder(void);            /* Update Loop */
String encoder_frame;                 /* Encoder link frame */

#if IMU_ENABLE == true
  /* IMU publisher */
  sensor_msgs::Imu imu_msg;  /* Message Type */
  String imu_topic;          /* Topic name */
  ros::Publisher *imu_pub;   /* Publisher */
  void update_imu(void);     /* Update Loop */
  String imu_frame;          /* Laser link frame */
#endif

/** Services **/
/* Reset Odometry */
ros::ServiceServer<hero_common::SetOdom::Request, hero_common::SetOdom::Response> *set_odom_srv;        /* Service Type */
String set_odom_topic;                                                                                  /* Service name */
void set_odom_callback(const hero_common::SetOdom::Request& req, hero_common::SetOdom::Response& res);  /* Callback function */

/* Set loop-frequency */
ros::ServiceServer<hero_common::SetFrequency::Request, hero_common::SetFrequency::Response> *set_frequency_srv;         /* Service Type */
String set_frequency_topic;                                                                                             /* Service name */
void set_frequency_callback(const hero_common::SetFrequency::Request& req, hero_common::SetFrequency::Response& res);   /* Callback function */

/* Set PID parameters on both motors */
ros::ServiceServer<hero_common::SetPID::Request, hero_common::SetPID::Response> *set_pid_srv;          /* Service Type */
String set_pid_topic;                                                                                  /* Service name */
void set_pid_callback(const hero_common::SetPID::Request& req, hero_common::SetPID::Response& res);    /* Callback function */

/* Autotune pid for motors */
ros::ServiceServer<std_srvs::Trigger::Request, std_srvs::Trigger::Response> *pid_calibration_srv;         /* Service Type */
String pid_calibration_topic;                                                                             /* Service name */
void pid_calibration_callback(const std_srvs::Trigger::Request& req, std_srvs::Trigger::Response& res);   /* Callback function */

/* Compute Odometry */
double deltaSteps, deltaTheta, deltaYaw;
double leftStepsDiff = 0, rightStepsDiff = 0;
double leftStepsPrev = 0, rightStepsPrev = 0;

unsigned long ros_debug_timer = 0; /* Debug timer */
unsigned long debug_rate = DEBUG_RATE;
unsigned long currentTime = 0; /* Odometry compute loop */
unsigned long lastTime = 0;


/* Setup ROS Communication */
void setup_ros(){
  /* Start ROS communication module */
  IPAddress ROS_MASTER_ADDRESS; /* Ros Master IP */
  if (default_config){
    ROS_MASTER_ADDRESS.fromString(ROS_MASTER_IP);
  } else{
    ROS_MASTER_ADDRESS.fromString(configurationData.ros_master_address);
  }
  nh.getHardware()->setConnection(ROS_MASTER_ADDRESS, ROS_MASTER_PORT);

  /* Starting ros node */
  nh.initNode();

  /* Updating Robot name */
  if (default_config){
    hero_name = String(ROBOT_NAME) + String(ROBOT_ID);
  } else {
    hero_name = String(ROBOT_NAME) + String(configurationData.robot_id);
  }

   /* Address TF */
  broadcaster.init(nh);

  /* Address command velocity subscribe */
  cmdvel_topic = hero_name + String("/cmd_vel");                                                     /* Update topic name */
  cmdvel_sub = new ros::Subscriber<geometry_msgs::Twist>(cmdvel_topic.c_str(), cmdvel_callback);     /* Instantiate subscriber */
  nh.subscribe(*cmdvel_sub);                                                                         /* Address Command Vel */

  #if MOTOR_PWM_SUBSCRIBER_ENABLE == true
    /* Address motor pwm subscribe */
    motor_topic = hero_name + String("/motor");                                                      /* Update topic name */
    motor_sub = new ros::Subscriber<hero_common::Motor>(motor_topic.c_str(), motor_callback);        /* Instantiate subscriber */
    nh.subscribe(*motor_sub);                                                                        /* Address Command Vel */
  #endif

  /* Address led subscriber */
  led_topic = hero_name + String("/led");                                                 /* Update topic name */
  led_sub = new ros::Subscriber<std_msgs::ColorRGBA>(led_topic.c_str(), led_callback);    /* Instantiate subscriber */
  nh.subscribe(*led_sub);                                                                 /* Address RGBA LEDs */
  
  /* Address odometry publisher */
  odom_topic = hero_name + String("/odom");                       /* Update topic name */
  odom_pub = new ros::Publisher(odom_topic.c_str(), &odom_msg);   /* Instantiate publisher */
  odom_frame = hero_name + String("/odom");                       /* Update frame name */
  base_frame  = hero_name + String("/base_link");                 /* Update frame name */
  odom_msg.header.frame_id = odom_frame.c_str();                  /* Set frame name */
  odom_msg.header.seq = -1;                                       /* Start message sequency */
  odom_msg.child_frame_id = base_frame.c_str();                   /* Update frame name */
  nh.advertise(*odom_pub);                                        /* Address Odometry */
  
  /* Address laser publisher */
  laser_topic = hero_name + String("/laser");                         /* Update topic name */
  laser_pub = new ros::Publisher(laser_topic.c_str(), &laser_msg);    /* Instantiate publisher */
  laser_frame = hero_name + String("/laser");                         /* Update frame name */
  laser_msg.header.frame_id = laser_frame.c_str();                    /* Set frame name */
  laser_msg.header.seq = -1;                                          /* Start message sequency */
  laser_msg.range_min = 0.0;                                          /* Min laser range */
  laser_msg.range_max = 1024.0;                                       /* Max laser range */
  laser_msg.angle_min = 0.0;                                          /* Initial angle */
  laser_msg.angle_max = 2 * M_PI;                                     /* Final angle */
  laser_msg.angle_increment = 0.79;                                   /* Angle increment */
  laser_msg.ranges_length = 8;                                        /* Samples; 8 proximity sensors */
  laser_msg.ranges = (float *)malloc(8 * sizeof(float));              /* Instantiate ranges vector */
  laser_msg.intensities_length = 8;                                   /* Samples; 8 proximity sensors */
  laser_msg.intensities = (float *)malloc(8 * sizeof(float));         /* Instantiate intensities vector */
  nh.advertise(*laser_pub);                                           /* Address Laser */

  /* Address encoder publisher */
  encoder_topic = hero_name + String("/encoder");                         /* Update topic name */
  encoder_pub = new ros::Publisher(encoder_topic.c_str(), &encoder_msg);    /* Instantiate publisher */
  encoder_frame = hero_name + String("/encoder");                         /* Update frame name */
  encoder_msg.header.frame_id = encoder_frame.c_str();                    /* Set frame name */
  encoder_msg.header.seq = -1;                                          /* Start message sequency */
  nh.advertise(*encoder_pub);                                           /* Address Laser */

  #if IMU_ENABLE == true
    /* Address IMU publisher */
    imu_topic = hero_name + String("/imu");                       /* Update topic name */
    imu_pub = new ros::Publisher(imu_topic.c_str(), &imu_msg);    /* Instantiate publisher */
    imu_frame = hero_name + String("/imu");                       /* Update frame name */
    imu_msg.header.frame_id = imu_frame.c_str();                  /* Set frame name */
    imu_msg.header.seq = -1;                                      /* Start message sequency */
    imu_msg.linear_acceleration_covariance[0] = 2.51605824e-03;   /* Accelerometer Covariance */
    imu_msg.linear_acceleration_covariance[1] = -7.08956399e-04;
    imu_msg.linear_acceleration_covariance[2] = -1.45457923e-04;
    imu_msg.linear_acceleration_covariance[3] = -7.08956399e-04;
    imu_msg.linear_acceleration_covariance[4] = 2.00625688e-03;
    imu_msg.linear_acceleration_covariance[5] = 3.71079569e-05;
    imu_msg.linear_acceleration_covariance[6] = -1.45457923e-04;
    imu_msg.linear_acceleration_covariance[7] = 3.71079569e-05;
    imu_msg.linear_acceleration_covariance[8] = 5.77742340e-05;
    imu_msg.angular_velocity_covariance[0] = 0.61750543;          /* Gyro Covariance */
    imu_msg.angular_velocity_covariance[1] = -0.22783495;
    imu_msg.angular_velocity_covariance[2] = -0.32218393;
    imu_msg.angular_velocity_covariance[3] = -0.22783495;
    imu_msg.angular_velocity_covariance[4] = 1.71576496;
    imu_msg.angular_velocity_covariance[5] = 0.24605797;
    imu_msg.angular_velocity_covariance[6] = -0.32218393;
    imu_msg.angular_velocity_covariance[7] = 0.24605797;
    imu_msg.angular_velocity_covariance[8] = 0.63667265; 
    nh.advertise(*imu_pub);                                       /* Address IMU */
  #endif
  
  /* Address set odom service */
  set_odom_topic = hero_name + String("/set_odom");                                                                                                    /* Update service name */
  set_odom_srv = new ros::ServiceServer<hero_common::SetOdom::Request, hero_common::SetOdom::Response>(set_odom_topic.c_str(), &set_odom_callback);    /* Instantiate service */
  nh.advertiseService(*set_odom_srv);                                                                                                                  /* Address set odom service */

  /* Address set frequency service */
  set_frequency_topic = hero_name + String("/set_frequency");                                                                                                                 /* Update service name */
  set_frequency_srv = new ros::ServiceServer<hero_common::SetFrequency::Request, hero_common::SetFrequency::Response>(set_frequency_topic.c_str(), &set_frequency_callback);  /* Instantiate service */
  nh.advertiseService(*set_frequency_srv);                                                                                                                                    /* Address set frequency service */

  /* Address set PID motors service */
  set_pid_topic = hero_name + String("/set_pid_parameters");                                                                                                 /* Update service name */
  set_pid_srv = new ros::ServiceServer<hero_common::SetPID::Request, hero_common::SetPID::Response>(set_pid_topic.c_str(), &set_pid_callback);               /* Instantiate service */
  nh.advertiseService(*set_pid_srv);                                                                                                                          /* Address fix motors service */

  /* Address PID calibration service */
  pid_calibration_topic = hero_name + String("/pid_calibration");                                                                                                     /* Update service name */
  pid_calibration_srv = new ros::ServiceServer<std_srvs::Trigger::Request, std_srvs::Trigger::Response>(pid_calibration_topic.c_str(), &pid_calibration_callback);    /* Instantiate service */
  nh.advertiseService(*pid_calibration_srv);                                                                                                                          /* Address PID calibration service */ 
}


/** Callbacks **/

/* Read IMU data and publish it*/
void readIMU(){
    if (!dmpReady) return;

    /* wait for MPU interrupt or extra packet(s) available */
    mpuIntStatus = mpu.getIntStatus();

    /* get current FIFO count */
    fifoCount = mpu.getFIFOCount();

    /* check for overflow (this should never happen unless our code is too inefficient) */
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
      /* reset so we can continue cleanly */
      mpu.resetFIFO();
    /* otherwise, check for DMP data ready interrupt (this should happen frequently) */
    } else if (mpuIntStatus & 0x02) {
      /* wait for correct available data length, should be a VERY short wait */
      while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
  
      /* read a packet from FIFO */
      mpu.getFIFOBytes(fifoBuffer, packetSize);
  
      /* track FIFO count here in case there is > 1 packet available   
       (this lets us immediately read more without waiting for an interrupt) */
      fifoCount -= packetSize;

      /* Display quaternion values in easy matrix form: w x y z */
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
      mpu.dmpGetAccel(&aa, fifoBuffer);
      mpu.dmpGetGyro(&gy, fifoBuffer);

      /* These methods (and a few others) are also available */
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
      
      /* blink LED to indicate activity */
      //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      /* Send laser message to be published into ROS */
      imu_msg.header.stamp = nh.now();
      imu_pub->publish( &imu_msg ); 
   }
}


/* Update and publish encoder data */
void update_encoder(void){
  /* Update motor position */
  encoder_msg.right_ticks = r_encoder.read();
  encoder_msg.left_ticks = l_encoder.read();
  currentTime = micros();

  /* Compute the difference of ticks */
  encoder_msg.left_diff  = encoder_msg.left_ticks - leftStepsPrev; // Expressed in tickes.
  encoder_msg.right_diff = encoder_msg.right_ticks - rightStepsPrev;   // Expressed in tickes.

  /* Update last encoder ticks*/
  leftStepsPrev = encoder_msg.left_ticks; 
  rightStepsPrev = encoder_msg.right_ticks;

  /* Transform ticks to distance in meters */
  encoder_msg.left_dist = MOT_STEP_DIST * encoder_msg.left_diff * ENCODER_MOTOR_TRANSMISSION;
  encoder_msg.right_dist = MOT_STEP_DIST * encoder_msg.right_diff * ENCODER_MOTOR_TRANSMISSION;
  
  /* Get encoder speed in m/s */
  /* low-pass filter */
  encoder_msg.timestep = ((double)(currentTime-lastTime)/1000000.0);
  encoder_msg.left_speed  = (double) encoder_msg.left_dist / encoder_msg.timestep;
  encoder_msg.right_speed = (double) encoder_msg.right_dist / encoder_msg.timestep;
  //if (abs(encoder_msg.left_speed_filtered - l_motor_speed) >= 0.05){
  //  encoder_msg.left_speed_filtered = (1.0 - ENCODER_SPEED_GAIN_AGGRESSIVE) * encoder_msg.left_speed_filtered + ENCODER_SPEED_GAIN_AGGRESSIVE * encoder_msg.left_speed;
  //} else {
    encoder_msg.left_speed_filtered = (1.0 - ENCODER_SPEED_GAIN) * encoder_msg.left_speed_filtered + ENCODER_SPEED_GAIN * encoder_msg.left_speed;
  //}
  //if (abs(encoder_msg.right_speed_filtered - r_motor_speed) >= 0.05){
//    encoder_msg.right_speed_filtered = (1.0 - ENCODER_SPEED_GAIN_AGGRESSIVE) * encoder_msg.right_speed_filtered + ENCODER_SPEED_GAIN_AGGRESSIVE * encoder_msg.right_speed;
  //} else {
    encoder_msg.right_speed_filtered = (1.0 - ENCODER_SPEED_GAIN) * encoder_msg.right_speed_filtered + ENCODER_SPEED_GAIN * encoder_msg.right_speed;
  //}
  l_encoder_speed = encoder_msg.left_speed_filtered; /*Used on PID loop control */
  r_encoder_speed = encoder_msg.right_speed_filtered;
  lastTime = currentTime;

  encoder_msg.header.stamp = nh.now();
  encoder_pub->publish( &encoder_msg );
}


/* Update and publish odom data */
void update_odom(void){
  /* Compute Odometry */
  deltaTheta =  (encoder_msg.right_dist - encoder_msg.left_dist) / WHEEL_DISTANCE; /* Expressed in radiant. */ 
  deltaSteps = (encoder_msg.right_dist + encoder_msg.left_dist) / (2.0); /* meter pes seconds */ 
  odom_msg.pose.pose.position.x += deltaSteps * cos(odom_msg.pose.pose.position.z + deltaTheta/2.0);
  odom_msg.pose.pose.position.y += deltaSteps * sin(odom_msg.pose.pose.position.z + deltaTheta/2.0);
    
  odom_msg.pose.pose.position.z += deltaTheta; /* Expressed in radiant. */ 
  if (odom_msg.pose.pose.position.z > M_PI) odom_msg.pose.pose.position.z = odom_msg.pose.pose.position.z - 2.0 * M_PI;
  if (odom_msg.pose.pose.position.z < -M_PI) odom_msg.pose.pose.position.z = odom_msg.pose.pose.position.z + 2.0 * M_PI;
  
  /* Since all odometry is 6DOF we'll need a quaternion created from yaw. */
  odom_msg.pose.pose.orientation = tf::createQuaternionFromYaw(odom_msg.pose.pose.position.z);

  /* Robot linear speed in m/s */
  odom_msg.twist.twist.linear.x = (encoder_msg.right_speed_filtered + encoder_msg.left_speed_filtered)/2.0;   
  /* Wheel speed in m/s */
  
  /* Robot angular speed in rad/s */                                                                                      
  odom_msg.twist.twist.angular.z = (encoder_msg.right_speed_filtered - encoder_msg.left_speed_filtered)/ WHEEL_DISTANCE;  
  odom_msg.twist.twist.angular.x = (double)l_motor_control + (double)MOTOR_LEFT_HALT_PWM;
  odom_msg.twist.twist.angular.y = (double)(-r_motor_control) + (double)MOTOR_RIGHT_HALT_PWM;

  /* publish odometry */
  odom_msg.header.stamp = nh.now();
  odom_msg.header.seq++;
  odom_pub->publish( &odom_msg );
  
  /* tf odom->base_link */
  t.header.frame_id = odom_frame.c_str();
  t.child_frame_id = base_frame.c_str();
  t.transform.translation.x = odom_msg.pose.pose.position.x;
  t.transform.translation.y = odom_msg.pose.pose.position.y;
  t.transform.translation.z = 0;
  t.transform.rotation = tf::createQuaternionFromYaw(odom_msg.pose.pose.position.z);
  t.header.stamp = nh.now();
  broadcaster.sendTransform(t);
 }


/* Compute inverse kinematic of a Differential Drive Robot */
void cmdvel_callback(const geometry_msgs::Twist& msg){
  /* Get robot velocities */
  float linear = max(min((double)msg.linear.x, MAX_LINEAR_VEL), -MAX_LINEAR_VEL); // max linear speed 0.25 m/s
  float angular = max(min((double)msg.angular.z, MAX_ANGULAR_VEL), -MAX_ANGULAR_VEL); // max angular speed 0.08 rad/s
  
  /* Inverse Kinematic of a Differential Drive Robot */
  l_motor_speed = (double)(2.0 * linear - WHEEL_SEPARATION * angular) / 2.0;
  r_motor_speed = (double)(2.0 * linear + WHEEL_SEPARATION * angular) / 2.0;

  if (linear == 0.0 && angular == 0.0){ /* Robot is not moving, so disable motor to safe battery */
    l_motor.detach();
    r_motor.detach();
    l_motor_control = 0;
    r_motor_control = 0;
    encoder_msg.left_speed_filtered = 0.0;
    encoder_msg.right_speed_filtered = 0.0;
  }else{
    r_motor.attach(MOTOR_RIGHT);
    l_motor.attach(MOTOR_LEFT);
  }
  /* Disable tunning if still receiving commands */
  tuning = false;
  l_aTune.Cancel();
  r_aTune.Cancel();
  pwm_only = false;
}


/* Set motor pwm */
void motor_callback(const hero_common::Motor& msg){
  r_motor.attach(MOTOR_RIGHT);
  l_motor.attach(MOTOR_LEFT);
  l_motor.writeMicroseconds(msg.left_motor_pwm);
  r_motor.writeMicroseconds(msg.right_motor_pwm);
  pwm_only = true;
}


/* Set odometry initial position */
void set_odom_callback( const hero_common::SetOdom::Request& req, hero_common::SetOdom::Response& res){
  l_encoder.write(0);
  r_encoder.write(0);

  leftStepsPrev = l_encoder.read();
  rightStepsPrev = r_encoder.read();
  
  odom_msg.pose.pose.position.x = req.x;
  odom_msg.pose.pose.position.y = req.y;
  odom_msg.pose.pose.position.z = req.theta;
  odom_msg.pose.pose.orientation = tf::createQuaternionFromYaw(req.theta);
  res.success = 1;
  res.message = "Odometry was changed!";
  nh.loginfo("[HERO] Odometry was changed!");
}

/* Set loop-frequency */
void set_frequency_callback( const hero_common::SetFrequency::Request& req, hero_common::SetFrequency::Response& res){
  loop_rate = req.frequency;
  res.success = 1;
  res.message = "\33[96m Changing loop-frequency. \33[0m";
  sprintf(buf,"\33[96m[%s] Changing loop-frequency to %f Hz \33[0m", hero_name.c_str(), req.frequency);
  nh.loginfo(buf);
}


/* Set PID parameters for both motors */
void set_pid_callback(const hero_common::SetPID::Request& req, hero_common::SetPID::Response& res){
  configurationPID.rkp = req.rkp;
  configurationPID.rkd = req.rki;
  configurationPID.rki = req.rkd;
  configurationPID.lkp = req.lkp;
  configurationPID.lki = req.lki;
  configurationPID.lkd = req.lkd;

  l_motor_pid.SetTunings(configurationPID.lkp, configurationPID.lki, configurationPID.lkd);
  r_motor_pid.SetTunings(configurationPID.rkp, configurationPID.rki, configurationPID.rkd);
  
  sprintf(buf,"\33[96m[%s] Recording values in the flash... \33[0m", hero_name.c_str());
  nh.loginfo(buf);
  
  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.put(MEM_INIT_POS_PID, configurationPID);
  EEPROM.end();
  
  sprintf(buf,"\33[96m[%s] PID Parameters has been succesfully recorded! \33[0m", hero_name.c_str());
  nh.loginfo(buf);
  res.success = 1;
  res.message = "PID Parameters has been succesfully recorded!";
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
  
  l_motor_control = TUNE_STEADY_STATE; // this should be outputStart in Autotune
  r_motor_control = -TUNE_STEADY_STATE; // this should be outputStart in Autotune
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
    /* Select the input  */
    int r0 = count & 0x01;
    int r1 = (count>>1) & 0x01;
    int r2 = (count>>2) & 0x01;
    digitalWrite(MUX_A, r0);
    digitalWrite(MUX_B, r1);
    digitalWrite(MUX_C, r2);
    /* Photodiode needs sleep for while since all the emissors are turned on at same time
      1. Read A0 sensor light
      2. Turn on the emissors and wait 100 us
      3. Read A0 sensor proximity
      4. Wait until A1 Espera até A1 desaturate and repeat for A1 {until A7}
      PS. It seems that the darker emissors recover faster than the light ones during over the saturation
    */
    delayMicroseconds(500);  // diode should power up in 100 us
    float env = analogRead(A0);
    analogWrite(MUX_EN, 1024); // turn on all diode and enable mux
    delayMicroseconds(100);  // diode should power up in 100 us -> 180 us
   
    laser_msg.ranges[real_pos[count]] = analogRead(A0) - env;
    laser_msg.intensities[real_pos[count]] = env;
    
    analogWrite(MUX_EN, 0); /* Turn off all diode and enable mux */
  } 
}

void update_laser(){
  readIR();
   /* Send laser message to be published into ROS */
  laser_msg.header.stamp = nh.now();
  laser_pub->publish( &laser_msg ); 
}

void tune_motors(){
  if ((millis() - tunning_steady_state) > TUNE_STEADY_STATE_TIME){ /* 10 seconds to steady state */
        if (!l_done) l_done = l_aTune.Runtime();
        if (!r_done) r_done = r_aTune.Runtime();
        if (l_done && r_done){
          tuning = false; /* We're done, set the tuning parameters */
          float lkp = l_aTune.GetKp() * SOME_OVERSHOOT_RULE_P;
          float lki = l_aTune.GetKi() * SOME_OVERSHOOT_RULE_I;
          float lkd = l_aTune.GetKd() * SOME_OVERSHOOT_RULE_D;
          if (lkp > TUNING_SUCCESSED_THRESHOLD_MIN && lkp < TUNING_SUCCESSED_THRESHOLD_MAX){ // * Tuning is successed
            l_motor_pid.SetTunings(lkp, lki, lkd);
            l_motor_pid.SetMode(l_motor_pid.GetMode());
            l_aTune.Cancel();
          } else { // * Tuning is failure
            nh.loginfo("\33[91m Left Motor Tuning Failure! Using default values.\33[0m");
          }
          sprintf(buf,"\33[96m Left Motor Best PID params (%f, %f, %f) \33[0m", lkp, lki, lkd);
          nh.loginfo(buf);
          float rkp = r_aTune.GetKp() * SOME_OVERSHOOT_RULE_P;
          float rki = r_aTune.GetKi() * SOME_OVERSHOOT_RULE_I;
          float rkd = r_aTune.GetKd() * SOME_OVERSHOOT_RULE_D;
          if (rkp > TUNING_SUCCESSED_THRESHOLD_MIN && rkp < TUNING_SUCCESSED_THRESHOLD_MAX){ // * Tuning is successed
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
        l_motor.writeMicroseconds((int)l_motor_control + (int)MOTOR_LEFT_HALT_PWM);
        r_motor.writeMicroseconds((int)-r_motor_control + (int)MOTOR_RIGHT_HALT_PWM);
}

bool is_config_mode(){
  for (int count = 0; count <= 7; count++) {
    /* Select the input  */
    int r0 = count & 0x01;
    int r1 = (count>>1) & 0x01;
    int r2 = (count>>2) & 0x01;
    digitalWrite(MUX_A, r0);
    digitalWrite(MUX_B, r1);
    digitalWrite(MUX_C, r2);
    /* Photodiode needs sleep for while since all the emissors are turned on at same time
      1. Read A0 sensor light
      2. Turn on the emissors and wait 100 us
      3. Read A0 sensor proximity
      4. Wait until A1 Espera até A1 desaturate and repeat for A1 {until A7}
      PS. It seems that the darker emissors recover faster than the light ones during over the saturation
    */
    delayMicroseconds(500);  // diode should power up in 100 us
    float env = analogRead(A0);
    analogWrite(MUX_EN, 1024); // turn on all diode and enable mux
    delayMicroseconds(100);  // diode should power up in 100 us -> 180 us
   
    if (analogRead(A0) - env < TOUCH_THRESHOLD) 
      return false;
    
    analogWrite(MUX_EN, 0); /* Turn off all diode and enable mux */
  } 
  return true;
}
  
#endif  // ___CONFIG_H__







