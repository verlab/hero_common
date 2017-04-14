#ifndef _ROS_SERVICE_PositionHold_h
#define _ROS_SERVICE_PositionHold_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mav_srvs
{

static const char POSITIONHOLD[] = "mav_srvs/PositionHold";

  class PositionHoldRequest : public ros::Msg
  {
    public:

    PositionHoldRequest()
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

    const char * getType(){ return POSITIONHOLD; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class PositionHoldResponse : public ros::Msg
  {
    public:

    PositionHoldResponse()
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

    const char * getType(){ return POSITIONHOLD; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class PositionHold {
    public:
    typedef PositionHoldRequest Request;
    typedef PositionHoldResponse Response;
  };

}
#endif
