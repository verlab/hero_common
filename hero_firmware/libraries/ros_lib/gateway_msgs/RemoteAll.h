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
      typedef const char* _gateway_type;
      _gateway_type gateway;
      uint32_t blacklist_length;
      typedef gateway_msgs::Rule _blacklist_type;
      _blacklist_type st_blacklist;
      _blacklist_type * blacklist;
      typedef bool _cancel_type;
      _cancel_type cancel;

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
      varToArr(outbuffer + offset, length_gateway);
      offset += 4;
      memcpy(outbuffer + offset, this->gateway, length_gateway);
      offset += length_gateway;
      *(outbuffer + offset + 0) = (this->blacklist_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->blacklist_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->blacklist_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->blacklist_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->blacklist_length);
      for( uint32_t i = 0; i < blacklist_length; i++){
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
      arrToVar(length_gateway, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_gateway; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_gateway-1]=0;
      this->gateway = (char *)(inbuffer + offset-1);
      offset += length_gateway;
      uint32_t blacklist_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      blacklist_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      blacklist_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      blacklist_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->blacklist_length);
      if(blacklist_lengthT > blacklist_length)
        this->blacklist = (gateway_msgs::Rule*)realloc(this->blacklist, blacklist_lengthT * sizeof(gateway_msgs::Rule));
      blacklist_length = blacklist_lengthT;
      for( uint32_t i = 0; i < blacklist_length; i++){
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
      typedef int8_t _result_type;
      _result_type result;
      typedef const char* _error_message_type;
      _error_message_type error_message;

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
