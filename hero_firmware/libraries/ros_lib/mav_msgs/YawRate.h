#ifndef _ROS_mav_msgs_YawRate_h
#define _ROS_mav_msgs_YawRate_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mav_msgs
{

  class YawRate : public ros::Msg
  {
    public:
      typedef float _yaw_rate_type;
      _yaw_rate_type yaw_rate;

    YawRate():
      yaw_rate(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->yaw_rate);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->yaw_rate));
     return offset;
    }

    const char * getType(){ return "mav_msgs/YawRate"; };
    const char * getMD5(){ return "13fb4b2050dc0fcc92f15aded0989092"; };

  };

}
#endif