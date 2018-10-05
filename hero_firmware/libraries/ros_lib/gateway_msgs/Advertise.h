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
      typedef bool _cancel_type;
      _cancel_type cancel;
      uint32_t rules_length;
      typedef gateway_msgs::Rule _rules_type;
      _rules_type st_rules;
      _rules_type * rules;

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
      *(outbuffer + offset + 0) = (this->rules_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->rules_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->rules_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->rules_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rules_length);
      for( uint32_t i = 0; i < rules_length; i++){
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
      uint32_t rules_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      rules_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      rules_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      rules_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->rules_length);
      if(rules_lengthT > rules_length)
        this->rules = (gateway_msgs::Rule*)realloc(this->rules, rules_lengthT * sizeof(gateway_msgs::Rule));
      rules_length = rules_lengthT;
      for( uint32_t i = 0; i < rules_length; i++){
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
      typedef int8_t _result_type;
      _result_type result;
      typedef const char* _error_message_type;
      _error_message_type error_message;
      uint32_t watchlist_length;
      typedef gateway_msgs::Rule _watchlist_type;
      _watchlist_type st_watchlist;
      _watchlist_type * watchlist;

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
      varToArr(outbuffer + offset, length_error_message);
      offset += 4;
      memcpy(outbuffer + offset, this->error_message, length_error_message);
      offset += length_error_message;
      *(outbuffer + offset + 0) = (this->watchlist_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->watchlist_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->watchlist_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->watchlist_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->watchlist_length);
      for( uint32_t i = 0; i < watchlist_length; i++){
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
      arrToVar(length_error_message, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_error_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_error_message-1]=0;
      this->error_message = (char *)(inbuffer + offset-1);
      offset += length_error_message;
      uint32_t watchlist_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      watchlist_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      watchlist_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      watchlist_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->watchlist_length);
      if(watchlist_lengthT > watchlist_length)
        this->watchlist = (gateway_msgs::Rule*)realloc(this->watchlist, watchlist_lengthT * sizeof(gateway_msgs::Rule));
      watchlist_length = watchlist_lengthT;
      for( uint32_t i = 0; i < watchlist_length; i++){
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
