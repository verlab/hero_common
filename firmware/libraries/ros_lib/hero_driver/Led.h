#ifndef _ROS_hero_driver_Led_h
#define _ROS_hero_driver_Led_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace hero_driver
{

  class Led : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef int8_t _R_type;
      _R_type R;
      typedef int8_t _G_type;
      _G_type G;
      typedef int8_t _B_type;
      _B_type B;

    Led():
      header(),
      R(0),
      G(0),
      B(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        int8_t real;
        uint8_t base;
      } u_R;
      u_R.real = this->R;
      *(outbuffer + offset + 0) = (u_R.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->R);
      union {
        int8_t real;
        uint8_t base;
      } u_G;
      u_G.real = this->G;
      *(outbuffer + offset + 0) = (u_G.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->G);
      union {
        int8_t real;
        uint8_t base;
      } u_B;
      u_B.real = this->B;
      *(outbuffer + offset + 0) = (u_B.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->B);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        int8_t real;
        uint8_t base;
      } u_R;
      u_R.base = 0;
      u_R.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->R = u_R.real;
      offset += sizeof(this->R);
      union {
        int8_t real;
        uint8_t base;
      } u_G;
      u_G.base = 0;
      u_G.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->G = u_G.real;
      offset += sizeof(this->G);
      union {
        int8_t real;
        uint8_t base;
      } u_B;
      u_B.base = 0;
      u_B.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->B = u_B.real;
      offset += sizeof(this->B);
     return offset;
    }

    const char * getType(){ return "hero_driver/Led"; };
    const char * getMD5(){ return "4751d692cf3908f97bf333ba494fdd42"; };

  };

}
#endif