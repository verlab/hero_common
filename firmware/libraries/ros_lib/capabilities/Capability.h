#ifndef _ROS_capabilities_Capability_h
#define _ROS_capabilities_Capability_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace capabilities
{

  class Capability : public ros::Msg
  {
    public:
      typedef const char* _capability_type;
      _capability_type capability;
      typedef const char* _provider_type;
      _provider_type provider;

    Capability():
      capability(""),
      provider("")
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
      uint32_t length_provider = strlen(this->provider);
      varToArr(outbuffer + offset, length_provider);
      offset += 4;
      memcpy(outbuffer + offset, this->provider, length_provider);
      offset += length_provider;
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
      uint32_t length_provider;
      arrToVar(length_provider, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_provider; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_provider-1]=0;
      this->provider = (char *)(inbuffer + offset-1);
      offset += length_provider;
     return offset;
    }

    const char * getType(){ return "capabilities/Capability"; };
    const char * getMD5(){ return "05f9dd41875315c324efdf915b0e33a9"; };

  };

}
#endif