#ifndef _ROS_SERVICE_ServiceResponseDetails_h
#define _ROS_SERVICE_ServiceResponseDetails_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rosapi/TypeDef.h"

namespace rosapi
{

static const char SERVICERESPONSEDETAILS[] = "rosapi/ServiceResponseDetails";

  class ServiceResponseDetailsRequest : public ros::Msg
  {
    public:
      typedef const char* _type_type;
      _type_type type;

    ServiceResponseDetailsRequest():
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

    const char * getType(){ return SERVICERESPONSEDETAILS; };
    const char * getMD5(){ return "dc67331de85cf97091b7d45e5c64ab75"; };

  };

  class ServiceResponseDetailsResponse : public ros::Msg
  {
    public:
      uint32_t typedefs_length;
      typedef rosapi::TypeDef _typedefs_type;
      _typedefs_type st_typedefs;
      _typedefs_type * typedefs;

    ServiceResponseDetailsResponse():
      typedefs_length(0), typedefs(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->typedefs_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->typedefs_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->typedefs_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->typedefs_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->typedefs_length);
      for( uint32_t i = 0; i < typedefs_length; i++){
      offset += this->typedefs[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t typedefs_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      typedefs_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      typedefs_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      typedefs_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->typedefs_length);
      if(typedefs_lengthT > typedefs_length)
        this->typedefs = (rosapi::TypeDef*)realloc(this->typedefs, typedefs_lengthT * sizeof(rosapi::TypeDef));
      typedefs_length = typedefs_lengthT;
      for( uint32_t i = 0; i < typedefs_length; i++){
      offset += this->st_typedefs.deserialize(inbuffer + offset);
        memcpy( &(this->typedefs[i]), &(this->st_typedefs), sizeof(rosapi::TypeDef));
      }
     return offset;
    }

    const char * getType(){ return SERVICERESPONSEDETAILS; };
    const char * getMD5(){ return "d088db0da260a2cde072246a5f577519"; };

  };

  class ServiceResponseDetails {
    public:
    typedef ServiceResponseDetailsRequest Request;
    typedef ServiceResponseDetailsResponse Response;
  };

}
#endif
