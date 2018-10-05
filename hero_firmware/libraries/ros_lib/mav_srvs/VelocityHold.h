#ifndef _ROS_SERVICE_VelocityHold_h
#define _ROS_SERVICE_VelocityHold_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mav_srvs
{

static const char VELOCITYHOLD[] = "mav_srvs/VelocityHold";

  class VelocityHoldRequest : public ros::Msg
  {
    public:

    VelocityHoldRequest()
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

    const char * getType(){ return VELOCITYHOLD; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class VelocityHoldResponse : public ros::Msg
  {
    public:

    VelocityHoldResponse()
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

    const char * getType(){ return VELOCITYHOLD; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class VelocityHold {
    public:
    typedef VelocityHoldRequest Request;
    typedef VelocityHoldResponse Response;
  };

}
#endif
