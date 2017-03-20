#ifndef _ROS_capabilities_CapabilityEvent_h
#define _ROS_capabilities_CapabilityEvent_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace capabilities
{

  class CapabilityEvent : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef const char* _capability_type;
      _capability_type capability;
      typedef const char* _provider_type;
      _provider_type provider;
      typedef const char* _type_type;
      _type_type type;
      typedef int32_t _pid_type;
      _pid_type pid;
      enum { LAUNCHED = "launched" };
      enum { STOPPED = "stopped" };
      enum { TERMINATED = "terminated" };
      enum { SERVER_READY = "server_ready" };

    CapabilityEvent():
      header(),
      capability(""),
      provider(""),
      type(""),
      pid(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
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
      uint32_t length_type = strlen(this->type);
      varToArr(outbuffer + offset, length_type);
      offset += 4;
      memcpy(outbuffer + offset, this->type, length_type);
      offset += length_type;
      union {
        int32_t real;
        uint32_t base;
      } u_pid;
      u_pid.real = this->pid;
      *(outbuffer + offset + 0) = (u_pid.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pid.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pid.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pid.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pid);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
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
      uint32_t length_type;
      arrToVar(length_type, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_type-1]=0;
      this->type = (char *)(inbuffer + offset-1);
      offset += length_type;
      union {
        int32_t real;
        uint32_t base;
      } u_pid;
      u_pid.base = 0;
      u_pid.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pid.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pid.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pid.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pid = u_pid.real;
      offset += sizeof(this->pid);
     return offset;
    }

    const char * getType(){ return "capabilities/CapabilityEvent"; };
    const char * getMD5(){ return "5a0d82ee1a8e7a5d0b058f0b20305b18"; };

  };

}
#endif