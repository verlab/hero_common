#ifndef _ROS_mavros_msgs_Waypoint_h
#define _ROS_mavros_msgs_Waypoint_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mavros_msgs
{

  class Waypoint : public ros::Msg
  {
    public:
      uint8_t frame;
      uint16_t command;
      bool is_current;
      bool autocontinue;
      float param1;
      float param2;
      float param3;
      float param4;
      float x_lat;
      float y_long;
      float z_alt;
      enum { FRAME_GLOBAL =  0 };
      enum { FRAME_LOCAL_NED =  1 };
      enum { FRAME_MISSION =  2 };
      enum { FRAME_GLOBAL_REL_ALT =  3 };
      enum { FRAME_LOCAL_ENU =  4 };

    Waypoint():
      frame(0),
      command(0),
      is_current(0),
      autocontinue(0),
      param1(0),
      param2(0),
      param3(0),
      param4(0),
      x_lat(0),
      y_long(0),
      z_alt(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->frame >> (8 * 0)) & 0xFF;
      offset += sizeof(this->frame);
      *(outbuffer + offset + 0) = (this->command >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->command >> (8 * 1)) & 0xFF;
      offset += sizeof(this->command);
      union {
        bool real;
        uint8_t base;
      } u_is_current;
      u_is_current.real = this->is_current;
      *(outbuffer + offset + 0) = (u_is_current.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->is_current);
      union {
        bool real;
        uint8_t base;
      } u_autocontinue;
      u_autocontinue.real = this->autocontinue;
      *(outbuffer + offset + 0) = (u_autocontinue.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->autocontinue);
      union {
        float real;
        uint32_t base;
      } u_param1;
      u_param1.real = this->param1;
      *(outbuffer + offset + 0) = (u_param1.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_param1.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_param1.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_param1.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->param1);
      union {
        float real;
        uint32_t base;
      } u_param2;
      u_param2.real = this->param2;
      *(outbuffer + offset + 0) = (u_param2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_param2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_param2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_param2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->param2);
      union {
        float real;
        uint32_t base;
      } u_param3;
      u_param3.real = this->param3;
      *(outbuffer + offset + 0) = (u_param3.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_param3.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_param3.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_param3.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->param3);
      union {
        float real;
        uint32_t base;
      } u_param4;
      u_param4.real = this->param4;
      *(outbuffer + offset + 0) = (u_param4.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_param4.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_param4.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_param4.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->param4);
      offset += serializeAvrFloat64(outbuffer + offset, this->x_lat);
      offset += serializeAvrFloat64(outbuffer + offset, this->y_long);
      offset += serializeAvrFloat64(outbuffer + offset, this->z_alt);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->frame =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->frame);
      this->command =  ((uint16_t) (*(inbuffer + offset)));
      this->command |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->command);
      union {
        bool real;
        uint8_t base;
      } u_is_current;
      u_is_current.base = 0;
      u_is_current.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->is_current = u_is_current.real;
      offset += sizeof(this->is_current);
      union {
        bool real;
        uint8_t base;
      } u_autocontinue;
      u_autocontinue.base = 0;
      u_autocontinue.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->autocontinue = u_autocontinue.real;
      offset += sizeof(this->autocontinue);
      union {
        float real;
        uint32_t base;
      } u_param1;
      u_param1.base = 0;
      u_param1.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_param1.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_param1.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_param1.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->param1 = u_param1.real;
      offset += sizeof(this->param1);
      union {
        float real;
        uint32_t base;
      } u_param2;
      u_param2.base = 0;
      u_param2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_param2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_param2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_param2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->param2 = u_param2.real;
      offset += sizeof(this->param2);
      union {
        float real;
        uint32_t base;
      } u_param3;
      u_param3.base = 0;
      u_param3.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_param3.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_param3.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_param3.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->param3 = u_param3.real;
      offset += sizeof(this->param3);
      union {
        float real;
        uint32_t base;
      } u_param4;
      u_param4.base = 0;
      u_param4.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_param4.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_param4.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_param4.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->param4 = u_param4.real;
      offset += sizeof(this->param4);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->x_lat));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->y_long));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->z_alt));
     return offset;
    }

    const char * getType(){ return "mavros_msgs/Waypoint"; };
    const char * getMD5(){ return "7a0d2b53dcd6b7aff0aa748703e85e92"; };

  };

}
#endif