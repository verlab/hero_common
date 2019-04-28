#ifndef _ROS_hero_common_Motor_h
#define _ROS_hero_common_Motor_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace hero_common
{

  class Motor : public ros::Msg
  {
    public:
      typedef int16_t _left_motor_pwm_type;
      _left_motor_pwm_type left_motor_pwm;
      typedef int16_t _right_motor_pwm_type;
      _right_motor_pwm_type right_motor_pwm;

    Motor():
      left_motor_pwm(0),
      right_motor_pwm(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_left_motor_pwm;
      u_left_motor_pwm.real = this->left_motor_pwm;
      *(outbuffer + offset + 0) = (u_left_motor_pwm.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_left_motor_pwm.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->left_motor_pwm);
      union {
        int16_t real;
        uint16_t base;
      } u_right_motor_pwm;
      u_right_motor_pwm.real = this->right_motor_pwm;
      *(outbuffer + offset + 0) = (u_right_motor_pwm.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_right_motor_pwm.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->right_motor_pwm);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_left_motor_pwm;
      u_left_motor_pwm.base = 0;
      u_left_motor_pwm.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_left_motor_pwm.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->left_motor_pwm = u_left_motor_pwm.real;
      offset += sizeof(this->left_motor_pwm);
      union {
        int16_t real;
        uint16_t base;
      } u_right_motor_pwm;
      u_right_motor_pwm.base = 0;
      u_right_motor_pwm.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_right_motor_pwm.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->right_motor_pwm = u_right_motor_pwm.real;
      offset += sizeof(this->right_motor_pwm);
     return offset;
    }

    const char * getType(){ return "hero_common/Motor"; };
    const char * getMD5(){ return "44d4249d207ce6a89de3d72080e4d0b5"; };

  };

}
#endif
