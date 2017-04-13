/*
 * rosserial Publisher Example
 * Prints "hello world!"
 */
#include <WifiHardware.h>
#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle_<WifiHardware> nh;
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "hello world!";

void setup()
{
  nh.initNode();
  nh.advertise(chatter);
}

void loop()
{
  str_msg.data = hello;
  chatter.publish( &str_msg );
  nh.spinOnce();
  delayMicroseconds(10);
}