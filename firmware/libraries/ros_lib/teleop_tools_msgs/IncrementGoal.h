#ifndef _ROS_teleop_tools_msgs_IncrementGoal_h
#define _ROS_teleop_tools_msgs_IncrementGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace teleop_tools_msgs
{

  class IncrementGoal : public ros::Msg
  {
    public:
      uint8_t increment_by_length;
      float st_increment_by;
      float * increment_by;

    IncrementGoal():
      increment_by_length(0), increment_by(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = increment_by_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < increment_by_length; i++){
      union {
        float real;
        uint32_t base;
      } u_increment_byi;
      u_increment_byi.real = this->increment_by[i];
      *(outbuffer + offset + 0) = (u_increment_byi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_increment_byi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_increment_byi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_increment_byi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->increment_by[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t increment_by_lengthT = *(inbuffer + offset++);
      if(increment_by_lengthT > increment_by_length)
        this->increment_by = (float*)realloc(this->increment_by, increment_by_lengthT * sizeof(float));
      offset += 3;
      increment_by_length = increment_by_lengthT;
      for( uint8_t i = 0; i < increment_by_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_increment_by;
      u_st_increment_by.base = 0;
      u_st_increment_by.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_increment_by.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_increment_by.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_increment_by.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_increment_by = u_st_increment_by.real;
      offset += sizeof(this->st_increment_by);
        memcpy( &(this->increment_by[i]), &(this->st_increment_by), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "teleop_tools_msgs/IncrementGoal"; };
    const char * getMD5(){ return "6801194f49dae2bee5b8f17b6ce4596f"; };

  };

}
#endif