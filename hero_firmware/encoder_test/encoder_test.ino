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
#include <Encoder.h>


/* Used for encoders */
#define INPUT_PULLUP
#define ENCODER_USE_INTERRUPTS

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(10, 14);
//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(115200);
  Serial.println("\nBasic Encoder Test:");
  //pinMode(9, INPUT_PULLUP);
}

long oldPosition  = -999;

void loop() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
  }
}
