#ifndef _ROS_SERVICE_ToggleEngage_h
#define _ROS_SERVICE_ToggleEngage_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mav_srvs
{

static const char TOGGLEENGAGE[] = "mav_srvs/ToggleEngage";

  class ToggleEngageRequest : public ros::Msg
  {
    public:

    ToggleEngageRequest()
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

    const char * getType(){ return TOGGLEENGAGE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class ToggleEngageResponse : public ros::Msg
  {
    public:

    ToggleEngageResponse()
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

    const char * getType(){ return TOGGLEENGAGE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class ToggleEngage {
    public:
    typedef ToggleEngageRequest Request;
    typedef ToggleEngageResponse Response;
  };

}
#endif
