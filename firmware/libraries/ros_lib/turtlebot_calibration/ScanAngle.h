#ifndef _ROS_turtlebot_calibration_ScanAngle_h
#define _ROS_turtlebot_calibration_ScanAngle_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace turtlebot_calibration
{

  class ScanAngle : public ros::Msg
  {
    public:
      std_msgs::Header header;
      float scan_angle;

    ScanAngle():
      header(),
      scan_angle(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->scan_angle);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->scan_angle));
     return offset;
    }

    const char * getType(){ return "turtlebot_calibration/ScanAngle"; };
    const char * getMD5(){ return "06e2c839dc5c7f5c13ac09a8b4ff0a6a"; };

  };

}
#endif