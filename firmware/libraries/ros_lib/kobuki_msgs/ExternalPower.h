#ifndef _ROS_kobuki_msgs_ExternalPower_h
#define _ROS_kobuki_msgs_ExternalPower_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace kobuki_msgs
{

  class ExternalPower : public ros::Msg
  {
    public:
      typedef uint8_t _source_type;
      _source_type source;
      typedef uint8_t _state_type;
      _state_type state;
      enum { PWR_3_3V1A =  0  };
      enum { PWR_5V1A =  1  };
      enum { PWR_12V5A =  2  };
      enum { PWR_12V1_5A =  3  };
      enum { OFF =  0 };
      enum { ON =  1 };

    ExternalPower():
      source(0),
      state(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->source >> (8 * 0)) & 0xFF;
      offset += sizeof(this->source);
      *(outbuffer + offset + 0) = (this->state >> (8 * 0)) & 0xFF;
      offset += sizeof(this->state);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->source =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->source);
      this->state =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->state);
     return offset;
    }

    const char * getType(){ return "kobuki_msgs/ExternalPower"; };
    const char * getMD5(){ return "95149d524971a4c6d19e64c827307194"; };

  };

}
#endif