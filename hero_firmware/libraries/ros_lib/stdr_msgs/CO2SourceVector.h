#ifndef _ROS_stdr_msgs_CO2SourceVector_h
#define _ROS_stdr_msgs_CO2SourceVector_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "stdr_msgs/CO2Source.h"

namespace stdr_msgs
{

  class CO2SourceVector : public ros::Msg
  {
    public:
      uint32_t co2_sources_length;
      typedef stdr_msgs::CO2Source _co2_sources_type;
      _co2_sources_type st_co2_sources;
      _co2_sources_type * co2_sources;

    CO2SourceVector():
      co2_sources_length(0), co2_sources(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->co2_sources_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->co2_sources_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->co2_sources_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->co2_sources_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->co2_sources_length);
      for( uint32_t i = 0; i < co2_sources_length; i++){
      offset += this->co2_sources[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t co2_sources_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      co2_sources_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      co2_sources_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      co2_sources_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->co2_sources_length);
      if(co2_sources_lengthT > co2_sources_length)
        this->co2_sources = (stdr_msgs::CO2Source*)realloc(this->co2_sources, co2_sources_lengthT * sizeof(stdr_msgs::CO2Source));
      co2_sources_length = co2_sources_lengthT;
      for( uint32_t i = 0; i < co2_sources_length; i++){
      offset += this->st_co2_sources.deserialize(inbuffer + offset);
        memcpy( &(this->co2_sources[i]), &(this->st_co2_sources), sizeof(stdr_msgs::CO2Source));
      }
     return offset;
    }

    const char * getType(){ return "stdr_msgs/CO2SourceVector"; };
    const char * getMD5(){ return "5ded45505bc7155e81a2d6033817c7f3"; };

  };

}
#endif