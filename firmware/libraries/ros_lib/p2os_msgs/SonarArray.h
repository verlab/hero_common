#ifndef _ROS_p2os_msgs_SonarArray_h
#define _ROS_p2os_msgs_SonarArray_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace p2os_msgs
{

  class SonarArray : public ros::Msg
  {
    public:
      std_msgs::Header header;
      int32_t ranges_count;
      uint8_t ranges_length;
      float st_ranges;
      float * ranges;

    SonarArray():
      header(),
      ranges_count(0),
      ranges_length(0), ranges(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_ranges_count;
      u_ranges_count.real = this->ranges_count;
      *(outbuffer + offset + 0) = (u_ranges_count.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ranges_count.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ranges_count.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ranges_count.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ranges_count);
      *(outbuffer + offset++) = ranges_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < ranges_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->ranges[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_ranges_count;
      u_ranges_count.base = 0;
      u_ranges_count.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ranges_count.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ranges_count.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ranges_count.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ranges_count = u_ranges_count.real;
      offset += sizeof(this->ranges_count);
      uint8_t ranges_lengthT = *(inbuffer + offset++);
      if(ranges_lengthT > ranges_length)
        this->ranges = (float*)realloc(this->ranges, ranges_lengthT * sizeof(float));
      offset += 3;
      ranges_length = ranges_lengthT;
      for( uint8_t i = 0; i < ranges_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_ranges));
        memcpy( &(this->ranges[i]), &(this->st_ranges), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "p2os_msgs/SonarArray"; };
    const char * getMD5(){ return "2984921c09aef26ad253c7629937a5bb"; };

  };

}
#endif