/*
  Input Pull-up Serial

  This example demonstrates the use of pinMode(INPUT_PULLUP). It reads a digital
  input on pin 2 and prints the results to the Serial Monitor.

  The circuit:
  - momentary switch attached from pin 2 to ground
  - built-in LED on pin 13

  Unlike pinMode(INPUT), there is no pull-down resistor necessary. An internal
  20K-ohm resistor is pulled to 5V. This configuration causes the input to read
  HIGH when the switch is open, and LOW when it is closed.

  created 14 Mar 2012
  by Scott Fitzgerald

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/InputPullupSerial
*/
#include <ros.h>
#include <ESP8266WiFi.h>

#include <sensor_msgs/LaserScan.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
const int pin = 9;

void setup() {
  //start serial connection
  Serial.begin(9600);
  //configure pin 2 as an input and enable the internal pull-up resistor
  //pinMode(10, INPUT_PULLUP);
  pinMode(pin, INPUT);
}

void loop() {
  //read the pushbutton value into a variable
  //int sensorVal = digitalRead(2);
  //print out the value of the pushbutton
  //Serial.println(sensorVal);

  //digitalWrite(pin, HIGH);
  Serial.println(digitalRead(pin));
  delay(1000);
  //digitalWrite(pin, LOW);
  Serial.println("Working");
  delay(1000);
}
