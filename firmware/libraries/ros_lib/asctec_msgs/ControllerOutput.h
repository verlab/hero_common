#ifndef _ROS_asctec_msgs_ControllerOutput_h
#define _ROS_asctec_msgs_ControllerOutput_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace asctec_msgs
{

  class ControllerOutput : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef int32_t _nick_type;
      _nick_type nick;
      typedef int32_t _roll_type;
      _roll_type roll;
      typedef int32_t _yaw_type;
      _yaw_type yaw;
      typedef int32_t _thrust_type;
      _thrust_type thrust;

    ControllerOutput():
      header(),
      nick(0),
      roll(0),
      yaw(0),
      thrust(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_nick;
      u_nick.real = this->nick;
      *(outbuffer + offset + 0) = (u_nick.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_nick.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_nick.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_nick.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->nick);
      union {
        int32_t real;
        uint32_t base;
      } u_roll;
      u_roll.real = this->roll;
      *(outbuffer + offset + 0) = (u_roll.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_roll.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_roll.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_roll.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->roll);
      union {
        int32_t real;
        uint32_t base;
      } u_yaw;
      u_yaw.real = this->yaw;
      *(outbuffer + offset + 0) = (u_yaw.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_yaw.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_yaw.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_yaw.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->yaw);
      union {
        int32_t real;
        uint32_t base;
      } u_thrust;
      u_thrust.real = this->thrust;
      *(outbuffer + offset + 0) = (u_thrust.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_thrust.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_thrust.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_thrust.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->thrust);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_nick;
      u_nick.base = 0;
      u_nick.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_nick.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_nick.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_nick.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->nick = u_nick.real;
      offset += sizeof(this->nick);
      union {
        int32_t real;
        uint32_t base;
      } u_roll;
      u_roll.base = 0;
      u_roll.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_roll.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_roll.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_roll.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->roll = u_roll.real;
      offset += sizeof(this->roll);
      union {
        int32_t real;
        uint32_t base;
      } u_yaw;
      u_yaw.base = 0;
      u_yaw.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_yaw.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_yaw.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_yaw.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->yaw = u_yaw.real;
      offset += sizeof(this->yaw);
      union {
        int32_t real;
        uint32_t base;
      } u_thrust;
      u_thrust.base = 0;
      u_thrust.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_thrust.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_thrust.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_thrust.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->thrust = u_thrust.real;
      offset += sizeof(this->thrust);
     return offset;
    }

    const char * getType(){ return "asctec_msgs/ControllerOutput"; };
    const char * getMD5(){ return "25c7094035da7c0bf36050e699ef0f7a"; };

  };

}
#endif