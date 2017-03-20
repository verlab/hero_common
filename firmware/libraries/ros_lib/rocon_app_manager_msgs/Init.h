#ifndef _ROS_SERVICE_Init_h
#define _ROS_SERVICE_Init_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rocon_app_manager_msgs
{

static const char INIT[] = "rocon_app_manager_msgs/Init";

  class InitRequest : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;

    InitRequest():
      name("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
     return offset;
    }

    const char * getType(){ return INIT; };
    const char * getMD5(){ return "c1f3d28f1b044c871e6eff2e9fc3c667"; };

  };

  class InitResponse : public ros::Msg
  {
    public:
      typedef bool _result_type;
      _result_type result;

    InitResponse():
      result(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_result;
      u_result.real = this->result;
      *(outbuffer + offset + 0) = (u_result.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->result);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_result;
      u_result.base = 0;
      u_result.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->result = u_result.real;
      offset += sizeof(this->result);
     return offset;
    }

    const char * getType(){ return INIT; };
    const char * getMD5(){ return "eb13ac1f1354ccecb7941ee8fa2192e8"; };

  };

  class Init {
    public:
    typedef InitRequest Request;
    typedef InitResponse Response;
  };

}
#endif
