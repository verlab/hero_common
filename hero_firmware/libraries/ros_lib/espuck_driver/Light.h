#ifndef _ROS_espuck_driver_Light_h
#define _ROS_espuck_driver_Light_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace espuck_driver
{

  class Light : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t ambient_light_length;
      typedef int16_t _ambient_light_type;
      _ambient_light_type st_ambient_light;
      _ambient_light_type * ambient_light;

    Light():
      header(),
      ambient_light_length(0), ambient_light(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->ambient_light_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->ambient_light_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->ambient_light_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->ambient_light_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ambient_light_length);
      for( uint32_t i = 0; i < ambient_light_length; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_ambient_lighti;
      u_ambient_lighti.real = this->ambient_light[i];
      *(outbuffer + offset + 0) = (u_ambient_lighti.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ambient_lighti.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->ambient_light[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t ambient_light_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      ambient_light_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      ambient_light_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      ambient_light_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->ambient_light_length);
      if(ambient_light_lengthT > ambient_light_length)
        this->ambient_light = (int16_t*)realloc(this->ambient_light, ambient_light_lengthT * sizeof(int16_t));
      ambient_light_length = ambient_light_lengthT;
      for( uint32_t i = 0; i < ambient_light_length; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_st_ambient_light;
      u_st_ambient_light.base = 0;
      u_st_ambient_light.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_ambient_light.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->st_ambient_light = u_st_ambient_light.real;
      offset += sizeof(this->st_ambient_light);
        memcpy( &(this->ambient_light[i]), &(this->st_ambient_light), sizeof(int16_t));
      }
     return offset;
    }

    const char * getType(){ return "espuck_driver/Light"; };
    const char * getMD5(){ return "2dc2c6954687665a168a25c9c88231f2"; };

  };

}
#endif