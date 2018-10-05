#ifndef _ROS_stdr_msgs_CO2SensorMsg_h
#define _ROS_stdr_msgs_CO2SensorMsg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose2D.h"

namespace stdr_msgs
{

  class CO2SensorMsg : public ros::Msg
  {
    public:
      typedef float _maxRange_type;
      _maxRange_type maxRange;
      typedef float _frequency_type;
      _frequency_type frequency;
      typedef const char* _frame_id_type;
      _frame_id_type frame_id;
      typedef geometry_msgs::Pose2D _pose_type;
      _pose_type pose;

    CO2SensorMsg():
      maxRange(0),
      frequency(0),
      frame_id(""),
      pose()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_maxRange;
      u_maxRange.real = this->maxRange;
      *(outbuffer + offset + 0) = (u_maxRange.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_maxRange.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_maxRange.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_maxRange.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->maxRange);
      union {
        float real;
        uint32_t base;
      } u_frequency;
      u_frequency.real = this->frequency;
      *(outbuffer + offset + 0) = (u_frequency.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_frequency.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_frequency.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_frequency.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->frequency);
      uint32_t length_frame_id = strlen(this->frame_id);
      varToArr(outbuffer + offset, length_frame_id);
      offset += 4;
      memcpy(outbuffer + offset, this->frame_id, length_frame_id);
      offset += length_frame_id;
      offset += this->pose.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_maxRange;
      u_maxRange.base = 0;
      u_maxRange.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_maxRange.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_maxRange.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_maxRange.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->maxRange = u_maxRange.real;
      offset += sizeof(this->maxRange);
      union {
        float real;
        uint32_t base;
      } u_frequency;
      u_frequency.base = 0;
      u_frequency.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_frequency.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_frequency.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_frequency.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->frequency = u_frequency.real;
      offset += sizeof(this->frequency);
      uint32_t length_frame_id;
      arrToVar(length_frame_id, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_frame_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_frame_id-1]=0;
      this->frame_id = (char *)(inbuffer + offset-1);
      offset += length_frame_id;
      offset += this->pose.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "stdr_msgs/CO2SensorMsg"; };
    const char * getMD5(){ return "a2ce066e5e102e00628fbb7d1ee5e32b"; };

  };

}
#endif