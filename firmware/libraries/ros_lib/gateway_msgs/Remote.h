#ifndef _ROS_SERVICE_Remote_h
#define _ROS_SERVICE_Remote_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "gateway_msgs/RemoteRule.h"

namespace gateway_msgs
{

static const char REMOTE[] = "gateway_msgs/Remote";

  class RemoteRequest : public ros::Msg
  {
    public:
      uint8_t remotes_length;
      gateway_msgs::RemoteRule st_remotes;
      gateway_msgs::RemoteRule * remotes;
      bool cancel;

    RemoteRequest():
      remotes_length(0), remotes(NULL),
      cancel(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = remotes_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < remotes_length; i++){
      offset += this->remotes[i].serialize(outbuffer + offset);
      }
      union {
        bool real;
        uint8_t base;
      } u_cancel;
      u_cancel.real = this->cancel;
      *(outbuffer + offset + 0) = (u_cancel.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->cancel);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t remotes_lengthT = *(inbuffer + offset++);
      if(remotes_lengthT > remotes_length)
        this->remotes = (gateway_msgs::RemoteRule*)realloc(this->remotes, remotes_lengthT * sizeof(gateway_msgs::RemoteRule));
      offset += 3;
      remotes_length = remotes_lengthT;
      for( uint8_t i = 0; i < remotes_length; i++){
      offset += this->st_remotes.deserialize(inbuffer + offset);
        memcpy( &(this->remotes[i]), &(this->st_remotes), sizeof(gateway_msgs::RemoteRule));
      }
      union {
        bool real;
        uint8_t base;
      } u_cancel;
      u_cancel.base = 0;
      u_cancel.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->cancel = u_cancel.real;
      offset += sizeof(this->cancel);
     return offset;
    }

    const char * getType(){ return REMOTE; };
    const char * getMD5(){ return "e9d79fdaee662b9f88ad5ffedb506465"; };

  };

  class RemoteResponse : public ros::Msg
  {
    public:
      int8_t result;
      const char* error_message;

    RemoteResponse():
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
      memcpy(outbuffer + offset, &length_error_message, sizeof(uint32_t));
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
      memcpy(&length_error_message, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_error_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_error_message-1]=0;
      this->error_message = (char *)(inbuffer + offset-1);
      offset += length_error_message;
     return offset;
    }

    const char * getType(){ return REMOTE; };
    const char * getMD5(){ return "cb1e85ae0c5f4b1c31221493724cc5aa"; };

  };

  class Remote {
    public:
    typedef RemoteRequest Request;
    typedef RemoteResponse Response;
  };

}
#endif
