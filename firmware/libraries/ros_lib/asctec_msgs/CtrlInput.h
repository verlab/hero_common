#ifndef _ROS_asctec_msgs_CtrlInput_h
#define _ROS_asctec_msgs_CtrlInput_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace asctec_msgs
{

  class CtrlInput : public ros::Msg
  {
    public:
      std_msgs::Header header;
      int16_t pitch;
      int16_t roll;
      int16_t yaw;
      int16_t thrust;
      int16_t ctrl;
      int16_t chksum;

    CtrlInput():
      header(),
      pitch(0),
      roll(0),
      yaw(0),
      thrust(0),
      ctrl(0),
      chksum(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        int16_t real;
        uint16_t base;
      } u_pitch;
      u_pitch.real = this->pitch;
      *(outbuffer + offset + 0) = (u_pitch.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pitch.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->pitch);
      union {
        int16_t real;
        uint16_t base;
      } u_roll;
      u_roll.real = this->roll;
      *(outbuffer + offset + 0) = (u_roll.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_roll.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->roll);
      union {
        int16_t real;
        uint16_t base;
      } u_yaw;
      u_yaw.real = this->yaw;
      *(outbuffer + offset + 0) = (u_yaw.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_yaw.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->yaw);
      union {
        int16_t real;
        uint16_t base;
      } u_thrust;
      u_thrust.real = this->thrust;
      *(outbuffer + offset + 0) = (u_thrust.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_thrust.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->thrust);
      union {
        int16_t real;
        uint16_t base;
      } u_ctrl;
      u_ctrl.real = this->ctrl;
      *(outbuffer + offset + 0) = (u_ctrl.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ctrl.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->ctrl);
      union {
        int16_t real;
        uint16_t base;
      } u_chksum;
      u_chksum.real = this->chksum;
      *(outbuffer + offset + 0) = (u_chksum.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_chksum.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->chksum);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        int16_t real;
        uint16_t base;
      } u_pitch;
      u_pitch.base = 0;
      u_pitch.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pitch.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->pitch = u_pitch.real;
      offset += sizeof(this->pitch);
      union {
        int16_t real;
        uint16_t base;
      } u_roll;
      u_roll.base = 0;
      u_roll.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_roll.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->roll = u_roll.real;
      offset += sizeof(this->roll);
      union {
        int16_t real;
        uint16_t base;
      } u_yaw;
      u_yaw.base = 0;
      u_yaw.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_yaw.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->yaw = u_yaw.real;
      offset += sizeof(this->yaw);
      union {
        int16_t real;
        uint16_t base;
      } u_thrust;
      u_thrust.base = 0;
      u_thrust.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_thrust.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->thrust = u_thrust.real;
      offset += sizeof(this->thrust);
      union {
        int16_t real;
        uint16_t base;
      } u_ctrl;
      u_ctrl.base = 0;
      u_ctrl.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ctrl.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->ctrl = u_ctrl.real;
      offset += sizeof(this->ctrl);
      union {
        int16_t real;
        uint16_t base;
      } u_chksum;
      u_chksum.base = 0;
      u_chksum.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_chksum.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->chksum = u_chksum.real;
      offset += sizeof(this->chksum);
     return offset;
    }

    const char * getType(){ return "asctec_msgs/CtrlInput"; };
    const char * getMD5(){ return "6a2f3591afa7529005dcc3a5acd6e490"; };

  };

}
#endif