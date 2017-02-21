#ifndef _ROS_yocs_msgs_NavigateToGoal_h
#define _ROS_yocs_msgs_NavigateToGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace yocs_msgs
{

  class NavigateToGoal : public ros::Msg
  {
    public:
      const char* location;
      int8_t approach_type;
      int8_t num_retry;
      float timeout;
      float distance;
      enum { APPROACH_NEAR =  11 };
      enum { APPROACH_ON =  12 };

    NavigateToGoal():
      location(""),
      approach_type(0),
      num_retry(0),
      timeout(0),
      distance(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_location = strlen(this->location);
      memcpy(outbuffer + offset, &length_location, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->location, length_location);
      offset += length_location;
      union {
        int8_t real;
        uint8_t base;
      } u_approach_type;
      u_approach_type.real = this->approach_type;
      *(outbuffer + offset + 0) = (u_approach_type.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->approach_type);
      union {
        int8_t real;
        uint8_t base;
      } u_num_retry;
      u_num_retry.real = this->num_retry;
      *(outbuffer + offset + 0) = (u_num_retry.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->num_retry);
      union {
        float real;
        uint32_t base;
      } u_timeout;
      u_timeout.real = this->timeout;
      *(outbuffer + offset + 0) = (u_timeout.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_timeout.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_timeout.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_timeout.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->timeout);
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
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_location;
      memcpy(&length_location, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_location; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_location-1]=0;
      this->location = (char *)(inbuffer + offset-1);
      offset += length_location;
      union {
        int8_t real;
        uint8_t base;
      } u_approach_type;
      u_approach_type.base = 0;
      u_approach_type.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->approach_type = u_approach_type.real;
      offset += sizeof(this->approach_type);
      union {
        int8_t real;
        uint8_t base;
      } u_num_retry;
      u_num_retry.base = 0;
      u_num_retry.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->num_retry = u_num_retry.real;
      offset += sizeof(this->num_retry);
      union {
        float real;
        uint32_t base;
      } u_timeout;
      u_timeout.base = 0;
      u_timeout.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_timeout.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_timeout.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_timeout.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->timeout = u_timeout.real;
      offset += sizeof(this->timeout);
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
     return offset;
    }

    const char * getType(){ return "yocs_msgs/NavigateToGoal"; };
    const char * getMD5(){ return "1549bb00469af4886dd492a95637d796"; };

  };

}
#endif