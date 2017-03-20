#ifndef _ROS_SERVICE_RemoveListener_h
#define _ROS_SERVICE_RemoveListener_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace zeroconf_msgs
{

static const char REMOVELISTENER[] = "zeroconf_msgs/RemoveListener";

  class RemoveListenerRequest : public ros::Msg
  {
    public:
      typedef const char* _service_type_type;
      _service_type_type service_type;

    RemoveListenerRequest():
      service_type("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_service_type = strlen(this->service_type);
      varToArr(outbuffer + offset, length_service_type);
      offset += 4;
      memcpy(outbuffer + offset, this->service_type, length_service_type);
      offset += length_service_type;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_service_type;
      arrToVar(length_service_type, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_service_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_service_type-1]=0;
      this->service_type = (char *)(inbuffer + offset-1);
      offset += length_service_type;
     return offset;
    }

    const char * getType(){ return REMOVELISTENER; };
    const char * getMD5(){ return "e1bf1fd6519c823d87c16f342a193a85"; };

  };

  class RemoveListenerResponse : public ros::Msg
  {
    public:
      typedef bool _result_type;
      _result_type result;

    RemoveListenerResponse():
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

    const char * getType(){ return REMOVELISTENER; };
    const char * getMD5(){ return "eb13ac1f1354ccecb7941ee8fa2192e8"; };

  };

  class RemoveListener {
    public:
    typedef RemoveListenerRequest Request;
    typedef RemoveListenerResponse Response;
  };

}
#endif
