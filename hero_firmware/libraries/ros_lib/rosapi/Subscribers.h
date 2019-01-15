#ifndef _ROS_SERVICE_Subscribers_h
#define _ROS_SERVICE_Subscribers_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rosapi
{

static const char SUBSCRIBERS[] = "rosapi/Subscribers";

  class SubscribersRequest : public ros::Msg
  {
    public:
      typedef const char* _topic_type;
      _topic_type topic;

    SubscribersRequest():
      topic("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_topic = strlen(this->topic);
      varToArr(outbuffer + offset, length_topic);
      offset += 4;
      memcpy(outbuffer + offset, this->topic, length_topic);
      offset += length_topic;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_topic;
      arrToVar(length_topic, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_topic; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_topic-1]=0;
      this->topic = (char *)(inbuffer + offset-1);
      offset += length_topic;
     return offset;
    }

    const char * getType(){ return SUBSCRIBERS; };
    const char * getMD5(){ return "d8f94bae31b356b24d0427f80426d0c3"; };

  };

  class SubscribersResponse : public ros::Msg
  {
    public:
      uint32_t subscribers_length;
      typedef char* _subscribers_type;
      _subscribers_type st_subscribers;
      _subscribers_type * subscribers;

    SubscribersResponse():
      subscribers_length(0), subscribers(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->subscribers_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->subscribers_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->subscribers_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->subscribers_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->subscribers_length);
      for( uint32_t i = 0; i < subscribers_length; i++){
      uint32_t length_subscribersi = strlen(this->subscribers[i]);
      varToArr(outbuffer + offset, length_subscribersi);
      offset += 4;
      memcpy(outbuffer + offset, this->subscribers[i], length_subscribersi);
      offset += length_subscribersi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t subscribers_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      subscribers_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      subscribers_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      subscribers_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->subscribers_length);
      if(subscribers_lengthT > subscribers_length)
        this->subscribers = (char**)realloc(this->subscribers, subscribers_lengthT * sizeof(char*));
      subscribers_length = subscribers_lengthT;
      for( uint32_t i = 0; i < subscribers_length; i++){
      uint32_t length_st_subscribers;
      arrToVar(length_st_subscribers, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_subscribers; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_subscribers-1]=0;
      this->st_subscribers = (char *)(inbuffer + offset-1);
      offset += length_st_subscribers;
        memcpy( &(this->subscribers[i]), &(this->st_subscribers), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return SUBSCRIBERS; };
    const char * getMD5(){ return "22418cab5ba9531d8c2b738b4e56153b"; };

  };

  class Subscribers {
    public:
    typedef SubscribersRequest Request;
    typedef SubscribersResponse Response;
  };

}
#endif
