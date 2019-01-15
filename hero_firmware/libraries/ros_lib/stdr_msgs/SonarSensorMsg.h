#ifndef _ROS_stdr_msgs_SonarSensorMsg_h
#define _ROS_stdr_msgs_SonarSensorMsg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "stdr_msgs/Noise.h"
#include "geometry_msgs/Pose2D.h"

namespace stdr_msgs
{

  class SonarSensorMsg : public ros::Msg
  {
    public:
      typedef float _maxRange_type;
      _maxRange_type maxRange;
      typedef float _minRange_type;
      _minRange_type minRange;
      typedef float _coneAngle_type;
      _coneAngle_type coneAngle;
      typedef float _frequency_type;
      _frequency_type frequency;
      typedef stdr_msgs::Noise _noise_type;
      _noise_type noise;
      typedef const char* _frame_id_type;
      _frame_id_type frame_id;
      typedef geometry_msgs::Pose2D _pose_type;
      _pose_type pose;

    SonarSensorMsg():
      maxRange(0),
      minRange(0),
      coneAngle(0),
      frequency(0),
      noise(),
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
      } u_minRange;
      u_minRange.real = this->minRange;
      *(outbuffer + offset + 0) = (u_minRange.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_minRange.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_minRange.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_minRange.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->minRange);
      union {
        float real;
        uint32_t base;
      } u_coneAngle;
      u_coneAngle.real = this->coneAngle;
      *(outbuffer + offset + 0) = (u_coneAngle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_coneAngle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_coneAngle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_coneAngle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->coneAngle);
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
      offset += this->noise.serialize(outbuffer + offset);
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
      } u_minRange;
      u_minRange.base = 0;
      u_minRange.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_minRange.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_minRange.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_minRange.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->minRange = u_minRange.real;
      offset += sizeof(this->minRange);
      union {
        float real;
        uint32_t base;
      } u_coneAngle;
      u_coneAngle.base = 0;
      u_coneAngle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_coneAngle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_coneAngle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_coneAngle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->coneAngle = u_coneAngle.real;
      offset += sizeof(this->coneAngle);
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
      offset += this->noise.deserialize(inbuffer + offset);
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

    const char * getType(){ return "stdr_msgs/SonarSensorMsg"; };
    const char * getMD5(){ return "e8b8bd75b2e357572ea0c9ee72ed58c1"; };

  };

}
#endif