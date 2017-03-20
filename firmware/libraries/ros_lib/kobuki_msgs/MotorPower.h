#ifndef _ROS_kobuki_msgs_MotorPower_h
#define _ROS_kobuki_msgs_MotorPower_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace kobuki_msgs
{

  class MotorPower : public ros::Msg
  {
    public:
      typedef uint8_t _state_type;
      _state_type state;
      enum { OFF =  0 };
      enum { ON =  1 };

    MotorPower():
      state(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->state >> (8 * 0)) & 0xFF;
      offset += sizeof(this->state);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->state =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->state);
     return offset;
    }

    const char * getType(){ return "kobuki_msgs/MotorPower"; };
    const char * getMD5(){ return "8f77c0161e0f2021493136bb5f3f0e51"; };

  };

}
#endif