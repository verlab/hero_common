#ifndef _ROS_SERVICE_Takeoff_h
#define _ROS_SERVICE_Takeoff_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mav_srvs
{

static const char TAKEOFF[] = "mav_srvs/Takeoff";

  class TakeoffRequest : public ros::Msg
  {
    public:

    TakeoffRequest()
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

    const char * getType(){ return TAKEOFF; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class TakeoffResponse : public ros::Msg
  {
    public:

    TakeoffResponse()
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

    const char * getType(){ return TAKEOFF; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class Takeoff {
    public:
    typedef TakeoffRequest Request;
    typedef TakeoffResponse Response;
  };

}
#endif
