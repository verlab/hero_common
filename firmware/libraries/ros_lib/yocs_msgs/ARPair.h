#ifndef _ROS_yocs_msgs_ARPair_h
#define _ROS_yocs_msgs_ARPair_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace yocs_msgs
{

  class ARPair : public ros::Msg
  {
    public:
      int16_t left_id;
      int16_t right_id;
      float baseline;
      float target_offset;
      const char* target_frame;

    ARPair():
      left_id(0),
      right_id(0),
      baseline(0),
      target_offset(0),
      target_frame("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_left_id;
      u_left_id.real = this->left_id;
      *(outbuffer + offset + 0) = (u_left_id.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_left_id.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->left_id);
      union {
        int16_t real;
        uint16_t base;
      } u_right_id;
      u_right_id.real = this->right_id;
      *(outbuffer + offset + 0) = (u_right_id.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_right_id.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->right_id);
      union {
        float real;
        uint32_t base;
      } u_baseline;
      u_baseline.real = this->baseline;
      *(outbuffer + offset + 0) = (u_baseline.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_baseline.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_baseline.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_baseline.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->baseline);
      union {
        float real;
        uint32_t base;
      } u_target_offset;
      u_target_offset.real = this->target_offset;
      *(outbuffer + offset + 0) = (u_target_offset.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_target_offset.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_target_offset.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_target_offset.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->target_offset);
      uint32_t length_target_frame = strlen(this->target_frame);
      memcpy(outbuffer + offset, &length_target_frame, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->target_frame, length_target_frame);
      offset += length_target_frame;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_left_id;
      u_left_id.base = 0;
      u_left_id.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_left_id.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->left_id = u_left_id.real;
      offset += sizeof(this->left_id);
      union {
        int16_t real;
        uint16_t base;
      } u_right_id;
      u_right_id.base = 0;
      u_right_id.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_right_id.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->right_id = u_right_id.real;
      offset += sizeof(this->right_id);
      union {
        float real;
        uint32_t base;
      } u_baseline;
      u_baseline.base = 0;
      u_baseline.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_baseline.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_baseline.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_baseline.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->baseline = u_baseline.real;
      offset += sizeof(this->baseline);
      union {
        float real;
        uint32_t base;
      } u_target_offset;
      u_target_offset.base = 0;
      u_target_offset.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_target_offset.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_target_offset.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_target_offset.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->target_offset = u_target_offset.real;
      offset += sizeof(this->target_offset);
      uint32_t length_target_frame;
      memcpy(&length_target_frame, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_target_frame; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_target_frame-1]=0;
      this->target_frame = (char *)(inbuffer + offset-1);
      offset += length_target_frame;
     return offset;
    }

    const char * getType(){ return "yocs_msgs/ARPair"; };
    const char * getMD5(){ return "9a0e51fbcb2eab37a945707af8ee9a6b"; };

  };

}
#endif