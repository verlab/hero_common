#ifndef _ROS_p2os_msgs_TCMState_h
#define _ROS_p2os_msgs_TCMState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace p2os_msgs
{

  class TCMState : public ros::Msg
  {
    public:
      bool tcm_power;

    TCMState():
      tcm_power(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_tcm_power;
      u_tcm_power.real = this->tcm_power;
      *(outbuffer + offset + 0) = (u_tcm_power.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->tcm_power);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_tcm_power;
      u_tcm_power.base = 0;
      u_tcm_power.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->tcm_power = u_tcm_power.real;
      offset += sizeof(this->tcm_power);
     return offset;
    }

    const char * getType(){ return "p2os_msgs/TCMState"; };
    const char * getMD5(){ return "c2bc91397a05d27a5eff6dafb47db890"; };

  };

}
#endif