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
      uint8_t co2_sources_length;
      stdr_msgs::CO2Source st_co2_sources;
      stdr_msgs::CO2Source * co2_sources;

    CO2SourceVector():
      co2_sources_length(0), co2_sources(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = co2_sources_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < co2_sources_length; i++){
      offset += this->co2_sources[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t co2_sources_lengthT = *(inbuffer + offset++);
      if(co2_sources_lengthT > co2_sources_length)
        this->co2_sources = (stdr_msgs::CO2Source*)realloc(this->co2_sources, co2_sources_lengthT * sizeof(stdr_msgs::CO2Source));
      offset += 3;
      co2_sources_length = co2_sources_lengthT;
      for( uint8_t i = 0; i < co2_sources_length; i++){
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