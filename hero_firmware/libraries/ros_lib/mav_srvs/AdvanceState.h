#ifndef _ROS_SERVICE_AdvanceState_h
#define _ROS_SERVICE_AdvanceState_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mav_srvs
{

static const char ADVANCESTATE[] = "mav_srvs/AdvanceState";

  class AdvanceStateRequest : public ros::Msg
  {
    public:

    AdvanceStateRequest()
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

    const char * getType(){ return ADVANCESTATE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class AdvanceStateResponse : public ros::Msg
  {
    public:

    AdvanceStateResponse()
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

    const char * getType(){ return ADVANCESTATE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class AdvanceState {
    public:
    typedef AdvanceStateRequest Request;
    typedef AdvanceStateResponse Response;
  };

}
#endif
