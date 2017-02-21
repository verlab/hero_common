#ifndef _ROS_SERVICE_GetAnnotations_h
#define _ROS_SERVICE_GetAnnotations_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "uuid_msgs/UniqueID.h"
#include "world_canvas_msgs/Annotation.h"

namespace world_canvas_msgs
{

static const char GETANNOTATIONS[] = "world_canvas_msgs/GetAnnotations";

  class GetAnnotationsRequest : public ros::Msg
  {
    public:
      const char* world;
      uint8_t ids_length;
      uuid_msgs::UniqueID st_ids;
      uuid_msgs::UniqueID * ids;
      uint8_t names_length;
      char* st_names;
      char* * names;
      uint8_t types_length;
      char* st_types;
      char* * types;
      uint8_t keywords_length;
      char* st_keywords;
      char* * keywords;
      uint8_t relationships_length;
      uuid_msgs::UniqueID st_relationships;
      uuid_msgs::UniqueID * relationships;

    GetAnnotationsRequest():
      world(""),
      ids_length(0), ids(NULL),
      names_length(0), names(NULL),
      types_length(0), types(NULL),
      keywords_length(0), keywords(NULL),
      relationships_length(0), relationships(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_world = strlen(this->world);
      memcpy(outbuffer + offset, &length_world, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->world, length_world);
      offset += length_world;
      *(outbuffer + offset++) = ids_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < ids_length; i++){
      offset += this->ids[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = names_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < names_length; i++){
      uint32_t length_namesi = strlen(this->names[i]);
      memcpy(outbuffer + offset, &length_namesi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->names[i], length_namesi);
      offset += length_namesi;
      }
      *(outbuffer + offset++) = types_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < types_length; i++){
      uint32_t length_typesi = strlen(this->types[i]);
      memcpy(outbuffer + offset, &length_typesi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->types[i], length_typesi);
      offset += length_typesi;
      }
      *(outbuffer + offset++) = keywords_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < keywords_length; i++){
      uint32_t length_keywordsi = strlen(this->keywords[i]);
      memcpy(outbuffer + offset, &length_keywordsi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->keywords[i], length_keywordsi);
      offset += length_keywordsi;
      }
      *(outbuffer + offset++) = relationships_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < relationships_length; i++){
      offset += this->relationships[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_world;
      memcpy(&length_world, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_world; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_world-1]=0;
      this->world = (char *)(inbuffer + offset-1);
      offset += length_world;
      uint8_t ids_lengthT = *(inbuffer + offset++);
      if(ids_lengthT > ids_length)
        this->ids = (uuid_msgs::UniqueID*)realloc(this->ids, ids_lengthT * sizeof(uuid_msgs::UniqueID));
      offset += 3;
      ids_length = ids_lengthT;
      for( uint8_t i = 0; i < ids_length; i++){
      offset += this->st_ids.deserialize(inbuffer + offset);
        memcpy( &(this->ids[i]), &(this->st_ids), sizeof(uuid_msgs::UniqueID));
      }
      uint8_t names_lengthT = *(inbuffer + offset++);
      if(names_lengthT > names_length)
        this->names = (char**)realloc(this->names, names_lengthT * sizeof(char*));
      offset += 3;
      names_length = names_lengthT;
      for( uint8_t i = 0; i < names_length; i++){
      uint32_t length_st_names;
      memcpy(&length_st_names, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_names; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_names-1]=0;
      this->st_names = (char *)(inbuffer + offset-1);
      offset += length_st_names;
        memcpy( &(this->names[i]), &(this->st_names), sizeof(char*));
      }
      uint8_t types_lengthT = *(inbuffer + offset++);
      if(types_lengthT > types_length)
        this->types = (char**)realloc(this->types, types_lengthT * sizeof(char*));
      offset += 3;
      types_length = types_lengthT;
      for( uint8_t i = 0; i < types_length; i++){
      uint32_t length_st_types;
      memcpy(&length_st_types, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_types; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_types-1]=0;
      this->st_types = (char *)(inbuffer + offset-1);
      offset += length_st_types;
        memcpy( &(this->types[i]), &(this->st_types), sizeof(char*));
      }
      uint8_t keywords_lengthT = *(inbuffer + offset++);
      if(keywords_lengthT > keywords_length)
        this->keywords = (char**)realloc(this->keywords, keywords_lengthT * sizeof(char*));
      offset += 3;
      keywords_length = keywords_lengthT;
      for( uint8_t i = 0; i < keywords_length; i++){
      uint32_t length_st_keywords;
      memcpy(&length_st_keywords, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_keywords; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_keywords-1]=0;
      this->st_keywords = (char *)(inbuffer + offset-1);
      offset += length_st_keywords;
        memcpy( &(this->keywords[i]), &(this->st_keywords), sizeof(char*));
      }
      uint8_t relationships_lengthT = *(inbuffer + offset++);
      if(relationships_lengthT > relationships_length)
        this->relationships = (uuid_msgs::UniqueID*)realloc(this->relationships, relationships_lengthT * sizeof(uuid_msgs::UniqueID));
      offset += 3;
      relationships_length = relationships_lengthT;
      for( uint8_t i = 0; i < relationships_length; i++){
      offset += this->st_relationships.deserialize(inbuffer + offset);
        memcpy( &(this->relationships[i]), &(this->st_relationships), sizeof(uuid_msgs::UniqueID));
      }
     return offset;
    }

    const char * getType(){ return GETANNOTATIONS; };
    const char * getMD5(){ return "a83f9980d7efa66065c5d298416d8283"; };

  };

  class GetAnnotationsResponse : public ros::Msg
  {
    public:
      bool result;
      const char* message;
      uint8_t annotations_length;
      world_canvas_msgs::Annotation st_annotations;
      world_canvas_msgs::Annotation * annotations;

    GetAnnotationsResponse():
      result(0),
      message(""),
      annotations_length(0), annotations(NULL)
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
      memcpy(outbuffer + offset, &length_message, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->message, length_message);
      offset += length_message;
      *(outbuffer + offset++) = annotations_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < annotations_length; i++){
      offset += this->annotations[i].serialize(outbuffer + offset);
      }
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
      memcpy(&length_message, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_message-1]=0;
      this->message = (char *)(inbuffer + offset-1);
      offset += length_message;
      uint8_t annotations_lengthT = *(inbuffer + offset++);
      if(annotations_lengthT > annotations_length)
        this->annotations = (world_canvas_msgs::Annotation*)realloc(this->annotations, annotations_lengthT * sizeof(world_canvas_msgs::Annotation));
      offset += 3;
      annotations_length = annotations_lengthT;
      for( uint8_t i = 0; i < annotations_length; i++){
      offset += this->st_annotations.deserialize(inbuffer + offset);
        memcpy( &(this->annotations[i]), &(this->st_annotations), sizeof(world_canvas_msgs::Annotation));
      }
     return offset;
    }

    const char * getType(){ return GETANNOTATIONS; };
    const char * getMD5(){ return "3f08a089ab5c7535a0df505d2a3c7fd4"; };

  };

  class GetAnnotations {
    public:
    typedef GetAnnotationsRequest Request;
    typedef GetAnnotationsResponse Response;
  };

}
#endif
