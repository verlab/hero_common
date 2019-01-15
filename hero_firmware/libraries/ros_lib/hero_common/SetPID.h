#ifndef _ROS_SERVICE_SetPID_h
#define _ROS_SERVICE_SetPID_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace hero_common
{

static const char SETPID[] = "hero_common/SetPID";

  class SetPIDRequest : public ros::Msg
  {
    public:
      typedef float _kp_type;
      _kp_type kp;
      typedef float _ki_type;
      _ki_type ki;
      typedef float _kd_type;
      _kd_type kd;

    SetPIDRequest():
      kp(0),
      ki(0),
      kd(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_kp;
      u_kp.real = this->kp;
      *(outbuffer + offset + 0) = (u_kp.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_kp.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_kp.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_kp.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->kp);
      union {
        float real;
        uint32_t base;
      } u_ki;
      u_ki.real = this->ki;
      *(outbuffer + offset + 0) = (u_ki.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ki.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ki.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ki.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ki);
      union {
        float real;
        uint32_t base;
      } u_kd;
      u_kd.real = this->kd;
      *(outbuffer + offset + 0) = (u_kd.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_kd.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_kd.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_kd.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->kd);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_kp;
      u_kp.base = 0;
      u_kp.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_kp.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_kp.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_kp.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->kp = u_kp.real;
      offset += sizeof(this->kp);
      union {
        float real;
        uint32_t base;
      } u_ki;
      u_ki.base = 0;
      u_ki.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ki.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ki.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ki.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ki = u_ki.real;
      offset += sizeof(this->ki);
      union {
        float real;
        uint32_t base;
      } u_kd;
      u_kd.base = 0;
      u_kd.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_kd.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_kd.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_kd.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->kd = u_kd.real;
      offset += sizeof(this->kd);
     return offset;
    }

    const char * getType(){ return SETPID; };
    const char * getMD5(){ return "08d0ca1f582560895ecba909de1d88ec"; };

  };

  class SetPIDResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;
      typedef const char* _message_type;
      _message_type message;

    SetPIDResponse():
      success(0),
      message("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
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

    virtual int deserialize(unsigned char *inbuffer)
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

    const char * getType(){ return SETPID; };
    const char * getMD5(){ return "937c9679a518e3a18d831e57125ea522"; };

  };

  class SetPID {
    public:
    typedef SetPIDRequest Request;
    typedef SetPIDResponse Response;
  };

}
#endif
