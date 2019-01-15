#ifndef _ROS_mav_msgs_Pitch_h
#define _ROS_mav_msgs_Pitch_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mav_msgs
{

  class Pitch : public ros::Msg
  {
    public:
      typedef float _pitch_type;
      _pitch_type pitch;

    Pitch():
      pitch(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->pitch);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->pitch));
     return offset;
    }

    const char * getType(){ return "mav_msgs/Pitch"; };
    const char * getMD5(){ return "2c7ebc18899e6ec103eaf1bdfe8e9de5"; };

  };

}
#endif