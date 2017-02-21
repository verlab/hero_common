#ifndef _ROS_p2os_msgs_AIO_h
#define _ROS_p2os_msgs_AIO_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace p2os_msgs
{

  class AIO : public ros::Msg
  {
    public:
      uint8_t voltages_count;
      uint8_t voltages_length;
      float st_voltages;
      float * voltages;

    AIO():
      voltages_count(0),
      voltages_length(0), voltages(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->voltages_count >> (8 * 0)) & 0xFF;
      offset += sizeof(this->voltages_count);
      *(outbuffer + offset++) = voltages_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < voltages_length; i++){
      union {
        float real;
        uint32_t base;
      } u_voltagesi;
      u_voltagesi.real = this->voltages[i];
      *(outbuffer + offset + 0) = (u_voltagesi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_voltagesi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_voltagesi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_voltagesi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->voltages[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->voltages_count =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->voltages_count);
      uint8_t voltages_lengthT = *(inbuffer + offset++);
      if(voltages_lengthT > voltages_length)
        this->voltages = (float*)realloc(this->voltages, voltages_lengthT * sizeof(float));
      offset += 3;
      voltages_length = voltages_lengthT;
      for( uint8_t i = 0; i < voltages_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_voltages;
      u_st_voltages.base = 0;
      u_st_voltages.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_voltages.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_voltages.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_voltages.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_voltages = u_st_voltages.real;
      offset += sizeof(this->st_voltages);
        memcpy( &(this->voltages[i]), &(this->st_voltages), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "p2os_msgs/AIO"; };
    const char * getMD5(){ return "80e4ca5770a3db29064af246946ff4fe"; };

  };

}
#endif