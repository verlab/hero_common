#ifndef _ROS_SERVICE_GetCapabilitySpecs_h
#define _ROS_SERVICE_GetCapabilitySpecs_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "capabilities/CapabilitySpec.h"

namespace capabilities
{

static const char GETCAPABILITYSPECS[] = "capabilities/GetCapabilitySpecs";

  class GetCapabilitySpecsRequest : public ros::Msg
  {
    public:

    GetCapabilitySpecsRequest()
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

    const char * getType(){ return GETCAPABILITYSPECS; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetCapabilitySpecsResponse : public ros::Msg
  {
    public:
      uint32_t capability_specs_length;
      typedef capabilities::CapabilitySpec _capability_specs_type;
      _capability_specs_type st_capability_specs;
      _capability_specs_type * capability_specs;

    GetCapabilitySpecsResponse():
      capability_specs_length(0), capability_specs(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->capability_specs_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->capability_specs_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->capability_specs_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->capability_specs_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->capability_specs_length);
      for( uint32_t i = 0; i < capability_specs_length; i++){
      offset += this->capability_specs[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t capability_specs_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      capability_specs_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      capability_specs_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      capability_specs_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->capability_specs_length);
      if(capability_specs_lengthT > capability_specs_length)
        this->capability_specs = (capabilities::CapabilitySpec*)realloc(this->capability_specs, capability_specs_lengthT * sizeof(capabilities::CapabilitySpec));
      capability_specs_length = capability_specs_lengthT;
      for( uint32_t i = 0; i < capability_specs_length; i++){
      offset += this->st_capability_specs.deserialize(inbuffer + offset);
        memcpy( &(this->capability_specs[i]), &(this->st_capability_specs), sizeof(capabilities::CapabilitySpec));
      }
     return offset;
    }

    const char * getType(){ return GETCAPABILITYSPECS; };
    const char * getMD5(){ return "70274a8d27cd41f8e0754661d97168f8"; };

  };

  class GetCapabilitySpecs {
    public:
    typedef GetCapabilitySpecsRequest Request;
    typedef GetCapabilitySpecsResponse Response;
  };

}
#endif
