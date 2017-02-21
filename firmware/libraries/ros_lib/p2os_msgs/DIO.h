#ifndef _ROS_p2os_msgs_DIO_h
#define _ROS_p2os_msgs_DIO_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace p2os_msgs
{

  class DIO : public ros::Msg
  {
    public:
      uint32_t count;
      uint16_t bits;

    DIO():
      count(0),
      bits(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->count >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->count >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->count >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->count >> (8 * 3)) & 0xFF;
      offset += sizeof(this->count);
      *(outbuffer + offset + 0) = (this->bits >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->bits >> (8 * 1)) & 0xFF;
      offset += sizeof(this->bits);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->count =  ((uint32_t) (*(inbuffer + offset)));
      this->count |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->count |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->count |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->count);
      this->bits =  ((uint16_t) (*(inbuffer + offset)));
      this->bits |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->bits);
     return offset;
    }

    const char * getType(){ return "p2os_msgs/DIO"; };
    const char * getMD5(){ return "d375575ab5b2233ab16927780da5f856"; };

  };

}
#endif