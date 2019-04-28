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

#ifndef __FIRMWARE_H__
#define __FIRMWARE_H__

/* Hardware Libraries */
#include <Servo.h>                      /* https://www.arduino.cc/en/Reference/Servo */
#include <Encoder.h>                    /* https://github.com/PaulStoffregen/Encoder */
#include <PID_v1.h>                     /* http://playground.arduino.cc/Code/PIDLibrary */
#include <PID_AutoTune_v0.h>            /* https://playground.arduino.cc/Code/PIDAutotuneLibrary */
#include <EEPROM.h>                     /* https://www.arduino.cc/en/Reference/EEPROM */
#include <NeoPixelBus.h>                /* https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use */
#include <NeoPixelBrightnessBus.h>    
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h" /* https://playground.arduino.cc/Main/MPU-6050 */
#include "Wire.h" /* Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation */

/* Addressable LEDs WS2812 Configuration */
const uint16_t PixelCount = PIXEL_COUNT;
NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(PixelCount);
RgbColor red(COLOR_SATURATION, 0, 0);
RgbColor green(0, COLOR_SATURATION, 0);
RgbColor cyan(0, COLOR_SATURATION, COLOR_SATURATION);
RgbColor magenta(COLOR_SATURATION, 0, COLOR_SATURATION);
RgbColor black(0);
unsigned long led_blinky = 0;
bool blinky = true;

/* Motor Configuration */
Servo l_motor; /* Left Motor Control */
Servo r_motor; /* Right Motor Control */

/* Encoder Configuration */
#define INPUT_PULLUP            /* Enable internal pull-up resistor */
#define ENCODER_USE_INTERRUPTS  /* Uses interruption to count the encoders ticks */
Encoder l_encoder(ENC_A_LEFT, ENC_B_LEFT);            /* Left Encoder Configuration */
Encoder r_encoder(ENC_A_RIGHT, ENC_B_RIGHT);          /* Right Encoder Configuration */
long motorPositionRight = 0, motorPositionLeft = 0;   /* Motor position */

/* Motors PID Control */
double l_motor_speed = 0.0, l_motor_control = 0.0, l_encoder_speed = 0.0;   /* Initial PID input and ouput */
double r_motor_speed = 0.0, r_motor_control = 0.0, r_encoder_speed = 0.0;   /* Initial PID input and ouput */
PID l_motor_pid(&l_encoder_speed, &l_motor_control, &l_motor_speed, DEFAULT_KP, DEFAULT_KI, DEFAULT_KD, DIRECT); /* Left motor PID */
PID r_motor_pid(&r_encoder_speed, &r_motor_control, &r_motor_speed, DEFAULT_KP, DEFAULT_KI, DEFAULT_KD, DIRECT); /* Right motor PID */
PID_ATune l_aTune(&l_encoder_speed, &l_motor_control);    /* Left motor autotuner */
PID_ATune r_aTune(&r_encoder_speed, &r_motor_control);    /* Right motor autotuner */

/* Autotuner Defaults */
double aTuneStep = TUNE_STEP;
double aTuneNoise = TUNE_NOISE; 
unsigned int aTuneLookBack = TUNE_LOOK_BACK;
boolean tuning = false;                   /* Enable or disable the tuning process */
extern Tuning tuningRule[];               /* Load autotuner rule some-overshot */
bool l_done, r_done;                      /* Check if autotuner has done */
unsigned long tunning_steady_state = 0;   /* Tuning steady state */

/* Timer Control */
unsigned long loop_timer = 0; /* Control loop timer */
unsigned long loop_rate = LOOP_RATE;

/* Debug string size */
char buf [MAX_BUFFER_SIZE];

/* IMU I2C Configuration */
#if IMU_ENABLE == true
    MPU6050 mpu;
    /* MPU control/status vars */
    bool dmpReady = false;    /* set true if DMP init was successful */
    uint8_t mpuIntStatus;     /* holds actual interrupt status byte from MPU */
    uint8_t devStatus;        /* return status after each device operation (0 = success, !0 = error) */
    uint16_t packetSize;      /* expected DMP packet size (default is 42 bytes) */
    uint16_t fifoCount;       /* count of all bytes currently in FIFO */
    uint8_t fifoBuffer[64];   /* FIFO storage buffer */
    /* MPU orientation/motion vars */
    Quaternion q;           /* [w, x, y, z]         quaternion container */
    VectorInt16 aa;         /* [x, y, z]            accel sensor measurements */
    VectorInt16 gy;         /* [x, y, z]            gyro sensor measurements */
    VectorInt16 aaReal;     /* [x, y, z]            gravity-free accel sensor measurements */
    VectorInt16 aaWorld;    /* [x, y, z]            world-frame accel sensor measurements */
    VectorFloat gravity;    /* [x, y, z]            gravity vector */
    float ypr[3];           /* [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector */
#endif



/* Setup PID Controller and Autotuner */
void setup_pid(){
  /* Setup PID */
  l_motor_pid.SetOutputLimits(-OUTPUT_LIMIT, OUTPUT_LIMIT);   /* Max output limit for left motor */
  l_motor_pid.SetSampleTime(SAMPLE_TIME);                     /* 10 microseconds */
  l_motor_pid.SetMode(AUTOMATIC);
  r_motor_pid.SetOutputLimits(-OUTPUT_LIMIT, OUTPUT_LIMIT);   /* Max output limit for right motor */
  r_motor_pid.SetSampleTime(SAMPLE_TIME);                     /* 10 microseconds */
  r_motor_pid.SetMode(AUTOMATIC);

  /* Setup autotuner for PID */
  l_aTune.SetControlType(PID_ATune::SOME_OVERSHOOT_PID); /* Set control type for autotuner */
  r_aTune.SetControlType(PID_ATune::SOME_OVERSHOOT_PID);
  l_aTune.SetNoiseBand(aTuneNoise); /* The autotune will ignore signal chatter smaller than this value this should be accurately set */
  l_aTune.SetOutputStep(aTuneStep); /* How far above and below the starting value will the output step? */
  l_aTune.SetLookbackSec((int)aTuneLookBack); /* How far back are we looking to identify peaks */
  r_aTune.SetNoiseBand(aTuneNoise); /* The autotune will ignore signal chatter smaller than this value this should be accurately set */
  r_aTune.SetOutputStep(aTuneStep); /* How far above and below the starting value will the output step? */
  r_aTune.SetLookbackSec((int)aTuneLookBack); /* How far back are we looking to identify peaks */

  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.get(MEM_INIT_POS_PID, configurationPID);
  EEPROM.end();

  if (configurationPID.lkp > TUNING_SUCCESSED_THRESHOLD_MIN && configurationPID.lkp < TUNING_SUCCESSED_THRESHOLD_MAX){
    l_motor_pid.SetTunings(configurationPID.lkp, configurationPID.lki, configurationPID.lkd);
    r_motor_pid.SetTunings(configurationPID.rkp, configurationPID.rki, configurationPID.rkd);
  }
}

/* PID Control loop for wheel speed */
void control(void){
  /* Update control loop and set the output to the motors */
  l_motor_pid.Compute();
  r_motor_pid.Compute();
  l_motor.writeMicroseconds((int)l_motor_control + MOTOR_LEFT_HALT_PWM);
  r_motor.writeMicroseconds((int)(-r_motor_control) + MOTOR_RIGHT_HALT_PWM);
}

/* Setup IMU I2C communication */
void setup_imu(){
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
    mpu.setXGyroOffset(XGYRO_OFFSET);
    mpu.setYGyroOffset(YGYRO_OFFSET);
    mpu.setZGyroOffset(ZGYRO_OFFSET);
    mpu.setZAccelOffset(ZACC_OFFSET); // 1688 factory default for my test chip
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
    }
 }

/* Setup laser Readings */
void setup_laser(){
  /* Setup Analog Multiplexer Pins */
  pinMode(MUX_A, OUTPUT); 
  pinMode(MUX_B, OUTPUT);
  pinMode(MUX_C, OUTPUT);
  pinMode(MUX_EN, OUTPUT);
}

/* Initiate motors and encoders */
void setup_motors(){
   /* Initiate Motors */
  r_motor.attach(MOTOR_RIGHT);
  l_motor.attach(MOTOR_LEFT);
  r_motor.writeMicroseconds(MOTOR_RIGHT_HALT_PWM);
  l_motor.writeMicroseconds(MOTOR_LEFT_HALT_PWM);
  delayMicroseconds(10);
  r_motor.detach();
  l_motor.detach();
  delay(1000);
  /* Initiate Encoders */
  l_encoder.write(0);
  r_encoder.write(0);
}

/* This resets all the neopixels to an off state */
void setup_led(){
  strip.Begin();
  for(int i = 0; i <= PixelCount; i++){
    strip.SetPixelColor(i, black);
    strip.Show();
  }
  strip.SetBrightness(COLOR_SATURATION);
  strip.Show();
  strip.Show();
  delay(100);
}

void hello(RgbColor color, unsigned long timer){
    strip.Begin();
  for (int i = 0; i < 10; i++){
    if (i % 2 == 0){
      strip.SetPixelColor(0, color);
      strip.SetPixelColor(1, black);
    }else{
      strip.SetPixelColor(0, black);
      strip.SetPixelColor(1, color);
    }
    strip.SetBrightness(COLOR_SATURATION);
    strip.Show();
    delay(timer);
  }
  strip.SetPixelColor(0, black);
  strip.SetPixelColor(1, black);
  strip.Show();
}



#endif  // ___CONFIG_H__







