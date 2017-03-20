#ifndef _ROS_kobuki_msgs_RobotStateEvent_h
#define _ROS_kobuki_msgs_RobotStateEvent_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace kobuki_msgs
{

  class RobotStateEvent : public ros::Msg
  {
    public:
      typedef uint8_t _state_type;
      _state_type state;
      enum { ONLINE =  1 };
      enum { OFFLINE =  0 };

    RobotStateEvent():
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

    const char * getType(){ return "kobuki_msgs/RobotStateEvent"; };
    const char * getMD5(){ return "c6eccd4cb1f95df95635b56d6226ea32"; };

  };

}
#endif