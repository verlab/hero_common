#ifndef _ROS_swarm_driver_Proximity_h
#define _ROS_swarm_driver_Proximity_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace swarm_driver
{

  class Proximity : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef int8_t _proximity_1_type;
      _proximity_1_type proximity_1;
      typedef int8_t _proximity_2_type;
      _proximity_2_type proximity_2;
      typedef int8_t _proximity_3_type;
      _proximity_3_type proximity_3;

    Proximity():
      header(),
      proximity_1(0),
      proximity_2(0),
      proximity_3(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        int8_t real;
        uint8_t base;
      } u_proximity_1;
      u_proximity_1.real = this->proximity_1;
      *(outbuffer + offset + 0) = (u_proximity_1.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->proximity_1);
      union {
        int8_t real;
        uint8_t base;
      } u_proximity_2;
      u_proximity_2.real = this->proximity_2;
      *(outbuffer + offset + 0) = (u_proximity_2.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->proximity_2);
      union {
        int8_t real;
        uint8_t base;
      } u_proximity_3;
      u_proximity_3.real = this->proximity_3;
      *(outbuffer + offset + 0) = (u_proximity_3.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->proximity_3);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        int8_t real;
        uint8_t base;
      } u_proximity_1;
      u_proximity_1.base = 0;
      u_proximity_1.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->proximity_1 = u_proximity_1.real;
      offset += sizeof(this->proximity_1);
      union {
        int8_t real;
        uint8_t base;
      } u_proximity_2;
      u_proximity_2.base = 0;
      u_proximity_2.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->proximity_2 = u_proximity_2.real;
      offset += sizeof(this->proximity_2);
      union {
        int8_t real;
        uint8_t base;
      } u_proximity_3;
      u_proximity_3.base = 0;
      u_proximity_3.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->proximity_3 = u_proximity_3.real;
      offset += sizeof(this->proximity_3);
     return offset;
    }

    const char * getType(){ return "swarm_driver/Proximity"; };
    const char * getMD5(){ return "ca615114cb10fd248647854f18d9858e"; };

  };

}
#endif