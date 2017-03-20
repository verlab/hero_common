#ifndef _ROS_SERVICE_GetCapabilitySpec_h
#define _ROS_SERVICE_GetCapabilitySpec_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "capabilities/CapabilitySpec.h"

namespace capabilities
{

static const char GETCAPABILITYSPEC[] = "capabilities/GetCapabilitySpec";

  class GetCapabilitySpecRequest : public ros::Msg
  {
    public:
      typedef const char* _capability_spec_type;
      _capability_spec_type capability_spec;

    GetCapabilitySpecRequest():
      capability_spec("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_capability_spec = strlen(this->capability_spec);
      varToArr(outbuffer + offset, length_capability_spec);
      offset += 4;
      memcpy(outbuffer + offset, this->capability_spec, length_capability_spec);
      offset += length_capability_spec;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_capability_spec;
      arrToVar(length_capability_spec, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_capability_spec; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_capability_spec-1]=0;
      this->capability_spec = (char *)(inbuffer + offset-1);
      offset += length_capability_spec;
     return offset;
    }

    const char * getType(){ return GETCAPABILITYSPEC; };
    const char * getMD5(){ return "0d24c4211d85e38f4c925c9fe87cce03"; };

  };

  class GetCapabilitySpecResponse : public ros::Msg
  {
    public:
      typedef capabilities::CapabilitySpec _capability_spec_type;
      _capability_spec_type capability_spec;

    GetCapabilitySpecResponse():
      capability_spec()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->capability_spec.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->capability_spec.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return GETCAPABILITYSPEC; };
    const char * getMD5(){ return "0144e716993364573443fef8a936aef2"; };

  };

  class GetCapabilitySpec {
    public:
    typedef GetCapabilitySpecRequest Request;
    typedef GetCapabilitySpecResponse Response;
  };

}
#endif
