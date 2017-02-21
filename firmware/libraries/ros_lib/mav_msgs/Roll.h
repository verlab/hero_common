#ifndef _ROS_mav_msgs_Roll_h
#define _ROS_mav_msgs_Roll_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mav_msgs
{

  class Roll : public ros::Msg
  {
    public:
      float roll;

    Roll():
      roll(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->roll);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->roll));
     return offset;
    }

    const char * getType(){ return "mav_msgs/Roll"; };
    const char * getMD5(){ return "13f2fe1457379c55f7019b0193d18f6b"; };

  };

}
#endif