/************************************************************************
 *  H E R O   E N C O D E R   T E S T
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
/* ESP Library */
#include <ESP8266WiFi.h>

/* ROS Library */
#include <ros.h>
#include <hero_common/Encoder.h>

#include <Encoder.h>

/* Used for encoders */
#define INPUT_PULLUP
#define ENCODER_USE_INTERRUPTS

#define ENC_A_LEFT 14  /* PIN D2 */
#define ENC_B_LEFT 4   /* PIN D5 */
#define ENC_A_RIGHT 10 /* PIN SD3 */
#define ENC_B_RIGHT 5  /* PIN D1 */

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capabilit
Encoder e_left(ENC_A_LEFT, ENC_B_LEFT);
Encoder e_right(ENC_A_RIGHT, ENC_B_RIGHT);
//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(115200);
  Serial.println("\nBasic Encoder Test:");
  //pinMode(9, INPUT_PULLUP);
}

long prevlpos = -999;
long prevrpos = -999;
unsigned long timer = 0;

void loop() {
  long rpos = e_right.read();
  long lpos = e_left.read();
  while (millis() - timer < 20)
    ;
  timer = millis();
  if (prevlpos != lpos || prevrpos != rpos) {
    Serial.print(e_left.read());
    Serial.print(',');
    Serial.println(e_right.read());
    prevlpos = lpos;
    prevrpos = rpos;
  }
}
