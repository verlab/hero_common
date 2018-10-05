#ifndef _ROS_SERVICE_AddCO2Source_h
#define _ROS_SERVICE_AddCO2Source_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "stdr_msgs/CO2Source.h"

namespace stdr_msgs
{

static const char ADDCO2SOURCE[] = "stdr_msgs/AddCO2Source";

  class AddCO2SourceRequest : public ros::Msg
  {
    public:
      typedef stdr_msgs::CO2Source _newSource_type;
      _newSource_type newSource;

    AddCO2SourceRequest():
      newSource()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->newSource.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->newSource.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return ADDCO2SOURCE; };
    const char * getMD5(){ return "7199b309078089de32dcffa91f18ebd0"; };

  };

  class AddCO2SourceResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;
      typedef const char* _message_type;
      _message_type message;

    AddCO2SourceResponse():
      success(0),
      message("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      uint32_t length_message = strlen(this->message);
      varToArr(outbuffer + offset, length_message);
      offset += 4;
      memcpy(outbuffer + offset, this->message, length_message);
      offset += length_message;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
      uint32_t length_message;
      arrToVar(length_message, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_message-1]=0;
      this->message = (char *)(inbuffer + offset-1);
      offset += length_message;
     return offset;
    }

    const char * getType(){ return ADDCO2SOURCE; };
    const char * getMD5(){ return "937c9679a518e3a18d831e57125ea522"; };

  };

  class AddCO2Source {
    public:
    typedef AddCO2SourceRequest Request;
    typedef AddCO2SourceResponse Response;
  };

}
#endif
