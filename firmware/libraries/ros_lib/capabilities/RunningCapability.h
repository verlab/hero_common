#ifndef _ROS_capabilities_RunningCapability_h
#define _ROS_capabilities_RunningCapability_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "capabilities/Capability.h"

namespace capabilities
{

  class RunningCapability : public ros::Msg
  {
    public:
      capabilities::Capability capability;
      uint8_t dependent_capabilities_length;
      capabilities::Capability st_dependent_capabilities;
      capabilities::Capability * dependent_capabilities;
      const char* started_by;
      int32_t pid;

    RunningCapability():
      capability(),
      dependent_capabilities_length(0), dependent_capabilities(NULL),
      started_by(""),
      pid(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->capability.serialize(outbuffer + offset);
      *(outbuffer + offset++) = dependent_capabilities_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < dependent_capabilities_length; i++){
      offset += this->dependent_capabilities[i].serialize(outbuffer + offset);
      }
      uint32_t length_started_by = strlen(this->started_by);
      memcpy(outbuffer + offset, &length_started_by, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->started_by, length_started_by);
      offset += length_started_by;
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
      offset += this->capability.deserialize(inbuffer + offset);
      uint8_t dependent_capabilities_lengthT = *(inbuffer + offset++);
      if(dependent_capabilities_lengthT > dependent_capabilities_length)
        this->dependent_capabilities = (capabilities::Capability*)realloc(this->dependent_capabilities, dependent_capabilities_lengthT * sizeof(capabilities::Capability));
      offset += 3;
      dependent_capabilities_length = dependent_capabilities_lengthT;
      for( uint8_t i = 0; i < dependent_capabilities_length; i++){
      offset += this->st_dependent_capabilities.deserialize(inbuffer + offset);
        memcpy( &(this->dependent_capabilities[i]), &(this->st_dependent_capabilities), sizeof(capabilities::Capability));
      }
      uint32_t length_started_by;
      memcpy(&length_started_by, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_started_by; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_started_by-1]=0;
      this->started_by = (char *)(inbuffer + offset-1);
      offset += length_started_by;
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

    const char * getType(){ return "capabilities/RunningCapability"; };
    const char * getMD5(){ return "f97e2b23f907893008679ba2ff64fafc"; };

  };

}
#endif