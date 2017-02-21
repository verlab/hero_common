#ifndef _ROS_SERVICE_RemoteAll_h
#define _ROS_SERVICE_RemoteAll_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "gateway_msgs/Rule.h"

namespace gateway_msgs
{

static const char REMOTEALL[] = "gateway_msgs/RemoteAll";

  class RemoteAllRequest : public ros::Msg
  {
    public:
      const char* gateway;
      uint8_t blacklist_length;
      gateway_msgs::Rule st_blacklist;
      gateway_msgs::Rule * blacklist;
      bool cancel;

    RemoteAllRequest():
      gateway(""),
      blacklist_length(0), blacklist(NULL),
      cancel(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_gateway = strlen(this->gateway);
      memcpy(outbuffer + offset, &length_gateway, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->gateway, length_gateway);
      offset += length_gateway;
      *(outbuffer + offset++) = blacklist_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < blacklist_length; i++){
      offset += this->blacklist[i].serialize(outbuffer + offset);
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
      uint32_t length_gateway;
      memcpy(&length_gateway, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_gateway; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_gateway-1]=0;
      this->gateway = (char *)(inbuffer + offset-1);
      offset += length_gateway;
      uint8_t blacklist_lengthT = *(inbuffer + offset++);
      if(blacklist_lengthT > blacklist_length)
        this->blacklist = (gateway_msgs::Rule*)realloc(this->blacklist, blacklist_lengthT * sizeof(gateway_msgs::Rule));
      offset += 3;
      blacklist_length = blacklist_lengthT;
      for( uint8_t i = 0; i < blacklist_length; i++){
      offset += this->st_blacklist.deserialize(inbuffer + offset);
        memcpy( &(this->blacklist[i]), &(this->st_blacklist), sizeof(gateway_msgs::Rule));
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

    const char * getType(){ return REMOTEALL; };
    const char * getMD5(){ return "036fdb1a9946cb6fec17ef2d907450d9"; };

  };

  class RemoteAllResponse : public ros::Msg
  {
    public:
      int8_t result;
      const char* error_message;

    RemoteAllResponse():
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

    const char * getType(){ return REMOTEALL; };
    const char * getMD5(){ return "cb1e85ae0c5f4b1c31221493724cc5aa"; };

  };

  class RemoteAll {
    public:
    typedef RemoteAllRequest Request;
    typedef RemoteAllResponse Response;
  };

}
#endif
