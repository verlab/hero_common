#ifndef _ROS_SERVICE_ServicesForType_h
#define _ROS_SERVICE_ServicesForType_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rosapi
{

static const char SERVICESFORTYPE[] = "rosapi/ServicesForType";

  class ServicesForTypeRequest : public ros::Msg
  {
    public:
      typedef const char* _type_type;
      _type_type type;

    ServicesForTypeRequest():
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

    const char * getType(){ return SERVICESFORTYPE; };
    const char * getMD5(){ return "dc67331de85cf97091b7d45e5c64ab75"; };

  };

  class ServicesForTypeResponse : public ros::Msg
  {
    public:
      uint32_t services_length;
      typedef char* _services_type;
      _services_type st_services;
      _services_type * services;

    ServicesForTypeResponse():
      services_length(0), services(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->services_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->services_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->services_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->services_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->services_length);
      for( uint32_t i = 0; i < services_length; i++){
      uint32_t length_servicesi = strlen(this->services[i]);
      varToArr(outbuffer + offset, length_servicesi);
      offset += 4;
      memcpy(outbuffer + offset, this->services[i], length_servicesi);
      offset += length_servicesi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t services_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      services_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      services_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      services_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->services_length);
      if(services_lengthT > services_length)
        this->services = (char**)realloc(this->services, services_lengthT * sizeof(char*));
      services_length = services_lengthT;
      for( uint32_t i = 0; i < services_length; i++){
      uint32_t length_st_services;
      arrToVar(length_st_services, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_services; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_services-1]=0;
      this->st_services = (char *)(inbuffer + offset-1);
      offset += length_st_services;
        memcpy( &(this->services[i]), &(this->st_services), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return SERVICESFORTYPE; };
    const char * getMD5(){ return "e44a7e7bcb900acadbcc28b132378f0c"; };

  };

  class ServicesForType {
    public:
    typedef ServicesForTypeRequest Request;
    typedef ServicesForTypeResponse Response;
  };

}
#endif
