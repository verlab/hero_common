#ifndef _ROS_mavros_msgs_Altitude_h
#define _ROS_mavros_msgs_Altitude_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace mavros_msgs
{

  class Altitude : public ros::Msg
  {
    public:
      std_msgs::Header header;
      float monotonic;
      float amsl;
      float local;
      float relative;
      float terrain;
      float bottom_clearance;

    Altitude():
      header(),
      monotonic(0),
      amsl(0),
      local(0),
      relative(0),
      terrain(0),
      bottom_clearance(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_monotonic;
      u_monotonic.real = this->monotonic;
      *(outbuffer + offset + 0) = (u_monotonic.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_monotonic.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_monotonic.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_monotonic.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->monotonic);
      union {
        float real;
        uint32_t base;
      } u_amsl;
      u_amsl.real = this->amsl;
      *(outbuffer + offset + 0) = (u_amsl.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_amsl.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_amsl.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_amsl.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->amsl);
      union {
        float real;
        uint32_t base;
      } u_local;
      u_local.real = this->local;
      *(outbuffer + offset + 0) = (u_local.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_local.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_local.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_local.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->local);
      union {
        float real;
        uint32_t base;
      } u_relative;
      u_relative.real = this->relative;
      *(outbuffer + offset + 0) = (u_relative.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_relative.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_relative.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_relative.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->relative);
      union {
        float real;
        uint32_t base;
      } u_terrain;
      u_terrain.real = this->terrain;
      *(outbuffer + offset + 0) = (u_terrain.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_terrain.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_terrain.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_terrain.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->terrain);
      union {
        float real;
        uint32_t base;
      } u_bottom_clearance;
      u_bottom_clearance.real = this->bottom_clearance;
      *(outbuffer + offset + 0) = (u_bottom_clearance.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_bottom_clearance.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_bottom_clearance.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_bottom_clearance.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->bottom_clearance);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_monotonic;
      u_monotonic.base = 0;
      u_monotonic.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_monotonic.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_monotonic.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_monotonic.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->monotonic = u_monotonic.real;
      offset += sizeof(this->monotonic);
      union {
        float real;
        uint32_t base;
      } u_amsl;
      u_amsl.base = 0;
      u_amsl.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_amsl.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_amsl.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_amsl.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->amsl = u_amsl.real;
      offset += sizeof(this->amsl);
      union {
        float real;
        uint32_t base;
      } u_local;
      u_local.base = 0;
      u_local.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_local.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_local.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_local.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->local = u_local.real;
      offset += sizeof(this->local);
      union {
        float real;
        uint32_t base;
      } u_relative;
      u_relative.base = 0;
      u_relative.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_relative.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_relative.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_relative.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->relative = u_relative.real;
      offset += sizeof(this->relative);
      union {
        float real;
        uint32_t base;
      } u_terrain;
      u_terrain.base = 0;
      u_terrain.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_terrain.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_terrain.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_terrain.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->terrain = u_terrain.real;
      offset += sizeof(this->terrain);
      union {
        float real;
        uint32_t base;
      } u_bottom_clearance;
      u_bottom_clearance.base = 0;
      u_bottom_clearance.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_bottom_clearance.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_bottom_clearance.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_bottom_clearance.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->bottom_clearance = u_bottom_clearance.real;
      offset += sizeof(this->bottom_clearance);
     return offset;
    }

    const char * getType(){ return "mavros_msgs/Altitude"; };
    const char * getMD5(){ return "1296a05dc5b6160be0ae04ba9ed3a3fa"; };

  };

}
#endif