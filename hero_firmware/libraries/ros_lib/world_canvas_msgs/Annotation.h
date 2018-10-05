#ifndef _ROS_world_canvas_msgs_Annotation_h
#define _ROS_world_canvas_msgs_Annotation_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ros/time.h"
#include "uuid_msgs/UniqueID.h"
#include "std_msgs/ColorRGBA.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"

namespace world_canvas_msgs
{

  class Annotation : public ros::Msg
  {
    public:
      typedef ros::Time _timestamp_type;
      _timestamp_type timestamp;
      typedef uuid_msgs::UniqueID _id_type;
      _id_type id;
      typedef uuid_msgs::UniqueID _data_id_type;
      _data_id_type data_id;
      typedef const char* _world_type;
      _world_type world;
      typedef const char* _name_type;
      _name_type name;
      typedef const char* _type_type;
      _type_type type;
      typedef int32_t _shape_type;
      _shape_type shape;
      typedef std_msgs::ColorRGBA _color_type;
      _color_type color;
      typedef geometry_msgs::Vector3 _size_type;
      _size_type size;
      typedef geometry_msgs::PoseWithCovarianceStamped _pose_type;
      _pose_type pose;
      uint32_t keywords_length;
      typedef char* _keywords_type;
      _keywords_type st_keywords;
      _keywords_type * keywords;
      uint32_t relationships_length;
      typedef uuid_msgs::UniqueID _relationships_type;
      _relationships_type st_relationships;
      _relationships_type * relationships;

    Annotation():
      timestamp(),
      id(),
      data_id(),
      world(""),
      name(""),
      type(""),
      shape(0),
      color(),
      size(),
      pose(),
      keywords_length(0), keywords(NULL),
      relationships_length(0), relationships(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->timestamp.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->timestamp.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->timestamp.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->timestamp.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->timestamp.sec);
      *(outbuffer + offset + 0) = (this->timestamp.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->timestamp.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->timestamp.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->timestamp.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->timestamp.nsec);
      offset += this->id.serialize(outbuffer + offset);
      offset += this->data_id.serialize(outbuffer + offset);
      uint32_t length_world = strlen(this->world);
      varToArr(outbuffer + offset, length_world);
      offset += 4;
      memcpy(outbuffer + offset, this->world, length_world);
      offset += length_world;
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      uint32_t length_type = strlen(this->type);
      varToArr(outbuffer + offset, length_type);
      offset += 4;
      memcpy(outbuffer + offset, this->type, length_type);
      offset += length_type;
      union {
        int32_t real;
        uint32_t base;
      } u_shape;
      u_shape.real = this->shape;
      *(outbuffer + offset + 0) = (u_shape.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_shape.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_shape.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_shape.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->shape);
      offset += this->color.serialize(outbuffer + offset);
      offset += this->size.serialize(outbuffer + offset);
      offset += this->pose.serialize(outbuffer + offset);
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
      this->timestamp.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->timestamp.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->timestamp.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->timestamp.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->timestamp.sec);
      this->timestamp.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->timestamp.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->timestamp.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->timestamp.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->timestamp.nsec);
      offset += this->id.deserialize(inbuffer + offset);
      offset += this->data_id.deserialize(inbuffer + offset);
      uint32_t length_world;
      arrToVar(length_world, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_world; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_world-1]=0;
      this->world = (char *)(inbuffer + offset-1);
      offset += length_world;
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
      uint32_t length_type;
      arrToVar(length_type, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_type-1]=0;
      this->type = (char *)(inbuffer + offset-1);
      offset += length_type;
      union {
        int32_t real;
        uint32_t base;
      } u_shape;
      u_shape.base = 0;
      u_shape.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_shape.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_shape.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_shape.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->shape = u_shape.real;
      offset += sizeof(this->shape);
      offset += this->color.deserialize(inbuffer + offset);
      offset += this->size.deserialize(inbuffer + offset);
      offset += this->pose.deserialize(inbuffer + offset);
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

    const char * getType(){ return "world_canvas_msgs/Annotation"; };
    const char * getMD5(){ return "ad3b363d73f197c0fc0f70645a6b2598"; };

  };

}
#endif