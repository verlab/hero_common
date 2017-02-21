#ifndef _ROS_p2os_msgs_LiftState_h
#define _ROS_p2os_msgs_LiftState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace p2os_msgs
{

  class LiftState : public ros::Msg
  {
    public:
      int32_t state;
      int32_t dir;
      float position;

    LiftState():
      state(0),
      dir(0),
      position(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_state;
      u_state.real = this->state;
      *(outbuffer + offset + 0) = (u_state.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_state.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_state.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_state.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->state);
      union {
        int32_t real;
        uint32_t base;
      } u_dir;
      u_dir.real = this->dir;
      *(outbuffer + offset + 0) = (u_dir.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_dir.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_dir.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_dir.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->dir);
      union {
        float real;
        uint32_t base;
      } u_position;
      u_position.real = this->position;
      *(outbuffer + offset + 0) = (u_position.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_position.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_position.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_position.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->position);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_state;
      u_state.base = 0;
      u_state.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_state.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_state.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_state.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->state = u_state.real;
      offset += sizeof(this->state);
      union {
        int32_t real;
        uint32_t base;
      } u_dir;
      u_dir.base = 0;
      u_dir.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_dir.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_dir.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_dir.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->dir = u_dir.real;
      offset += sizeof(this->dir);
      union {
        float real;
        uint32_t base;
      } u_position;
      u_position.base = 0;
      u_position.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_position.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_position.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_position.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->position = u_position.real;
      offset += sizeof(this->position);
     return offset;
    }

    const char * getType(){ return "p2os_msgs/LiftState"; };
    const char * getMD5(){ return "4dcc2e41838611193ef6b9f90c9be41f"; };

  };

}
#endif