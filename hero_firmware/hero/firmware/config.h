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

#ifndef __CONFIG_H__
#define __CONFIG_H__

#define DEBUG 1


/* WIFI Config */
#define IP_A 10
#define IP_B 42
#define IP_C 0
#define IP_D 1
#define WIFI_SSID "epuck_net" // network name
#define WIFI_PASSWD "epuck_9895" // network password
#define ROS_MASTER_PORT 11411


/* Robot Params */
#define WHEEL_DIAMETER 4.955     /* Wheel diameter in cm. */
#define WHEEL_SEPARATION 6.335   /* Separation between wheels (cm) */
#define WHEEL_DISTANCE 0.06335   /* Distance between wheels in meters (axis length) */
#define WHEEL_CIRCUMFERENCE ((WHEEL_DIAMETER * M_PI)/100.0)  /* Wheel circumference (meters). */
#define MOT_STEP_DIST (WHEEL_CIRCUMFERENCE/288.0)  /* Distance for each motor step (meters); 
                                                      a complete turn is 288 steps (0.000535598 meters per step (m/steps)).

/* IO */
#define ENC_A_LEFT 14 // D2
#define ENC_B_LEFT 4 // D5
#define ENC_A_RIGHT 10 // SD3
#define ENC_B_RIGHT 5 // D1
#define MOTOR_RIGHT 16 // D3
#define MOTOR_LEFT 0 // D0
#define MUX_A 15 // D8
#define MUX_B 13 // D7
#define MUX_C 12 // D6
#define MUX_EN 2 // D4
#define I2C_SDA 3 // RX
#define I2C_SCL 1 // TX


/* WS2812b */
#define COLOR_SATURATION 255

/* MUX IR Control */
/* Analog Multiplexer 4051 */
//const int real_pos[8] = {0,1,2,5,6,7,4,3};
const int real_pos[8] = {0, 1, 2, 7, 3, 6, 4, 5};
// 0, 1, 2, 4, 6, 7, 5, 3

/* Control */
#define ENCODER_SPEED_GAIN 0.06
#define DEFAULT_KP 1200
#define DEFAULT_KI 7.5
#define DEFAULT_KD 3.5

#define MAX_BUFFER_SIZE 100

#endif  // ___CONFIG_H__
