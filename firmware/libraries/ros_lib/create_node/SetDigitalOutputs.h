#ifndef _ROS_SERVICE_SetDigitalOutputs_h
#define _ROS_SERVICE_SetDigitalOutputs_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace create_node
{

static const char SETDIGITALOUTPUTS[] = "create_node/SetDigitalOutputs";

  class SetDigitalOutputsRequest : public ros::Msg
  {
    public:
      typedef uint8_t _digital_out_0_type;
      _digital_out_0_type digital_out_0;
      typedef uint8_t _digital_out_1_type;
      _digital_out_1_type digital_out_1;
      typedef uint8_t _digital_out_2_type;
      _digital_out_2_type digital_out_2;

    SetDigitalOutputsRequest():
      digital_out_0(0),
      digital_out_1(0),
      digital_out_2(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->digital_out_0 >> (8 * 0)) & 0xFF;
      offset += sizeof(this->digital_out_0);
      *(outbuffer + offset + 0) = (this->digital_out_1 >> (8 * 0)) & 0xFF;
      offset += sizeof(this->digital_out_1);
      *(outbuffer + offset + 0) = (this->digital_out_2 >> (8 * 0)) & 0xFF;
      offset += sizeof(this->digital_out_2);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->digital_out_0 =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->digital_out_0);
      this->digital_out_1 =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->digital_out_1);
      this->digital_out_2 =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->digital_out_2);
     return offset;
    }

    const char * getType(){ return SETDIGITALOUTPUTS; };
    const char * getMD5(){ return "95ef1ce60d04abfe27bea339a6261f29"; };

  };

  class SetDigitalOutputsResponse : public ros::Msg
  {
    public:
      typedef bool _done_type;
      _done_type done;

    SetDigitalOutputsResponse():
      done(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_done;
      u_done.real = this->done;
      *(outbuffer + offset + 0) = (u_done.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->done);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_done;
      u_done.base = 0;
      u_done.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->done = u_done.real;
      offset += sizeof(this->done);
     return offset;
    }

    const char * getType(){ return SETDIGITALOUTPUTS; };
    const char * getMD5(){ return "89bb254424e4cffedbf494e7b0ddbfea"; };

  };

  class SetDigitalOutputs {
    public:
    typedef SetDigitalOutputsRequest Request;
    typedef SetDigitalOutputsResponse Response;
  };

}
#endif
