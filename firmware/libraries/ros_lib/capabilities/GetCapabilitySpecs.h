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
      uint8_t capability_specs_length;
      capabilities::CapabilitySpec st_capability_specs;
      capabilities::CapabilitySpec * capability_specs;

    GetCapabilitySpecsResponse():
      capability_specs_length(0), capability_specs(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = capability_specs_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < capability_specs_length; i++){
      offset += this->capability_specs[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t capability_specs_lengthT = *(inbuffer + offset++);
      if(capability_specs_lengthT > capability_specs_length)
        this->capability_specs = (capabilities::CapabilitySpec*)realloc(this->capability_specs, capability_specs_lengthT * sizeof(capabilities::CapabilitySpec));
      offset += 3;
      capability_specs_length = capability_specs_lengthT;
      for( uint8_t i = 0; i < capability_specs_length; i++){
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
