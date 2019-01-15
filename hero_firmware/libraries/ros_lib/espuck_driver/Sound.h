#ifndef _ROS_espuck_driver_Sound_h
#define _ROS_espuck_driver_Sound_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace espuck_driver
{

  class Sound : public ros::Msg
  {
    public:
      typedef int8_t _index_type;
      _index_type index;

    Sound():
      index(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_index;
      u_index.real = this->index;
      *(outbuffer + offset + 0) = (u_index.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->index);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_index;
      u_index.base = 0;
      u_index.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->index = u_index.real;
      offset += sizeof(this->index);
     return offset;
    }

    const char * getType(){ return "espuck_driver/Sound"; };
    const char * getMD5(){ return "c4ecff52046eaecf0190e650b1958286"; };

  };

}
#endif