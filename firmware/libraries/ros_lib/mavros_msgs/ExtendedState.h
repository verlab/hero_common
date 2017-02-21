#ifndef _ROS_mavros_msgs_ExtendedState_h
#define _ROS_mavros_msgs_ExtendedState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace mavros_msgs
{

  class ExtendedState : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t vtol_state;
      uint8_t landed_state;
      enum { VTOL_STATE_UNDEFINED =  0 };
      enum { VTOL_STATE_TRANSITION_TO_FW =  1 };
      enum { VTOL_STATE_TRANSITION_TO_MC =  2 };
      enum { VTOL_STATE_MC =  3 };
      enum { VTOL_STATE_FW =  4 };
      enum { LANDED_STATE_UNDEFINED =  0 };
      enum { LANDED_STATE_ON_GROUND =  1 };
      enum { LANDED_STATE_IN_AIR =  2 };

    ExtendedState():
      header(),
      vtol_state(0),
      landed_state(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->vtol_state >> (8 * 0)) & 0xFF;
      offset += sizeof(this->vtol_state);
      *(outbuffer + offset + 0) = (this->landed_state >> (8 * 0)) & 0xFF;
      offset += sizeof(this->landed_state);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->vtol_state =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->vtol_state);
      this->landed_state =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->landed_state);
     return offset;
    }

    const char * getType(){ return "mavros_msgs/ExtendedState"; };
    const char * getMD5(){ return "c2e3721f1a54980a39715b775091885e"; };

  };

}
#endif