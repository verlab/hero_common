#ifndef _ROS_SERVICE_ESTOP_h
#define _ROS_SERVICE_ESTOP_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mav_srvs
{

static const char ESTOP[] = "mav_srvs/ESTOP";

  class ESTOPRequest : public ros::Msg
  {
    public:

    ESTOPRequest()
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

    const char * getType(){ return ESTOP; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class ESTOPResponse : public ros::Msg
  {
    public:

    ESTOPResponse()
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

    const char * getType(){ return ESTOP; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class ESTOP {
    public:
    typedef ESTOPRequest Request;
    typedef ESTOPResponse Response;
  };

}
#endif
