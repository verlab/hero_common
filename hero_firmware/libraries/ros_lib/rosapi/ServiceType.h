#ifndef _ROS_SERVICE_ServiceType_h
#define _ROS_SERVICE_ServiceType_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rosapi
{

static const char SERVICETYPE[] = "rosapi/ServiceType";

  class ServiceTypeRequest : public ros::Msg
  {
    public:
      typedef const char* _service_type;
      _service_type service;

    ServiceTypeRequest():
      service("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_service = strlen(this->service);
      varToArr(outbuffer + offset, length_service);
      offset += 4;
      memcpy(outbuffer + offset, this->service, length_service);
      offset += length_service;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_service;
      arrToVar(length_service, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_service; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_service-1]=0;
      this->service = (char *)(inbuffer + offset-1);
      offset += length_service;
     return offset;
    }

    const char * getType(){ return SERVICETYPE; };
    const char * getMD5(){ return "1cbcfa13b08f6d36710b9af8741e6112"; };

  };

  class ServiceTypeResponse : public ros::Msg
  {
    public:
      typedef const char* _type_type;
      _type_type type;

    ServiceTypeResponse():
      type("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_type = strlen(this->type);
      varToArr(outbuffer + offset, length_type);
      offset += 4;
      memcpy(outbuffer + offset, this->type, length_type);
      offset += length_type;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_type;
      arrToVar(length_type, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_type-1]=0;
      this->type = (char *)(inbuffer + offset-1);
      offset += length_type;
     return offset;
    }

    const char * getType(){ return SERVICETYPE; };
    const char * getMD5(){ return "dc67331de85cf97091b7d45e5c64ab75"; };

  };

  class ServiceType {
    public:
    typedef ServiceTypeRequest Request;
    typedef ServiceTypeResponse Response;
  };

}
#endif
