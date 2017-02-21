#ifndef _ROS_mavros_msgs_HilActuatorControls_h
#define _ROS_mavros_msgs_HilActuatorControls_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace mavros_msgs
{

  class HilActuatorControls : public ros::Msg
  {
    public:
      std_msgs::Header header;
      float controls[16];
      uint8_t mode;
      uint64_t flags;

    HilActuatorControls():
      header(),
      controls(),
      mode(0),
      flags(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      for( uint8_t i = 0; i < 16; i++){
      union {
        float real;
        uint32_t base;
      } u_controlsi;
      u_controlsi.real = this->controls[i];
      *(outbuffer + offset + 0) = (u_controlsi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_controlsi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_controlsi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_controlsi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->controls[i]);
      }
      *(outbuffer + offset + 0) = (this->mode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->mode);
      union {
        uint64_t real;
        uint32_t base;
      } u_flags;
      u_flags.real = this->flags;
      *(outbuffer + offset + 0) = (u_flags.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_flags.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_flags.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_flags.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->flags);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      for( uint8_t i = 0; i < 16; i++){
      union {
        float real;
        uint32_t base;
      } u_controlsi;
      u_controlsi.base = 0;
      u_controlsi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_controlsi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_controlsi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_controlsi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->controls[i] = u_controlsi.real;
      offset += sizeof(this->controls[i]);
      }
      this->mode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->mode);
      union {
        uint64_t real;
        uint32_t base;
      } u_flags;
      u_flags.base = 0;
      u_flags.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_flags.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_flags.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_flags.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->flags = u_flags.real;
      offset += sizeof(this->flags);
     return offset;
    }

    const char * getType(){ return "mavros_msgs/HilActuatorControls"; };
    const char * getMD5(){ return "18482e8ef0330ac2fc9a0421be1d11c3"; };

  };

}
#endif