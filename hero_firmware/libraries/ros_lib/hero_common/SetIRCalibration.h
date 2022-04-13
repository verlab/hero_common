#ifndef _ROS_SERVICE_SetIRCalibration_h
#define _ROS_SERVICE_SetIRCalibration_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace hero_common
{

static const char SETIRCALIBRATION[] = "hero_common/SetIRCalibration";

  class SetIRCalibrationRequest : public ros::Msg
  {
    public:
      typedef float _IR0_type;
      _IR0_type IR0;
      typedef float _IR1_type;
      _IR1_type IR1;
      typedef float _IR2_type;
      _IR2_type IR2;
      typedef float _IR3_type;
      _IR3_type IR3;
      typedef float _IR4_type;
      _IR4_type IR4;
      typedef float _IR5_type;
      _IR5_type IR5;
      typedef float _IR6_type;
      _IR6_type IR6;
      typedef float _IR7_type;
      _IR7_type IR7;

    SetIRCalibrationRequest():
      IR0(0),
      IR1(0),
      IR2(0),
      IR3(0),
      IR4(0),
      IR5(0),
      IR6(0),
      IR7(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->IR0);
      offset += serializeAvrFloat64(outbuffer + offset, this->IR1);
      offset += serializeAvrFloat64(outbuffer + offset, this->IR2);
      offset += serializeAvrFloat64(outbuffer + offset, this->IR3);
      offset += serializeAvrFloat64(outbuffer + offset, this->IR4);
      offset += serializeAvrFloat64(outbuffer + offset, this->IR5);
      offset += serializeAvrFloat64(outbuffer + offset, this->IR6);
      offset += serializeAvrFloat64(outbuffer + offset, this->IR7);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->IR0));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->IR1));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->IR2));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->IR3));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->IR4));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->IR5));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->IR6));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->IR7));
     return offset;
    }

    virtual const char * getType() override { return SETIRCALIBRATION; };
    virtual const char * getMD5() override { return "27748d949ad62e65750ad22074426005"; };

  };

  class SetIRCalibrationResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;
      typedef const char* _message_type;
      _message_type message;

    SetIRCalibrationResponse():
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

    virtual const char * getType() override { return SETIRCALIBRATION; };
    virtual const char * getMD5() override { return "937c9679a518e3a18d831e57125ea522"; };

  };

  class SetIRCalibration {
    public:
    typedef SetIRCalibrationRequest Request;
    typedef SetIRCalibrationResponse Response;
  };

}
#endif
