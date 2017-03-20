#ifndef _ROS_SERVICE_GetRunningCapabilities_h
#define _ROS_SERVICE_GetRunningCapabilities_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "capabilities/RunningCapability.h"

namespace capabilities
{

static const char GETRUNNINGCAPABILITIES[] = "capabilities/GetRunningCapabilities";

  class GetRunningCapabilitiesRequest : public ros::Msg
  {
    public:

    GetRunningCapabilitiesRequest()
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

    const char * getType(){ return GETRUNNINGCAPABILITIES; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetRunningCapabilitiesResponse : public ros::Msg
  {
    public:
      uint32_t running_capabilities_length;
      typedef capabilities::RunningCapability _running_capabilities_type;
      _running_capabilities_type st_running_capabilities;
      _running_capabilities_type * running_capabilities;

    GetRunningCapabilitiesResponse():
      running_capabilities_length(0), running_capabilities(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->running_capabilities_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->running_capabilities_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->running_capabilities_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->running_capabilities_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->running_capabilities_length);
      for( uint32_t i = 0; i < running_capabilities_length; i++){
      offset += this->running_capabilities[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t running_capabilities_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      running_capabilities_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      running_capabilities_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      running_capabilities_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->running_capabilities_length);
      if(running_capabilities_lengthT > running_capabilities_length)
        this->running_capabilities = (capabilities::RunningCapability*)realloc(this->running_capabilities, running_capabilities_lengthT * sizeof(capabilities::RunningCapability));
      running_capabilities_length = running_capabilities_lengthT;
      for( uint32_t i = 0; i < running_capabilities_length; i++){
      offset += this->st_running_capabilities.deserialize(inbuffer + offset);
        memcpy( &(this->running_capabilities[i]), &(this->st_running_capabilities), sizeof(capabilities::RunningCapability));
      }
     return offset;
    }

    const char * getType(){ return GETRUNNINGCAPABILITIES; };
    const char * getMD5(){ return "e8e5cf68c34711ffaa719728f34ea7a3"; };

  };

  class GetRunningCapabilities {
    public:
    typedef GetRunningCapabilitiesRequest Request;
    typedef GetRunningCapabilitiesResponse Response;
  };

}
#endif
