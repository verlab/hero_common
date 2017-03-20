#ifndef _ROS_kobuki_msgs_DigitalOutput_h
#define _ROS_kobuki_msgs_DigitalOutput_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace kobuki_msgs
{

  class DigitalOutput : public ros::Msg
  {
    public:
      bool values[4];
      bool mask[4];

    DigitalOutput():
      values(),
      mask()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 4; i++){
      union {
        bool real;
        uint8_t base;
      } u_valuesi;
      u_valuesi.real = this->values[i];
      *(outbuffer + offset + 0) = (u_valuesi.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->values[i]);
      }
      for( uint32_t i = 0; i < 4; i++){
      union {
        bool real;
        uint8_t base;
      } u_maski;
      u_maski.real = this->mask[i];
      *(outbuffer + offset + 0) = (u_maski.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->mask[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 4; i++){
      union {
        bool real;
        uint8_t base;
      } u_valuesi;
      u_valuesi.base = 0;
      u_valuesi.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->values[i] = u_valuesi.real;
      offset += sizeof(this->values[i]);
      }
      for( uint32_t i = 0; i < 4; i++){
      union {
        bool real;
        uint8_t base;
      } u_maski;
      u_maski.base = 0;
      u_maski.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->mask[i] = u_maski.real;
      offset += sizeof(this->mask[i]);
      }
     return offset;
    }

    const char * getType(){ return "kobuki_msgs/DigitalOutput"; };
    const char * getMD5(){ return "1e97cd7f196a0270516b506e8bf29ca2"; };

  };

}
#endif