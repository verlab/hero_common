#ifndef _ROS_kobuki_msgs_Sound_h
#define _ROS_kobuki_msgs_Sound_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace kobuki_msgs
{

  class Sound : public ros::Msg
  {
    public:
      typedef uint8_t _value_type;
      _value_type value;
      enum { ON =  0 };
      enum { OFF =  1 };
      enum { RECHARGE =  2 };
      enum { BUTTON =  3 };
      enum { ERROR =  4 };
      enum { CLEANINGSTART =  5 };
      enum { CLEANINGEND =  6 };

    Sound():
      value(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->value >> (8 * 0)) & 0xFF;
      offset += sizeof(this->value);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->value =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->value);
     return offset;
    }

    const char * getType(){ return "kobuki_msgs/Sound"; };
    const char * getMD5(){ return "dfeab0daae67749c426c1db741a4f420"; };

  };

}
#endif