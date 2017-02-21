#ifndef _ROS_SERVICE_ChangeDesPose_h
#define _ROS_SERVICE_ChangeDesPose_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mav_srvs
{

static const char CHANGEDESPOSE[] = "mav_srvs/ChangeDesPose";

  class ChangeDesPoseRequest : public ros::Msg
  {
    public:
      float delta_x;
      float delta_y;
      float delta_z;
      float delta_yaw;

    ChangeDesPoseRequest():
      delta_x(0),
      delta_y(0),
      delta_z(0),
      delta_yaw(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->delta_x);
      offset += serializeAvrFloat64(outbuffer + offset, this->delta_y);
      offset += serializeAvrFloat64(outbuffer + offset, this->delta_z);
      offset += serializeAvrFloat64(outbuffer + offset, this->delta_yaw);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->delta_x));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->delta_y));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->delta_z));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->delta_yaw));
     return offset;
    }

    const char * getType(){ return CHANGEDESPOSE; };
    const char * getMD5(){ return "d7fc6ebd227f042943398b515a57e14f"; };

  };

  class ChangeDesPoseResponse : public ros::Msg
  {
    public:

    ChangeDesPoseResponse()
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

    const char * getType(){ return CHANGEDESPOSE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class ChangeDesPose {
    public:
    typedef ChangeDesPoseRequest Request;
    typedef ChangeDesPoseResponse Response;
  };

}
#endif
