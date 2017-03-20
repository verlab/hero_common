#ifndef _ROS_SERVICE_StopCapability_h
#define _ROS_SERVICE_StopCapability_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace capabilities
{

static const char STOPCAPABILITY[] = "capabilities/StopCapability";

  class StopCapabilityRequest : public ros::Msg
  {
    public:
      typedef const char* _capability_type;
      _capability_type capability;

    StopCapabilityRequest():
      capability("")
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
     return offset;
    }

    const char * getType(){ return STOPCAPABILITY; };
    const char * getMD5(){ return "e0d1dd20c6cc3fed63f3710228856be9"; };

  };

  class StopCapabilityResponse : public ros::Msg
  {
    public:
      typedef bool _successful_type;
      _successful_type successful;

    StopCapabilityResponse():
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

    const char * getType(){ return STOPCAPABILITY; };
    const char * getMD5(){ return "6ccdb752b565be6d250259ff3d0c7ea1"; };

  };

  class StopCapability {
    public:
    typedef StopCapabilityRequest Request;
    typedef StopCapabilityResponse Response;
  };

}
#endif
