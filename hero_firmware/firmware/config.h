/*
  ******************************************************************************
                      H E R O   F I R M W A R E
  ******************************************************************************
  Paulo Rezeck        <rezeck@dcc.ufmg.br>
  Mauricio Ferrari    <mauferrari@dcc.ufmg.br>
  Hector Azpurua      <hectorxxx@gmail.com>


                Computer Vision and Robotics Lab (VeRLab)
               Universidade Federal de Minas Gerais - Brazil
  ******************************************************************************
  Copyright (c) 2021 Paulo Rezeck.  All right reserved.
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  ******************************************************************************/

#ifndef __CONFIG_H__
#define __CONFIG_H__

/* Version Configuration */
#define CONFIG_VERSION "v2.4"
#define HARDWARE_VERSION "v2.5"
#define FIRMWARE_VERSION "v3.5"

/*Robot name */
#define ROBOT_NAME "/hero_"
#define ROBOT_ID "0"

/* WIFI Configuration - use web configuration */
#define ROS_MASTER_IP "10.42.0.1"   /* ROS Master IP - Config as a hotspot by default */
#define WIFI_SSID "hero_network"    /* Network name */
#define WIFI_PASSWD "s3cr3tp4ss"    /* Network password */
#define ROS_MASTER_PORT 11411       /* ROS Port */
bool default_config = true;

/* Firmware Configuration */
#define DEBUG true              /* Debug mode */
#define DEBUG_RATE 1            /* Default debug frequency */
#define SYNC_RATE 20            /* Default loop frequency */
#define MAX_BUFFER_SIZE 100     /* Max debug string buffer */
#define WIFI_CONNECT_LOOP 500   /* Time sleep when trying to connect the WIFI to an AP */
bool config_mode = false;       /* If you cover all the IR sensors with the hand, the robot start as a config mode accessed by AP mode*/

/* Robot Configuration */
#define ROBOT_DIAMETER 0.07367             /* Robot footprint diameter (m)*/
#define WHEEL_DIAMETER 0.0492 //0.04955    /* Wheel diameter (m) */
#define WHEEL_SEPARATION 0.063 //0.06335   /* Separation between wheels (m) */
#define WHEEL_CIRCUMFERENCE ((WHEEL_DIAMETER * M_PI))   /* Wheel circumference (meters). */
#define MOT_STEP_DIST (WHEEL_CIRCUMFERENCE/288.0)             /* Distance for each motor step (meters); a complete turn is 288 steps (0.000535598 meters per step (m/steps)). */
#define MAX_LINEAR_VEL 0.28   /* max linear speed 25 m/s */
#define MAX_ANGULAR_VEL 8.0 // 0.08 /* Max angular speed 0.08 rad/s */

/* Encoder Configuration */
#define ENC_A_LEFT 14                   /* PIN D2 */
#define ENC_B_LEFT 4                    /* PIN D5 */
#define ENC_A_RIGHT 10                  /* PIN SD3 */
#define ENC_B_RIGHT 5                   /* PIN D1 */
#define ENCODER_SPEED_GAIN 0.06         /* Encoder filter */
#define ENCODER_SPEED_GAIN_AGGRESSIVE 1.0

/* Motor Configuration */
#define MOTOR_RIGHT 16        /* PIN D3 */
#define MOTOR_LEFT 0          /* PIN D0 */
#define MOTOR_RIGHT_HALT_PWM 1500   /* PWM Range 1000-2000*/
#define MOTOR_LEFT_HALT_PWM 1500   /* PWM Range 1000-2000*/
#define MOTOR_PWM_SUBSCRIBER_ENABLE true

/* Laser Configuration */
#define MUX_A 15              /* PIN D8 */
#define MUX_B 13              /* PIN D7 */
#define MUX_C 12              /* PIN D6 */
#define MUX_EN 2              /* PIN D4 */
#define TOUCH_THRESHOLD 450   /* If sensor readings reach 900 than we assume a touch sensor */
const int real_pos[8] = {0, 1, 2, 7, 3, 6, 4, 5}; /* Sort proximity sensors*/
const int real_pos_inter[8] = {0, 2, 4, 14, 6, 12, 8, 10}; /* Sort proximity sensors*/

/* I2C Configuration */
#define I2C_SDA 3   /* PIN RX */
#define I2C_SCL 1   /* PIN TX */


/* IMU Enable */
#define IMU_ENABLE false   /* Enable or disable IMU */
#define XGYRO_OFFSET 220  /* Supply your own gyro offsets here, scaled for min sensitivity */
#define YGYRO_OFFSET 76
#define ZGYRO_OFFSET -85
#define ZACC_OFFSET 1788


/* Addressable LED WS2812b */
#define PIXEL_COUNT 7         /* NUMBER OF LED */
#define COLOR_SATURATION 255  /* MAX SATURATION COLOR */


/* PID Control */
#define DEFAULT_KP 1200                     /* Default proportional term */
#define DEFAULT_KI 7.5                      /* Default integrative term */
#define DEFAULT_KD 3.5                      /* Default derivative term */
#define OUTPUT_LIMIT 1000                    /* Max output limit */
#define SAMPLE_TIME 50000                      /* Sample time in us*/
#define SOME_OVERSHOOT_RULE_P 1.5 //3.2           /* Using some-overshot rule */
#define SOME_OVERSHOOT_RULE_I 1.0 //0.07
#define SOME_OVERSHOOT_RULE_D 0.08 //0.002
#define TUNING_SUCCESSED_THRESHOLD_MIN 200  /* Sanity-test to decide if tuning process was ok; looks only the proportional term */
#define TUNING_SUCCESSED_THRESHOLD_MAX 2700
//#define MEM_INIT_POS_PID 300/

/* Autotuner */
#define TUNE_STEP 40                  /* How far above and below the starting value will the output step? */
#define TUNE_NOISE 0.001              /* The autotune will ignore signal chatter smaller than this value this should be accurately set */
#define TUNE_LOOK_BACK 3              /* How far (seconds) back are we looking to identify peaks */
#define TUNE_STEADY_STATE_TIME 8000  /* Steady state time (ms) before pertubation */
#define TUNE_STEADY_STATE 80 //120          /* Steady state PWM to start Autotune 0 - 100 should be ok*/

struct PID_CONFIG {
    float lkp;
    float lki;
    float lkd;
    float rkp;
    float rki;
    float rkd;
} configurationPID = {
  // The default values
  -1,
  -1,
  -1,
  -1,
  -1,
  -1
};

struct DATA {
  uint robot_id;
  char robot_desc[20];
  char ros_master_address[20];
  char wifi_ssid[20];
  char wifi_pass[20];
} configurationData = {
  // The default values
  0,
  "",
  "",
  "",
  ""
};

struct MOTOR_P {
  int leftMotorDeadzone;
  int rightMotorDeadzone;
} motorData = {
  // The default values
  -1,
  -1
};


struct IR_CALIB {
  float alpha[8];
} irCalib = {
  // The default values
  {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5}
};


#endif  // ___CONFIG_H__
