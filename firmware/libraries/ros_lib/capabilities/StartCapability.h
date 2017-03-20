#ifndef _ROS_SERVICE_StartCapability_h
#define _ROS_SERVICE_StartCapability_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace capabilities
{

static const char STARTCAPABILITY[] = "capabilities/StartCapability";

  class StartCapabilityRequest : public ros::Msg
  {
    public:
      typedef const char* _capability_type;
      _capability_type capability;
      typedef const char* _preferred_provider_type;
      _preferred_provider_type preferred_provider;

    StartCapabilityRequest():
      capability(""),
      preferred_provider("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_capability = strlen(this->capability);
      varToArr(outbuffer + offset, length_capability);
      offset += 4;
      memcpy(outbuffer + offset, this->capability, length_capability);
      offset += length_capability;
      uint32_t length_preferred_provider = strlen(this->preferred_provider);
      varToArr(outbuffer + offset, length_preferred_provider);
      offset += 4;
      memcpy(outbuffer + offset, this->preferred_provider, length_preferred_provider);
      offset += length_preferred_provider;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_capability;
      arrToVar(length_capability, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_capability; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_capability-1]=0;
      this->capability = (char *)(inbuffer + offset-1);
      offset += length_capability;
      uint32_t length_preferred_provider;
      arrToVar(length_preferred_provider, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_preferred_provider; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_preferred_provider-1]=0;
      this->preferred_provider = (char *)(inbuffer + offset-1);
      offset += length_preferred_provider;
     return offset;
    }

    const char * getType(){ return STARTCAPABILITY; };
    const char * getMD5(){ return "2cc14acc01fae719c849d4ea89820c67"; };

  };

  class StartCapabilityResponse : public ros::Msg
  {
    public:
      typedef bool _successful_type;
      _successful_type successful;

    StartCapabilityResponse():
      successful(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_successful;
      u_successful.real = this->successful;
      *(outbuffer + offset + 0) = (u_successful.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->successful);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_successful;
      u_successful.base = 0;
      u_successful.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->successful = u_successful.real;
      offset += sizeof(this->successful);
     return offset;
    }

    const char * getType(){ return STARTCAPABILITY; };
    const char * getMD5(){ return "6ccdb752b565be6d250259ff3d0c7ea1"; };

  };

  class StartCapability {
    public:
    typedef StartCapabilityRequest Request;
    typedef StartCapabilityResponse Response;
  };

}
#endif
