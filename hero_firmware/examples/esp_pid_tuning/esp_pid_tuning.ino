/*
   PID Tuning
   ESPCOPTER
*/

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <ros.h>
#include <rosserial_arduino/Adc.h>
#include <geometry_msgs/Quaternion.h>

ros::NodeHandle nh;

geometry_msgs::Quaternion pid_msg;
ros::Publisher pub_("/drone_1/set_gain", &pid_msg);


void setup()
{
  nh.initNode();
  nh.advertise(pub_);
}

//We average the analog reading to elminate some of the noise
float averageAnalog(int pin, int samples) {
  float v = 0;
  for (int i = 0; i < samples; i++) v += analogRead(pin);
  return v / samples;
}

unsigned long timer = 0;

float map_f(float x, float in_min, float in_max, float out_min, float out_max){
return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void loop()
{
  pid_msg.x = map_f(averageAnalog(0, 100), 0, 1023.0, -4.0, 4.0);
  pid_msg.y = map_f(averageAnalog(1, 100), 0, 1023.0, -6.0, 6.0);
  pid_msg.z = map_f(averageAnalog(2, 100), 0, 1023.0, -2.0, 2.0);
  pid_msg.w = 1; //analogRead(3);

  if ((micros() - timer) > 100 * 1e3) {
    timer = micros();
    pub_.publish(&pid_msg);
    nh.spinOnce();
  }

}
