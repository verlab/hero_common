#ifndef _ROS_SERVICE_GetMotorsOnOff_h
#define _ROS_SERVICE_GetMotorsOnOff_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mav_srvs
{

static const char GETMOTORSONOFF[] = "mav_srvs/GetMotorsOnOff";

  class GetMotorsOnOffRequest : public ros::Msg
  {
    public:

    GetMotorsOnOffRequest()
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

    const char * getType(){ return GETMOTORSONOFF; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetMotorsOnOffResponse : public ros::Msg
  {
    public:
      typedef bool _on_type;
      _on_type on;

    GetMotorsOnOffResponse():
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

    const char * getType(){ return GETMOTORSONOFF; };
    const char * getMD5(){ return "74983d2ffe4877de8ae30b7a94625c41"; };

  };

  class GetMotorsOnOff {
    public:
    typedef GetMotorsOnOffRequest Request;
    typedef GetMotorsOnOffResponse Response;
  };

}
#endif
