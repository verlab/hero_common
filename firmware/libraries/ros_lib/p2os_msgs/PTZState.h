#ifndef _ROS_p2os_msgs_PTZState_h
#define _ROS_p2os_msgs_PTZState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace p2os_msgs
{

  class PTZState : public ros::Msg
  {
    public:
      int32_t pan;
      int32_t tilt;
      int32_t zoom;
      bool relative;

    PTZState():
      pan(0),
      tilt(0),
      zoom(0),
      relative(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_pan;
      u_pan.real = this->pan;
      *(outbuffer + offset + 0) = (u_pan.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pan.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pan.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pan.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pan);
      union {
        int32_t real;
        uint32_t base;
      } u_tilt;
      u_tilt.real = this->tilt;
      *(outbuffer + offset + 0) = (u_tilt.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_tilt.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_tilt.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_tilt.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->tilt);
      union {
        int32_t real;
        uint32_t base;
      } u_zoom;
      u_zoom.real = this->zoom;
      *(outbuffer + offset + 0) = (u_zoom.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_zoom.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_zoom.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_zoom.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->zoom);
      union {
        bool real;
        uint8_t base;
      } u_relative;
      u_relative.real = this->relative;
      *(outbuffer + offset + 0) = (u_relative.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->relative);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_pan;
      u_pan.base = 0;
      u_pan.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pan.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pan.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pan.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pan = u_pan.real;
      offset += sizeof(this->pan);
      union {
        int32_t real;
        uint32_t base;
      } u_tilt;
      u_tilt.base = 0;
      u_tilt.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_tilt.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_tilt.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_tilt.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->tilt = u_tilt.real;
      offset += sizeof(this->tilt);
      union {
        int32_t real;
        uint32_t base;
      } u_zoom;
      u_zoom.base = 0;
      u_zoom.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_zoom.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_zoom.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_zoom.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->zoom = u_zoom.real;
      offset += sizeof(this->zoom);
      union {
        bool real;
        uint8_t base;
      } u_relative;
      u_relative.base = 0;
      u_relative.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->relative = u_relative.real;
      offset += sizeof(this->relative);
     return offset;
    }

    const char * getType(){ return "p2os_msgs/PTZState"; };
    const char * getMD5(){ return "1f71ce2a42b32376ea869eb051358045"; };

  };

}
#endif