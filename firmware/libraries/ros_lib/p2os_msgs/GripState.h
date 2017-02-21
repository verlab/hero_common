#ifndef _ROS_p2os_msgs_GripState_h
#define _ROS_p2os_msgs_GripState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace p2os_msgs
{

  class GripState : public ros::Msg
  {
    public:
      uint32_t state;
      int32_t dir;
      bool inner_beam;
      bool outer_beam;
      bool left_contact;
      bool right_contact;

    GripState():
      state(0),
      dir(0),
      inner_beam(0),
      outer_beam(0),
      left_contact(0),
      right_contact(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->state >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->state >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->state >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->state >> (8 * 3)) & 0xFF;
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
        bool real;
        uint8_t base;
      } u_inner_beam;
      u_inner_beam.real = this->inner_beam;
      *(outbuffer + offset + 0) = (u_inner_beam.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->inner_beam);
      union {
        bool real;
        uint8_t base;
      } u_outer_beam;
      u_outer_beam.real = this->outer_beam;
      *(outbuffer + offset + 0) = (u_outer_beam.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->outer_beam);
      union {
        bool real;
        uint8_t base;
      } u_left_contact;
      u_left_contact.real = this->left_contact;
      *(outbuffer + offset + 0) = (u_left_contact.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->left_contact);
      union {
        bool real;
        uint8_t base;
      } u_right_contact;
      u_right_contact.real = this->right_contact;
      *(outbuffer + offset + 0) = (u_right_contact.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->right_contact);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->state =  ((uint32_t) (*(inbuffer + offset)));
      this->state |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->state |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->state |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
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
        bool real;
        uint8_t base;
      } u_inner_beam;
      u_inner_beam.base = 0;
      u_inner_beam.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->inner_beam = u_inner_beam.real;
      offset += sizeof(this->inner_beam);
      union {
        bool real;
        uint8_t base;
      } u_outer_beam;
      u_outer_beam.base = 0;
      u_outer_beam.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->outer_beam = u_outer_beam.real;
      offset += sizeof(this->outer_beam);
      union {
        bool real;
        uint8_t base;
      } u_left_contact;
      u_left_contact.base = 0;
      u_left_contact.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->left_contact = u_left_contact.real;
      offset += sizeof(this->left_contact);
      union {
        bool real;
        uint8_t base;
      } u_right_contact;
      u_right_contact.base = 0;
      u_right_contact.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->right_contact = u_right_contact.real;
      offset += sizeof(this->right_contact);
     return offset;
    }

    const char * getType(){ return "p2os_msgs/GripState"; };
    const char * getMD5(){ return "370eb3507be0ed1043be50a3da3a07c6"; };

  };

}
#endif