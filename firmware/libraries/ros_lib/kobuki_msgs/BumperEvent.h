#ifndef _ROS_kobuki_msgs_BumperEvent_h
#define _ROS_kobuki_msgs_BumperEvent_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace kobuki_msgs
{

  class BumperEvent : public ros::Msg
  {
    public:
      typedef uint8_t _bumper_type;
      _bumper_type bumper;
      typedef uint8_t _state_type;
      _state_type state;
      enum { LEFT =  0 };
      enum { CENTER =  1 };
      enum { RIGHT =  2 };
      enum { RELEASED =  0 };
      enum { PRESSED =  1 };

    BumperEvent():
      bumper(0),
      state(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->bumper >> (8 * 0)) & 0xFF;
      offset += sizeof(this->bumper);
      *(outbuffer + offset + 0) = (this->state >> (8 * 0)) & 0xFF;
      offset += sizeof(this->state);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->bumper =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->bumper);
      this->state =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->state);
     return offset;
    }

    const char * getType(){ return "kobuki_msgs/BumperEvent"; };
    const char * getMD5(){ return "ffe360cd50f14f9251d9844083e72ac5"; };

  };

}
#endif