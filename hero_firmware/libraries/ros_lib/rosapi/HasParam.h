#ifndef _ROS_SERVICE_HasParam_h
#define _ROS_SERVICE_HasParam_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rosapi
{

static const char HASPARAM[] = "rosapi/HasParam";

  class HasParamRequest : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;

    HasParamRequest():
      name("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
     return offset;
    }

    const char * getType(){ return HASPARAM; };
    const char * getMD5(){ return "c1f3d28f1b044c871e6eff2e9fc3c667"; };

  };

  class HasParamResponse : public ros::Msg
  {
    public:
      typedef bool _exists_type;
      _exists_type exists;

    HasParamResponse():
      exists(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_exists;
      u_exists.real = this->exists;
      *(outbuffer + offset + 0) = (u_exists.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->exists);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_exists;
      u_exists.base = 0;
      u_exists.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->exists = u_exists.real;
      offset += sizeof(this->exists);
     return offset;
    }

    const char * getType(){ return HASPARAM; };
    const char * getMD5(){ return "e8c90de4adc1219c86af9c2874c0c1b5"; };

  };

  class HasParam {
    public:
    typedef HasParamRequest Request;
    typedef HasParamResponse Response;
  };

}
#endif
