#ifndef _ROS_SERVICE_SetTurtlebotMode_h
#define _ROS_SERVICE_SetTurtlebotMode_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace create_node
{

static const char SETTURTLEBOTMODE[] = "create_node/SetTurtlebotMode";

  class SetTurtlebotModeRequest : public ros::Msg
  {
    public:
      typedef uint8_t _mode_type;
      _mode_type mode;

    SetTurtlebotModeRequest():
      mode(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->mode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->mode);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->mode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->mode);
     return offset;
    }

    const char * getType(){ return SETTURTLEBOTMODE; };
    const char * getMD5(){ return "89b81386720be1cd0ce7a3953fcd1b19"; };

  };

  class SetTurtlebotModeResponse : public ros::Msg
  {
    public:
      typedef bool _valid_mode_type;
      _valid_mode_type valid_mode;

    SetTurtlebotModeResponse():
      valid_mode(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_valid_mode;
      u_valid_mode.real = this->valid_mode;
      *(outbuffer + offset + 0) = (u_valid_mode.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->valid_mode);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_valid_mode;
      u_valid_mode.base = 0;
      u_valid_mode.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->valid_mode = u_valid_mode.real;
      offset += sizeof(this->valid_mode);
     return offset;
    }

    const char * getType(){ return SETTURTLEBOTMODE; };
    const char * getMD5(){ return "ef9db56bf4a60ce42049595d58c32b54"; };

  };

  class SetTurtlebotMode {
    public:
    typedef SetTurtlebotModeRequest Request;
    typedef SetTurtlebotModeResponse Response;
  };

}
#endif
