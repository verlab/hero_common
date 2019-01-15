#ifndef _ROS_SERVICE_Topics_h
#define _ROS_SERVICE_Topics_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rosapi
{

static const char TOPICS[] = "rosapi/Topics";

  class TopicsRequest : public ros::Msg
  {
    public:

    TopicsRequest()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return TOPICS; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class TopicsResponse : public ros::Msg
  {
    public:
      uint32_t topics_length;
      typedef char* _topics_type;
      _topics_type st_topics;
      _topics_type * topics;
      uint32_t types_length;
      typedef char* _types_type;
      _types_type st_types;
      _types_type * types;

    TopicsResponse():
      topics_length(0), topics(NULL),
      types_length(0), types(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->topics_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->topics_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->topics_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->topics_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->topics_length);
      for( uint32_t i = 0; i < topics_length; i++){
      uint32_t length_topicsi = strlen(this->topics[i]);
      varToArr(outbuffer + offset, length_topicsi);
      offset += 4;
      memcpy(outbuffer + offset, this->topics[i], length_topicsi);
      offset += length_topicsi;
      }
      *(outbuffer + offset + 0) = (this->types_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->types_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->types_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->types_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->types_length);
      for( uint32_t i = 0; i < types_length; i++){
      uint32_t length_typesi = strlen(this->types[i]);
      varToArr(outbuffer + offset, length_typesi);
      offset += 4;
      memcpy(outbuffer + offset, this->types[i], length_typesi);
      offset += length_typesi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t topics_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      topics_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      topics_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      topics_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->topics_length);
      if(topics_lengthT > topics_length)
        this->topics = (char**)realloc(this->topics, topics_lengthT * sizeof(char*));
      topics_length = topics_lengthT;
      for( uint32_t i = 0; i < topics_length; i++){
      uint32_t length_st_topics;
      arrToVar(length_st_topics, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_topics; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_topics-1]=0;
      this->st_topics = (char *)(inbuffer + offset-1);
      offset += length_st_topics;
        memcpy( &(this->topics[i]), &(this->st_topics), sizeof(char*));
      }
      uint32_t types_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      types_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      types_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      types_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->types_length);
      if(types_lengthT > types_length)
        this->types = (char**)realloc(this->types, types_lengthT * sizeof(char*));
      types_length = types_lengthT;
      for( uint32_t i = 0; i < types_length; i++){
      uint32_t length_st_types;
      arrToVar(length_st_types, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_types; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_types-1]=0;
      this->st_types = (char *)(inbuffer + offset-1);
      offset += length_st_types;
        memcpy( &(this->types[i]), &(this->st_types), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return TOPICS; };
    const char * getMD5(){ return "d966d98fc333fa1f3135af765eac1ba8"; };

  };

  class Topics {
    public:
    typedef TopicsRequest Request;
    typedef TopicsResponse Response;
  };

}
#endif
