#ifndef _ROS_p2os_msgs_ArmState_h
#define _ROS_p2os_msgs_ArmState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace p2os_msgs
{

  class ArmState : public ros::Msg
  {
    public:
      bool arm_power;

    ArmState():
      arm_power(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_arm_power;
      u_arm_power.real = this->arm_power;
      *(outbuffer + offset + 0) = (u_arm_power.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->arm_power);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_arm_power;
      u_arm_power.base = 0;
      u_arm_power.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->arm_power = u_arm_power.real;
      offset += sizeof(this->arm_power);
     return offset;
    }

    const char * getType(){ return "p2os_msgs/ArmState"; };
    const char * getMD5(){ return "f78f2c49a110ba43464d5c16d2a19027"; };

  };

}
#endif