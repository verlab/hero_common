#ifndef _ROS_kobuki_msgs_ControllerInfo_h
#define _ROS_kobuki_msgs_ControllerInfo_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace kobuki_msgs
{

  class ControllerInfo : public ros::Msg
  {
    public:
      typedef uint8_t _type_type;
      _type_type type;
      typedef float _p_gain_type;
      _p_gain_type p_gain;
      typedef float _i_gain_type;
      _i_gain_type i_gain;
      typedef float _d_gain_type;
      _d_gain_type d_gain;
      enum { DEFAULT =   0 };
      enum { USER_CONFIGURED =   1 };

    ControllerInfo():
      type(0),
      p_gain(0),
      i_gain(0),
      d_gain(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->type >> (8 * 0)) & 0xFF;
      offset += sizeof(this->type);
      offset += serializeAvrFloat64(outbuffer + offset, this->p_gain);
      offset += serializeAvrFloat64(outbuffer + offset, this->i_gain);
      offset += serializeAvrFloat64(outbuffer + offset, this->d_gain);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->type =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->type);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->p_gain));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->i_gain));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->d_gain));
     return offset;
    }

    const char * getType(){ return "kobuki_msgs/ControllerInfo"; };
    const char * getMD5(){ return "46af38e72f0640f41ed22174d43a2550"; };

  };

}
#endif