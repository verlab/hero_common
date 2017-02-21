#ifndef _ROS_SERVICE_Advertise_h
#define _ROS_SERVICE_Advertise_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "gateway_msgs/Rule.h"

namespace gateway_msgs
{

static const char ADVERTISE[] = "gateway_msgs/Advertise";

  class AdvertiseRequest : public ros::Msg
  {
    public:
      bool cancel;
      uint8_t rules_length;
      gateway_msgs::Rule st_rules;
      gateway_msgs::Rule * rules;

    AdvertiseRequest():
      cancel(0),
      rules_length(0), rules(NULL)
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
      *(outbuffer + offset++) = rules_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < rules_length; i++){
      offset += this->rules[i].serialize(outbuffer + offset);
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
      uint8_t rules_lengthT = *(inbuffer + offset++);
      if(rules_lengthT > rules_length)
        this->rules = (gateway_msgs::Rule*)realloc(this->rules, rules_lengthT * sizeof(gateway_msgs::Rule));
      offset += 3;
      rules_length = rules_lengthT;
      for( uint8_t i = 0; i < rules_length; i++){
      offset += this->st_rules.deserialize(inbuffer + offset);
        memcpy( &(this->rules[i]), &(this->st_rules), sizeof(gateway_msgs::Rule));
      }
     return offset;
    }

    const char * getType(){ return ADVERTISE; };
    const char * getMD5(){ return "85ef604243258e1594c5a7401f5e0339"; };

  };

  class AdvertiseResponse : public ros::Msg
  {
    public:
      int8_t result;
      const char* error_message;
      uint8_t watchlist_length;
      gateway_msgs::Rule st_watchlist;
      gateway_msgs::Rule * watchlist;

    AdvertiseResponse():
      result(0),
      error_message(""),
      watchlist_length(0), watchlist(NULL)
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
      *(outbuffer + offset++) = watchlist_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < watchlist_length; i++){
      offset += this->watchlist[i].serialize(outbuffer + offset);
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
      uint8_t watchlist_lengthT = *(inbuffer + offset++);
      if(watchlist_lengthT > watchlist_length)
        this->watchlist = (gateway_msgs::Rule*)realloc(this->watchlist, watchlist_lengthT * sizeof(gateway_msgs::Rule));
      offset += 3;
      watchlist_length = watchlist_lengthT;
      for( uint8_t i = 0; i < watchlist_length; i++){
      offset += this->st_watchlist.deserialize(inbuffer + offset);
        memcpy( &(this->watchlist[i]), &(this->st_watchlist), sizeof(gateway_msgs::Rule));
      }
     return offset;
    }

    const char * getType(){ return ADVERTISE; };
    const char * getMD5(){ return "c389af2721ca403446acba93862aff4f"; };

  };

  class Advertise {
    public:
    typedef AdvertiseRequest Request;
    typedef AdvertiseResponse Response;
  };

}
#endif
