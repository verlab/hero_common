#ifndef _ROS_SERVICE_SetMotor_h
#define _ROS_SERVICE_SetMotor_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace hero_common
{

static const char SETMOTOR[] = "hero_common/SetMotor";

  class SetMotorRequest : public ros::Msg
  {
    public:
      typedef int16_t _left_motor_pwm_type;
      _left_motor_pwm_type left_motor_pwm;
      typedef int16_t _right_motor_pwm_type;
      _right_motor_pwm_type right_motor_pwm;

    SetMotorRequest():
      left_motor_pwm(0),
      right_motor_pwm(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
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

    virtual int deserialize(unsigned char *inbuffer) override
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

    virtual const char * getType() override { return SETMOTOR; };
    virtual const char * getMD5() override { return "44d4249d207ce6a89de3d72080e4d0b5"; };

  };

  class SetMotorResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;
      typedef const char* _message_type;
      _message_type message;

    SetMotorResponse():
      success(0),
      message("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      uint32_t length_message = strlen(this->message);
      varToArr(outbuffer + offset, length_message);
      offset += 4;
      memcpy(outbuffer + offset, this->message, length_message);
      offset += length_message;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
      uint32_t length_message;
      arrToVar(length_message, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_message-1]=0;
      this->message = (char *)(inbuffer + offset-1);
      offset += length_message;
     return offset;
    }

    virtual const char * getType() override { return SETMOTOR; };
    virtual const char * getMD5() override { return "937c9679a518e3a18d831e57125ea522"; };

  };

  class SetMotor {
    public:
    typedef SetMotorRequest Request;
    typedef SetMotorResponse Response;
  };

}
#endif
