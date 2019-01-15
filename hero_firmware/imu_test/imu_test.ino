 /************************************************************************
 *  H E R O   I R   I M U
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
#include <sensor_msgs/Imu.h>

#include <ESP8266WiFi.h>

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
//#include "MPU6050.h" // not necessary if using MotionApps include file

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 mpu;
//MPU6050 mpu(0x69); // <-- use for AD0 high

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

#define LED_PIN LED_BUILTIN
bool blinkState = false;

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
sensor_msgs::Imu imu_msg;
/* Frame definitions */
String imu_frame;
void update_imu(void);
String imu_topic;
ros::Publisher *imu_pub;
char buf [100];

void setup() {
     /* Connect the ESP8266 the the wifi AP */
    WiFi.begin(WIFI_SSID, WIFI_PASSWD);
    while (WiFi.status() != WL_CONNECTED) delay(500);
  
    /* Start ROS communication module */
    uint16_t ROS_MASTER_PORT = 11411;
    nh.getHardware()->setConnection(ROS_MASTER_ADDRESS, ROS_MASTER_PORT);
  
    /* Setup laser publisher */
    hero_name = String("/hero_1");
    imu_topic = hero_name + String("/imu");
    imu_pub = new ros::Publisher(imu_topic.c_str(), &imu_msg);
  
    /* Starting ros node */
    nh.initNode();
    
    /* Address Publishers */
    nh.advertise(*imu_pub);
    imu_frame = hero_name + String("/imu");
    imu_msg.header.frame_id = imu_frame.c_str();
    imu_msg.header.seq = -1;

    
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.pins(3, 1); //3 as SDA and 1 as SCL
        Wire.begin(); //3 as SDA and 1 as SCL
        Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
        state = 1;
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
        state = 0;
    #endif

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
    //sprintf(buf,"\33[96m %s \33[0m Enabling DMP...\33[0m");
    //nh.loginfo(buf);
    //nh.spinOnce();
    mpu.setDMPEnabled(true);

    // enable Arduino interrupt detection
    mpuIntStatus = mpu.getIntStatus();

    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    //delay(100);
    //sprintf(buf,"\33[96m %s \33[0m DMP ready! Waiting for first interrupt...\33[0m");
    //nh.loginfo(buf);
    //nh.spinOnce();
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
 
   // configure Arduino LED pin for output
   pinMode(LED_PIN, OUTPUT);

    /* ROS LOG */
    sprintf(buf,"\33[96m Welcome to Hero #1 - IMU Test! \33[0m");
    nh.loginfo(buf);
    nh.spinOnce();

}


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
      readIMU();
      nh.spinOnce();
    }
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
  
      imu_msg.linear_acceleration.x = aa.x;
      imu_msg.linear_acceleration.y = aa.y;
      imu_msg.linear_acceleration.z = aa.z;
      
      // blink LED to indicate activity
      blinkState = !blinkState;
      digitalWrite(LED_PIN, blinkState);
      /* Send laser message to be published into ROS */
      imu_msg.header.stamp = nh.now();
      imu_pub->publish( &imu_msg ); 
   }
}





