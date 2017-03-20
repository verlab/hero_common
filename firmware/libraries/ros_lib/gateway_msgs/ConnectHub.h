#ifndef _ROS_SERVICE_ConnectHub_h
#define _ROS_SERVICE_ConnectHub_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace gateway_msgs
{

static const char CONNECTHUB[] = "gateway_msgs/ConnectHub";

  class ConnectHubRequest : public ros::Msg
  {
    public:
      typedef const char* _uri_type;
      _uri_type uri;

    ConnectHubRequest():
      uri("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_uri = strlen(this->uri);
      varToArr(outbuffer + offset, length_uri);
      offset += 4;
      memcpy(outbuffer + offset, this->uri, length_uri);
      offset += length_uri;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_uri;
      arrToVar(length_uri, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_uri; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_uri-1]=0;
      this->uri = (char *)(inbuffer + offset-1);
      offset += length_uri;
     return offset;
    }

    const char * getType(){ return CONNECTHUB; };
    const char * getMD5(){ return "636fe5e07550f026d28388e95c38a9f4"; };

  };

  class ConnectHubResponse : public ros::Msg
  {
    public:
      typedef int8_t _result_type;
      _result_type result;
      typedef const char* _error_message_type;
      _error_message_type error_message;

    ConnectHubResponse():
      result(0),
      error_message("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_result;
      u_result.real = this->result;
      *(outbuffer + offset + 0) = (u_result.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->result);
      uint32_t length_error_message = strlen(this->error_message);
      varToArr(outbuffer + offset, length_error_message);
      offset += 4;
      memcpy(outbuffer + offset, this->error_message, length_error_message);
      offset += length_error_message;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_result;
      u_result.base = 0;
      u_result.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->result = u_result.real;
      offset += sizeof(this->result);
      uint32_t length_error_message;
      arrToVar(length_error_message, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_error_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_error_message-1]=0;
      this->error_message = (char *)(inbuffer + offset-1);
      offset += length_error_message;
     return offset;
    }

    const char * getType(){ return CONNECTHUB; };
    const char * getMD5(){ return "cb1e85ae0c5f4b1c31221493724cc5aa"; };

  };

  class ConnectHub {
    public:
    typedef ConnectHubRequest Request;
    typedef ConnectHubResponse Response;
  };

}
#endif
