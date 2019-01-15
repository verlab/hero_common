#ifndef _ROS_espuck_driver_Temperature_h
#define _ROS_espuck_driver_Temperature_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace espuck_driver
{

  class Temperature : public ros::Msg
  {
    public:
      typedef int8_t _temp_type;
      _temp_type temp;

    Temperature():
      temp(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_temp;
      u_temp.real = this->temp;
      *(outbuffer + offset + 0) = (u_temp.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->temp);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_temp;
      u_temp.base = 0;
      u_temp.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->temp = u_temp.real;
      offset += sizeof(this->temp);
     return offset;
    }

    const char * getType(){ return "espuck_driver/Temperature"; };
    const char * getMD5(){ return "dd3d89b4162a8b8c4f9f08c084f821bd"; };

  };

}
#endif