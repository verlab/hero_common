#ifndef _ROS_SERVICE_FreeCapability_h
#define _ROS_SERVICE_FreeCapability_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace capabilities
{

static const char FREECAPABILITY[] = "capabilities/FreeCapability";

  class FreeCapabilityRequest : public ros::Msg
  {
    public:
      const char* capability;
      const char* bond_id;

    FreeCapabilityRequest():
      capability(""),
      bond_id("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_capability = strlen(this->capability);
      memcpy(outbuffer + offset, &length_capability, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->capability, length_capability);
      offset += length_capability;
      uint32_t length_bond_id = strlen(this->bond_id);
      memcpy(outbuffer + offset, &length_bond_id, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->bond_id, length_bond_id);
      offset += length_bond_id;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_capability;
      memcpy(&length_capability, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_capability; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_capability-1]=0;
      this->capability = (char *)(inbuffer + offset-1);
      offset += length_capability;
      uint32_t length_bond_id;
      memcpy(&length_bond_id, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_bond_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_bond_id-1]=0;
      this->bond_id = (char *)(inbuffer + offset-1);
      offset += length_bond_id;
     return offset;
    }

    const char * getType(){ return FREECAPABILITY; };
    const char * getMD5(){ return "a428ffea976541636efe63c8605fd3ec"; };

  };

  class FreeCapabilityResponse : public ros::Msg
  {
    public:

    FreeCapabilityResponse()
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

    const char * getType(){ return FREECAPABILITY; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class FreeCapability {
    public:
    typedef FreeCapabilityRequest Request;
    typedef FreeCapabilityResponse Response;
  };

}
#endif
