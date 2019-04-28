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
      typedef float _lkp_type;
      _lkp_type lkp;
      typedef float _lki_type;
      _lki_type lki;
      typedef float _lkd_type;
      _lkd_type lkd;
      typedef float _rkp_type;
      _rkp_type rkp;
      typedef float _rki_type;
      _rki_type rki;
      typedef float _rkd_type;
      _rkd_type rkd;

    SetPIDRequest():
      lkp(0),
      lki(0),
      lkd(0),
      rkp(0),
      rki(0),
      rkd(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_lkp;
      u_lkp.real = this->lkp;
      *(outbuffer + offset + 0) = (u_lkp.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_lkp.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_lkp.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_lkp.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->lkp);
      union {
        float real;
        uint32_t base;
      } u_lki;
      u_lki.real = this->lki;
      *(outbuffer + offset + 0) = (u_lki.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_lki.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_lki.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_lki.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->lki);
      union {
        float real;
        uint32_t base;
      } u_lkd;
      u_lkd.real = this->lkd;
      *(outbuffer + offset + 0) = (u_lkd.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_lkd.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_lkd.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_lkd.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->lkd);
      union {
        float real;
        uint32_t base;
      } u_rkp;
      u_rkp.real = this->rkp;
      *(outbuffer + offset + 0) = (u_rkp.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rkp.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rkp.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rkp.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rkp);
      union {
        float real;
        uint32_t base;
      } u_rki;
      u_rki.real = this->rki;
      *(outbuffer + offset + 0) = (u_rki.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rki.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rki.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rki.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rki);
      union {
        float real;
        uint32_t base;
      } u_rkd;
      u_rkd.real = this->rkd;
      *(outbuffer + offset + 0) = (u_rkd.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rkd.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rkd.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rkd.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rkd);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_lkp;
      u_lkp.base = 0;
      u_lkp.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_lkp.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_lkp.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_lkp.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->lkp = u_lkp.real;
      offset += sizeof(this->lkp);
      union {
        float real;
        uint32_t base;
      } u_lki;
      u_lki.base = 0;
      u_lki.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_lki.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_lki.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_lki.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->lki = u_lki.real;
      offset += sizeof(this->lki);
      union {
        float real;
        uint32_t base;
      } u_lkd;
      u_lkd.base = 0;
      u_lkd.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_lkd.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_lkd.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_lkd.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->lkd = u_lkd.real;
      offset += sizeof(this->lkd);
      union {
        float real;
        uint32_t base;
      } u_rkp;
      u_rkp.base = 0;
      u_rkp.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_rkp.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_rkp.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_rkp.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->rkp = u_rkp.real;
      offset += sizeof(this->rkp);
      union {
        float real;
        uint32_t base;
      } u_rki;
      u_rki.base = 0;
      u_rki.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_rki.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_rki.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_rki.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->rki = u_rki.real;
      offset += sizeof(this->rki);
      union {
        float real;
        uint32_t base;
      } u_rkd;
      u_rkd.base = 0;
      u_rkd.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_rkd.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_rkd.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_rkd.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->rkd = u_rkd.real;
      offset += sizeof(this->rkd);
     return offset;
    }

    const char * getType(){ return SETPID; };
    const char * getMD5(){ return "f0d0bdba02bc62a48d52638e38dc8a4b"; };

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
