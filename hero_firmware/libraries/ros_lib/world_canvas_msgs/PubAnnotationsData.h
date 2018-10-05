#ifndef _ROS_SERVICE_PubAnnotationsData_h
#define _ROS_SERVICE_PubAnnotationsData_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "uuid_msgs/UniqueID.h"

namespace world_canvas_msgs
{

static const char PUBANNOTATIONSDATA[] = "world_canvas_msgs/PubAnnotationsData";

  class PubAnnotationsDataRequest : public ros::Msg
  {
    public:
      uint32_t annotation_ids_length;
      typedef uuid_msgs::UniqueID _annotation_ids_type;
      _annotation_ids_type st_annotation_ids;
      _annotation_ids_type * annotation_ids;
      typedef const char* _topic_name_type;
      _topic_name_type topic_name;
      typedef const char* _topic_type_type;
      _topic_type_type topic_type;
      typedef bool _pub_as_list_type;
      _pub_as_list_type pub_as_list;

    PubAnnotationsDataRequest():
      annotation_ids_length(0), annotation_ids(NULL),
      topic_name(""),
      topic_type(""),
      pub_as_list(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->annotation_ids_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->annotation_ids_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->annotation_ids_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->annotation_ids_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->annotation_ids_length);
      for( uint32_t i = 0; i < annotation_ids_length; i++){
      offset += this->annotation_ids[i].serialize(outbuffer + offset);
      }
      uint32_t length_topic_name = strlen(this->topic_name);
      varToArr(outbuffer + offset, length_topic_name);
      offset += 4;
      memcpy(outbuffer + offset, this->topic_name, length_topic_name);
      offset += length_topic_name;
      uint32_t length_topic_type = strlen(this->topic_type);
      varToArr(outbuffer + offset, length_topic_type);
      offset += 4;
      memcpy(outbuffer + offset, this->topic_type, length_topic_type);
      offset += length_topic_type;
      union {
        bool real;
        uint8_t base;
      } u_pub_as_list;
      u_pub_as_list.real = this->pub_as_list;
      *(outbuffer + offset + 0) = (u_pub_as_list.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pub_as_list);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t annotation_ids_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      annotation_ids_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      annotation_ids_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      annotation_ids_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->annotation_ids_length);
      if(annotation_ids_lengthT > annotation_ids_length)
        this->annotation_ids = (uuid_msgs::UniqueID*)realloc(this->annotation_ids, annotation_ids_lengthT * sizeof(uuid_msgs::UniqueID));
      annotation_ids_length = annotation_ids_lengthT;
      for( uint32_t i = 0; i < annotation_ids_length; i++){
      offset += this->st_annotation_ids.deserialize(inbuffer + offset);
        memcpy( &(this->annotation_ids[i]), &(this->st_annotation_ids), sizeof(uuid_msgs::UniqueID));
      }
      uint32_t length_topic_name;
      arrToVar(length_topic_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_topic_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_topic_name-1]=0;
      this->topic_name = (char *)(inbuffer + offset-1);
      offset += length_topic_name;
      uint32_t length_topic_type;
      arrToVar(length_topic_type, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_topic_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_topic_type-1]=0;
      this->topic_type = (char *)(inbuffer + offset-1);
      offset += length_topic_type;
      union {
        bool real;
        uint8_t base;
      } u_pub_as_list;
      u_pub_as_list.base = 0;
      u_pub_as_list.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->pub_as_list = u_pub_as_list.real;
      offset += sizeof(this->pub_as_list);
     return offset;
    }

    const char * getType(){ return PUBANNOTATIONSDATA; };
    const char * getMD5(){ return "1f37618ab20aa1492050e9599baf8ad0"; };

  };

  class PubAnnotationsDataResponse : public ros::Msg
  {
    public:
      typedef bool _result_type;
      _result_type result;
      typedef const char* _message_type;
      _message_type message;

    PubAnnotationsDataResponse():
      result(0),
      message("")
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
      uint32_t length_message = strlen(this->message);
      varToArr(outbuffer + offset, length_message);
      offset += 4;
      memcpy(outbuffer + offset, this->message, length_message);
      offset += length_message;
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
      uint32_t length_message;
      arrToVar(length_message, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_message-1]=0;
      this->message = (char *)(inbuffer + offset-1);
      offset += length_message;
     return offset;
    }

    const char * getType(){ return PUBANNOTATIONSDATA; };
    const char * getMD5(){ return "b543fbd3518c791be28589b850702201"; };

  };

  class PubAnnotationsData {
    public:
    typedef PubAnnotationsDataRequest Request;
    typedef PubAnnotationsDataResponse Response;
  };

}
#endif
