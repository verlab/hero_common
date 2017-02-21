#ifndef _ROS_SERVICE_AdvertiseAll_h
#define _ROS_SERVICE_AdvertiseAll_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "gateway_msgs/Rule.h"

namespace gateway_msgs
{

static const char ADVERTISEALL[] = "gateway_msgs/AdvertiseAll";

  class AdvertiseAllRequest : public ros::Msg
  {
    public:
      bool cancel;
      uint8_t blacklist_length;
      gateway_msgs::Rule st_blacklist;
      gateway_msgs::Rule * blacklist;

    AdvertiseAllRequest():
      cancel(0),
      blacklist_length(0), blacklist(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_cancel;
      u_cancel.real = this->cancel;
      *(outbuffer + offset + 0) = (u_cancel.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->cancel);
      *(outbuffer + offset++) = blacklist_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < blacklist_length; i++){
      offset += this->blacklist[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_cancel;
      u_cancel.base = 0;
      u_cancel.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->cancel = u_cancel.real;
      offset += sizeof(this->cancel);
      uint8_t blacklist_lengthT = *(inbuffer + offset++);
      if(blacklist_lengthT > blacklist_length)
        this->blacklist = (gateway_msgs::Rule*)realloc(this->blacklist, blacklist_lengthT * sizeof(gateway_msgs::Rule));
      offset += 3;
      blacklist_length = blacklist_lengthT;
      for( uint8_t i = 0; i < blacklist_length; i++){
      offset += this->st_blacklist.deserialize(inbuffer + offset);
        memcpy( &(this->blacklist[i]), &(this->st_blacklist), sizeof(gateway_msgs::Rule));
      }
     return offset;
    }

    const char * getType(){ return ADVERTISEALL; };
    const char * getMD5(){ return "b9886afdbeb585f0929f1fe1334dd03e"; };

  };

  class AdvertiseAllResponse : public ros::Msg
  {
    public:
      int8_t result;
      const char* error_message;
      uint8_t blacklist_length;
      gateway_msgs::Rule st_blacklist;
      gateway_msgs::Rule * blacklist;

    AdvertiseAllResponse():
      result(0),
      error_message(""),
      blacklist_length(0), blacklist(NULL)
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
      *(outbuffer + offset++) = blacklist_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < blacklist_length; i++){
      offset += this->blacklist[i].serialize(outbuffer + offset);
      }
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
      uint8_t blacklist_lengthT = *(inbuffer + offset++);
      if(blacklist_lengthT > blacklist_length)
        this->blacklist = (gateway_msgs::Rule*)realloc(this->blacklist, blacklist_lengthT * sizeof(gateway_msgs::Rule));
      offset += 3;
      blacklist_length = blacklist_lengthT;
      for( uint8_t i = 0; i < blacklist_length; i++){
      offset += this->st_blacklist.deserialize(inbuffer + offset);
        memcpy( &(this->blacklist[i]), &(this->st_blacklist), sizeof(gateway_msgs::Rule));
      }
     return offset;
    }

    const char * getType(){ return ADVERTISEALL; };
    const char * getMD5(){ return "d9c8370d5d4ea835b3dd7ba52feee140"; };

  };

  class AdvertiseAll {
    public:
    typedef AdvertiseAllRequest Request;
    typedef AdvertiseAllResponse Response;
  };

}
#endif
