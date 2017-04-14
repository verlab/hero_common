#ifndef _ROS_SERVICE_GetFlightState_h
#define _ROS_SERVICE_GetFlightState_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mav_srvs
{

static const char GETFLIGHTSTATE[] = "mav_srvs/GetFlightState";

  class GetFlightStateRequest : public ros::Msg
  {
    public:

    GetFlightStateRequest()
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

    const char * getType(){ return GETFLIGHTSTATE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetFlightStateResponse : public ros::Msg
  {
    public:
      typedef uint8_t _state_type;
      _state_type state;

    GetFlightStateResponse():
      state(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->state >> (8 * 0)) & 0xFF;
      offset += sizeof(this->state);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->state =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->state);
     return offset;
    }

    const char * getType(){ return GETFLIGHTSTATE; };
    const char * getMD5(){ return "800f34bc468def1d86e2d42bea5648c0"; };

  };

  class GetFlightState {
    public:
    typedef GetFlightStateRequest Request;
    typedef GetFlightStateResponse Response;
  };

}
#endif
