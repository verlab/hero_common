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
      typedef capabilities::Capability _capability_type;
      _capability_type capability;
      uint32_t dependent_capabilities_length;
      typedef capabilities::Capability _dependent_capabilities_type;
      _dependent_capabilities_type st_dependent_capabilities;
      _dependent_capabilities_type * dependent_capabilities;
      typedef const char* _started_by_type;
      _started_by_type started_by;
      typedef int32_t _pid_type;
      _pid_type pid;

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
      *(outbuffer + offset + 0) = (this->dependent_capabilities_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->dependent_capabilities_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->dependent_capabilities_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->dependent_capabilities_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->dependent_capabilities_length);
      for( uint32_t i = 0; i < dependent_capabilities_length; i++){
      offset += this->dependent_capabilities[i].serialize(outbuffer + offset);
      }
      uint32_t length_started_by = strlen(this->started_by);
      varToArr(outbuffer + offset, length_started_by);
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
      uint32_t dependent_capabilities_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      dependent_capabilities_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      dependent_capabilities_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      dependent_capabilities_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->dependent_capabilities_length);
      if(dependent_capabilities_lengthT > dependent_capabilities_length)
        this->dependent_capabilities = (capabilities::Capability*)realloc(this->dependent_capabilities, dependent_capabilities_lengthT * sizeof(capabilities::Capability));
      dependent_capabilities_length = dependent_capabilities_lengthT;
      for( uint32_t i = 0; i < dependent_capabilities_length; i++){
      offset += this->st_dependent_capabilities.deserialize(inbuffer + offset);
        memcpy( &(this->dependent_capabilities[i]), &(this->st_dependent_capabilities), sizeof(capabilities::Capability));
      }
      uint32_t length_started_by;
      arrToVar(length_started_by, (inbuffer + offset));
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