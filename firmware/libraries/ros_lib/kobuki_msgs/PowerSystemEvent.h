#ifndef _ROS_kobuki_msgs_PowerSystemEvent_h
#define _ROS_kobuki_msgs_PowerSystemEvent_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace kobuki_msgs
{

  class PowerSystemEvent : public ros::Msg
  {
    public:
      typedef uint8_t _event_type;
      _event_type event;
      enum { UNPLUGGED =  0 };
      enum { PLUGGED_TO_ADAPTER =  1 };
      enum { PLUGGED_TO_DOCKBASE =  2 };
      enum { CHARGE_COMPLETED =  3 };
      enum { BATTERY_LOW =  4 };
      enum { BATTERY_CRITICAL =  5 };

    PowerSystemEvent():
      event(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->event >> (8 * 0)) & 0xFF;
      offset += sizeof(this->event);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->event =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->event);
     return offset;
    }

    const char * getType(){ return "kobuki_msgs/PowerSystemEvent"; };
    const char * getMD5(){ return "f6464657d6c911b00c7bc7b43a154bf8"; };

  };

}
#endif