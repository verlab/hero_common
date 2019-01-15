 /************************************************************************
 *  H E R O   I R   A N D   I M U   T E S T
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

#include <ESP8266WiFi.h>

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

#include <NeoPixelBus.h>
#include <NeoPixelBrightnessBus.h>
#define colorSaturation 128

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

/* IMU publisher */
sensor_msgs::Imu imu_msg;
/* Frame definitions */
String imu_frame;
void update_imu(void);
String imu_topic;
ros::Publisher *imu_pub;

char buf [100];

/* Analog Multiplexer 4051 */
const int s0 = 15; // D6 Blue
const int s1 = 13; // D7 Green
const int s2 = 12; // D8 Yellow
const int enable = 2;

/* Setup */
void setup() {
  /* Connect the ESP8266 the the wifi AP */
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  while (WiFi.status() != WL_CONNECTED) delay(500);

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
 

  /* Address Subscribers */
  nh.subscribe(*led_sub);

  // join I2C bus (I2Cdev library doesn't do this automatically)
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.pins(3, 1); //3 as SDA and 1 as SCL
      Wire.begin(); //3 as SDA and 1 as SCL
      Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
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
  
  /* ROS LOG */
  //Serial.println("\n\n Welcome to hero odometry test! ");
  sprintf(buf,"\33[96m Welcome to Hero #1 - IR & IMU Test! \33[0m");
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
      readIMU();
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

