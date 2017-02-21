#ifndef _ROS_SERVICE_RetreatState_h
#define _ROS_SERVICE_RetreatState_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mav_srvs
{

static const char RETREATSTATE[] = "mav_srvs/RetreatState";

  class RetreatStateRequest : public ros::Msg
  {
    public:

    RetreatStateRequest()
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

    const char * getType(){ return RETREATSTATE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class RetreatStateResponse : public ros::Msg
  {
    public:

    RetreatStateResponse()
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

    const char * getType(){ return RETREATSTATE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class RetreatState {
    public:
    typedef RetreatStateRequest Request;
    typedef RetreatStateResponse Response;
  };

}
#endif
