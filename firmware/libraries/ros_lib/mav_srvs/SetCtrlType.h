#ifndef _ROS_SERVICE_SetCtrlType_h
#define _ROS_SERVICE_SetCtrlType_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mav_srvs
{

static const char SETCTRLTYPE[] = "mav_srvs/SetCtrlType";

  class SetCtrlTypeRequest : public ros::Msg
  {
    public:
      typedef uint8_t _ctrl_type_type;
      _ctrl_type_type ctrl_type;

    SetCtrlTypeRequest():
      ctrl_type(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->ctrl_type >> (8 * 0)) & 0xFF;
      offset += sizeof(this->ctrl_type);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->ctrl_type =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->ctrl_type);
     return offset;
    }

    const char * getType(){ return SETCTRLTYPE; };
    const char * getMD5(){ return "edf3553e2c2fb06a103b49edfc9846de"; };

  };

  class SetCtrlTypeResponse : public ros::Msg
  {
    public:

    SetCtrlTypeResponse()
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

    const char * getType(){ return SETCTRLTYPE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class SetCtrlType {
    public:
    typedef SetCtrlTypeRequest Request;
    typedef SetCtrlTypeResponse Response;
  };

}
#endif
