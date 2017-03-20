#ifndef _ROS_SERVICE_UseCapability_h
#define _ROS_SERVICE_UseCapability_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace capabilities
{

static const char USECAPABILITY[] = "capabilities/UseCapability";

  class UseCapabilityRequest : public ros::Msg
  {
    public:
      typedef const char* _capability_type;
      _capability_type capability;
      typedef const char* _preferred_provider_type;
      _preferred_provider_type preferred_provider;
      typedef const char* _bond_id_type;
      _bond_id_type bond_id;

    UseCapabilityRequest():
      capability(""),
      preferred_provider(""),
      bond_id("")
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
      uint32_t length_bond_id = strlen(this->bond_id);
      varToArr(outbuffer + offset, length_bond_id);
      offset += 4;
      memcpy(outbuffer + offset, this->bond_id, length_bond_id);
      offset += length_bond_id;
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
      uint32_t length_bond_id;
      arrToVar(length_bond_id, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_bond_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_bond_id-1]=0;
      this->bond_id = (char *)(inbuffer + offset-1);
      offset += length_bond_id;
     return offset;
    }

    const char * getType(){ return USECAPABILITY; };
    const char * getMD5(){ return "d12bf387dc5fcdd1fb836406b703a384"; };

  };

  class UseCapabilityResponse : public ros::Msg
  {
    public:

    UseCapabilityResponse()
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

    const char * getType(){ return USECAPABILITY; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class UseCapability {
    public:
    typedef UseCapabilityRequest Request;
    typedef UseCapabilityResponse Response;
  };

}
#endif
