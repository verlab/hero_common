#ifndef _ROS_kobuki_msgs_ButtonEvent_h
#define _ROS_kobuki_msgs_ButtonEvent_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace kobuki_msgs
{

  class ButtonEvent : public ros::Msg
  {
    public:
      typedef uint8_t _button_type;
      _button_type button;
      typedef uint8_t _state_type;
      _state_type state;
      enum { Button0 =  0 };
      enum { Button1 =  1 };
      enum { Button2 =  2 };
      enum { RELEASED =  0 };
      enum { PRESSED =  1 };

    ButtonEvent():
      button(0),
      state(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->button >> (8 * 0)) & 0xFF;
      offset += sizeof(this->button);
      *(outbuffer + offset + 0) = (this->state >> (8 * 0)) & 0xFF;
      offset += sizeof(this->state);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->button =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->button);
      this->state =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->state);
     return offset;
    }

    const char * getType(){ return "kobuki_msgs/ButtonEvent"; };
    const char * getMD5(){ return "49eca512765dbdec759a79083ffcec8d"; };

  };

}
#endif