#ifndef _ROS_yocs_msgs_NavigateToFeedback_h
#define _ROS_yocs_msgs_NavigateToFeedback_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace yocs_msgs
{

  class NavigateToFeedback : public ros::Msg
  {
    public:
      const char* message;
      float distance;
      float remain_time;
      int8_t status;
      enum { STATUS_RETRY =  21 };
      enum { STATUS_INPROGRESS =  22 };
      enum { STATUS_ERROR =  23 };

    NavigateToFeedback():
      message(""),
      distance(0),
      remain_time(0),
      status(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_message = strlen(this->message);
      memcpy(outbuffer + offset, &length_message, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->message, length_message);
      offset += length_message;
      union {
        float real;
        uint32_t base;
      } u_distance;
      u_distance.real = this->distance;
      *(outbuffer + offset + 0) = (u_distance.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_distance.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_distance.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_distance.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->distance);
      union {
        float real;
        uint32_t base;
      } u_remain_time;
      u_remain_time.real = this->remain_time;
      *(outbuffer + offset + 0) = (u_remain_time.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_remain_time.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_remain_time.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_remain_time.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->remain_time);
      union {
        int8_t real;
        uint8_t base;
      } u_status;
      u_status.real = this->status;
      *(outbuffer + offset + 0) = (u_status.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->status);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_message;
      memcpy(&length_message, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_message-1]=0;
      this->message = (char *)(inbuffer + offset-1);
      offset += length_message;
      union {
        float real;
        uint32_t base;
      } u_distance;
      u_distance.base = 0;
      u_distance.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_distance.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_distance.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_distance.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->distance = u_distance.real;
      offset += sizeof(this->distance);
      union {
        float real;
        uint32_t base;
      } u_remain_time;
      u_remain_time.base = 0;
      u_remain_time.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_remain_time.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_remain_time.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_remain_time.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->remain_time = u_remain_time.real;
      offset += sizeof(this->remain_time);
      union {
        int8_t real;
        uint8_t base;
      } u_status;
      u_status.base = 0;
      u_status.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->status = u_status.real;
      offset += sizeof(this->status);
     return offset;
    }

    const char * getType(){ return "yocs_msgs/NavigateToFeedback"; };
    const char * getMD5(){ return "b7dbba42e365116e557ccba16fa0414a"; };

  };

}
#endif