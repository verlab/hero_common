#ifndef _ROS_stdr_msgs_ThermalSourceVector_h
#define _ROS_stdr_msgs_ThermalSourceVector_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "stdr_msgs/ThermalSource.h"

namespace stdr_msgs
{

  class ThermalSourceVector : public ros::Msg
  {
    public:
      uint32_t thermal_sources_length;
      typedef stdr_msgs::ThermalSource _thermal_sources_type;
      _thermal_sources_type st_thermal_sources;
      _thermal_sources_type * thermal_sources;

    ThermalSourceVector():
      thermal_sources_length(0), thermal_sources(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->thermal_sources_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->thermal_sources_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->thermal_sources_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->thermal_sources_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->thermal_sources_length);
      for( uint32_t i = 0; i < thermal_sources_length; i++){
      offset += this->thermal_sources[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t thermal_sources_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      thermal_sources_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      thermal_sources_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      thermal_sources_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->thermal_sources_length);
      if(thermal_sources_lengthT > thermal_sources_length)
        this->thermal_sources = (stdr_msgs::ThermalSource*)realloc(this->thermal_sources, thermal_sources_lengthT * sizeof(stdr_msgs::ThermalSource));
      thermal_sources_length = thermal_sources_lengthT;
      for( uint32_t i = 0; i < thermal_sources_length; i++){
      offset += this->st_thermal_sources.deserialize(inbuffer + offset);
        memcpy( &(this->thermal_sources[i]), &(this->st_thermal_sources), sizeof(stdr_msgs::ThermalSource));
      }
     return offset;
    }

    const char * getType(){ return "stdr_msgs/ThermalSourceVector"; };
    const char * getMD5(){ return "dddbbf1cf2eb1ad9e8f6f398fb8b44ac"; };

  };

}
#endif