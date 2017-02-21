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
      uint8_t running_capabilities_length;
      capabilities::RunningCapability st_running_capabilities;
      capabilities::RunningCapability * running_capabilities;

    GetRunningCapabilitiesResponse():
      running_capabilities_length(0), running_capabilities(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = running_capabilities_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < running_capabilities_length; i++){
      offset += this->running_capabilities[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t running_capabilities_lengthT = *(inbuffer + offset++);
      if(running_capabilities_lengthT > running_capabilities_length)
        this->running_capabilities = (capabilities::RunningCapability*)realloc(this->running_capabilities, running_capabilities_lengthT * sizeof(capabilities::RunningCapability));
      offset += 3;
      running_capabilities_length = running_capabilities_lengthT;
      for( uint8_t i = 0; i < running_capabilities_length; i++){
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
