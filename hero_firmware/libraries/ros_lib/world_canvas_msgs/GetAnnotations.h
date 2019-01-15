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
      typedef const char* _world_type;
      _world_type world;
      uint32_t ids_length;
      typedef uuid_msgs::UniqueID _ids_type;
      _ids_type st_ids;
      _ids_type * ids;
      uint32_t names_length;
      typedef char* _names_type;
      _names_type st_names;
      _names_type * names;
      uint32_t types_length;
      typedef char* _types_type;
      _types_type st_types;
      _types_type * types;
      uint32_t keywords_length;
      typedef char* _keywords_type;
      _keywords_type st_keywords;
      _keywords_type * keywords;
      uint32_t relationships_length;
      typedef uuid_msgs::UniqueID _relationships_type;
      _relationships_type st_relationships;
      _relationships_type * relationships;

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
      varToArr(outbuffer + offset, length_world);
      offset += 4;
      memcpy(outbuffer + offset, this->world, length_world);
      offset += length_world;
      *(outbuffer + offset + 0) = (this->ids_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->ids_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->ids_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->ids_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ids_length);
      for( uint32_t i = 0; i < ids_length; i++){
      offset += this->ids[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->names_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->names_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->names_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->names_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->names_length);
      for( uint32_t i = 0; i < names_length; i++){
      uint32_t length_namesi = strlen(this->names[i]);
      varToArr(outbuffer + offset, length_namesi);
      offset += 4;
      memcpy(outbuffer + offset, this->names[i], length_namesi);
      offset += length_namesi;
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
      *(outbuffer + offset + 0) = (this->keywords_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->keywords_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->keywords_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->keywords_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->keywords_length);
      for( uint32_t i = 0; i < keywords_length; i++){
      uint32_t length_keywordsi = strlen(this->keywords[i]);
      varToArr(outbuffer + offset, length_keywordsi);
      offset += 4;
      memcpy(outbuffer + offset, this->keywords[i], length_keywordsi);
      offset += length_keywordsi;
      }
      *(outbuffer + offset + 0) = (this->relationships_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->relationships_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->relationships_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->relationships_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->relationships_length);
      for( uint32_t i = 0; i < relationships_length; i++){
      offset += this->relationships[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_world;
      arrToVar(length_world, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_world; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_world-1]=0;
      this->world = (char *)(inbuffer + offset-1);
      offset += length_world;
      uint32_t ids_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      ids_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      ids_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      ids_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->ids_length);
      if(ids_lengthT > ids_length)
        this->ids = (uuid_msgs::UniqueID*)realloc(this->ids, ids_lengthT * sizeof(uuid_msgs::UniqueID));
      ids_length = ids_lengthT;
      for( uint32_t i = 0; i < ids_length; i++){
      offset += this->st_ids.deserialize(inbuffer + offset);
        memcpy( &(this->ids[i]), &(this->st_ids), sizeof(uuid_msgs::UniqueID));
      }
      uint32_t names_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      names_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      names_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      names_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->names_length);
      if(names_lengthT > names_length)
        this->names = (char**)realloc(this->names, names_lengthT * sizeof(char*));
      names_length = names_lengthT;
      for( uint32_t i = 0; i < names_length; i++){
      uint32_t length_st_names;
      arrToVar(length_st_names, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_names; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_names-1]=0;
      this->st_names = (char *)(inbuffer + offset-1);
      offset += length_st_names;
        memcpy( &(this->names[i]), &(this->st_names), sizeof(char*));
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
      uint32_t keywords_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      keywords_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      keywords_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      keywords_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->keywords_length);
      if(keywords_lengthT > keywords_length)
        this->keywords = (char**)realloc(this->keywords, keywords_lengthT * sizeof(char*));
      keywords_length = keywords_lengthT;
      for( uint32_t i = 0; i < keywords_length; i++){
      uint32_t length_st_keywords;
      arrToVar(length_st_keywords, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_keywords; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_keywords-1]=0;
      this->st_keywords = (char *)(inbuffer + offset-1);
      offset += length_st_keywords;
        memcpy( &(this->keywords[i]), &(this->st_keywords), sizeof(char*));
      }
      uint32_t relationships_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      relationships_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      relationships_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      relationships_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->relationships_length);
      if(relationships_lengthT > relationships_length)
        this->relationships = (uuid_msgs::UniqueID*)realloc(this->relationships, relationships_lengthT * sizeof(uuid_msgs::UniqueID));
      relationships_length = relationships_lengthT;
      for( uint32_t i = 0; i < relationships_length; i++){
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
      typedef bool _result_type;
      _result_type result;
      typedef const char* _message_type;
      _message_type message;
      uint32_t annotations_length;
      typedef world_canvas_msgs::Annotation _annotations_type;
      _annotations_type st_annotations;
      _annotations_type * annotations;

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
      varToArr(outbuffer + offset, length_message);
      offset += 4;
      memcpy(outbuffer + offset, this->message, length_message);
      offset += length_message;
      *(outbuffer + offset + 0) = (this->annotations_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->annotations_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->annotations_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->annotations_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->annotations_length);
      for( uint32_t i = 0; i < annotations_length; i++){
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
      arrToVar(length_message, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_message-1]=0;
      this->message = (char *)(inbuffer + offset-1);
      offset += length_message;
      uint32_t annotations_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      annotations_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      annotations_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      annotations_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->annotations_length);
      if(annotations_lengthT > annotations_length)
        this->annotations = (world_canvas_msgs::Annotation*)realloc(this->annotations, annotations_lengthT * sizeof(world_canvas_msgs::Annotation));
      annotations_length = annotations_lengthT;
      for( uint32_t i = 0; i < annotations_length; i++){
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
