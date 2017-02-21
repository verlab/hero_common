#ifndef _ROS_SERVICE_SetMotorsOnOff_h
#define _ROS_SERVICE_SetMotorsOnOff_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mav_srvs
{

static const char SETMOTORSONOFF[] = "mav_srvs/SetMotorsOnOff";

  class SetMotorsOnOffRequest : public ros::Msg
  {
    public:
      bool on;

    SetMotorsOnOffRequest():
      on(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_on;
      u_on.real = this->on;
      *(outbuffer + offset + 0) = (u_on.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->on);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_on;
      u_on.base = 0;
      u_on.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->on = u_on.real;
      offset += sizeof(this->on);
     return offset;
    }

    const char * getType(){ return SETMOTORSONOFF; };
    const char * getMD5(){ return "74983d2ffe4877de8ae30b7a94625c41"; };

  };

  class SetMotorsOnOffResponse : public ros::Msg
  {
    public:

    SetMotorsOnOffResponse()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return SETMOTORSONOFF; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class SetMotorsOnOff {
    public:
    typedef SetMotorsOnOffRequest Request;
    typedef SetMotorsOnOffResponse Response;
  };

}
#endif
