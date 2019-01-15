#ifndef _ROS_variant_msgs_Test_h
#define _ROS_variant_msgs_Test_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "std_msgs/Bool.h"
#include "std_msgs/String.h"

namespace variant_msgs
{

  class Test : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef int32_t _builtin_int_type;
      _builtin_int_type builtin_int;
      typedef bool _builtin_boolean_type;
      _builtin_boolean_type builtin_boolean;
      typedef std_msgs::Bool _boolean_type;
      _boolean_type boolean;
      typedef const char* _builtin_string_type;
      _builtin_string_type builtin_string;
      typedef std_msgs::String _string_type;
      _string_type string;
      int32_t builtin_int_array[3];
      uint32_t builtin_int_vector_length;
      typedef int32_t _builtin_int_vector_type;
      _builtin_int_vector_type st_builtin_int_vector;
      _builtin_int_vector_type * builtin_int_vector;
      std_msgs::String string_array[3];
      uint32_t string_vector_length;
      typedef std_msgs::String _string_vector_type;
      _string_vector_type st_string_vector;
      _string_vector_type * string_vector;
      bool builtin_boolean_array[3];
      enum { byte_constant =  42 };

    Test():
      header(),
      builtin_int(0),
      builtin_boolean(0),
      boolean(),
      builtin_string(""),
      string(),
      builtin_int_array(),
      builtin_int_vector_length(0), builtin_int_vector(NULL),
      string_array(),
      string_vector_length(0), string_vector(NULL),
      builtin_boolean_array()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_builtin_int;
      u_builtin_int.real = this->builtin_int;
      *(outbuffer + offset + 0) = (u_builtin_int.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_builtin_int.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_builtin_int.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_builtin_int.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->builtin_int);
      union {
        bool real;
        uint8_t base;
      } u_builtin_boolean;
      u_builtin_boolean.real = this->builtin_boolean;
      *(outbuffer + offset + 0) = (u_builtin_boolean.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->builtin_boolean);
      offset += this->boolean.serialize(outbuffer + offset);
      uint32_t length_builtin_string = strlen(this->builtin_string);
      varToArr(outbuffer + offset, length_builtin_string);
      offset += 4;
      memcpy(outbuffer + offset, this->builtin_string, length_builtin_string);
      offset += length_builtin_string;
      offset += this->string.serialize(outbuffer + offset);
      for( uint32_t i = 0; i < 3; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_builtin_int_arrayi;
      u_builtin_int_arrayi.real = this->builtin_int_array[i];
      *(outbuffer + offset + 0) = (u_builtin_int_arrayi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_builtin_int_arrayi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_builtin_int_arrayi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_builtin_int_arrayi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->builtin_int_array[i]);
      }
      *(outbuffer + offset + 0) = (this->builtin_int_vector_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->builtin_int_vector_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->builtin_int_vector_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->builtin_int_vector_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->builtin_int_vector_length);
      for( uint32_t i = 0; i < builtin_int_vector_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_builtin_int_vectori;
      u_builtin_int_vectori.real = this->builtin_int_vector[i];
      *(outbuffer + offset + 0) = (u_builtin_int_vectori.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_builtin_int_vectori.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_builtin_int_vectori.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_builtin_int_vectori.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->builtin_int_vector[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      offset += this->string_array[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->string_vector_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->string_vector_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->string_vector_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->string_vector_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->string_vector_length);
      for( uint32_t i = 0; i < string_vector_length; i++){
      offset += this->string_vector[i].serialize(outbuffer + offset);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        bool real;
        uint8_t base;
      } u_builtin_boolean_arrayi;
      u_builtin_boolean_arrayi.real = this->builtin_boolean_array[i];
      *(outbuffer + offset + 0) = (u_builtin_boolean_arrayi.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->builtin_boolean_array[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_builtin_int;
      u_builtin_int.base = 0;
      u_builtin_int.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_builtin_int.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_builtin_int.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_builtin_int.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->builtin_int = u_builtin_int.real;
      offset += sizeof(this->builtin_int);
      union {
        bool real;
        uint8_t base;
      } u_builtin_boolean;
      u_builtin_boolean.base = 0;
      u_builtin_boolean.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->builtin_boolean = u_builtin_boolean.real;
      offset += sizeof(this->builtin_boolean);
      offset += this->boolean.deserialize(inbuffer + offset);
      uint32_t length_builtin_string;
      arrToVar(length_builtin_string, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_builtin_string; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_builtin_string-1]=0;
      this->builtin_string = (char *)(inbuffer + offset-1);
      offset += length_builtin_string;
      offset += this->string.deserialize(inbuffer + offset);
      for( uint32_t i = 0; i < 3; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_builtin_int_arrayi;
      u_builtin_int_arrayi.base = 0;
      u_builtin_int_arrayi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_builtin_int_arrayi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_builtin_int_arrayi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_builtin_int_arrayi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->builtin_int_array[i] = u_builtin_int_arrayi.real;
      offset += sizeof(this->builtin_int_array[i]);
      }
      uint32_t builtin_int_vector_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      builtin_int_vector_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      builtin_int_vector_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      builtin_int_vector_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->builtin_int_vector_length);
      if(builtin_int_vector_lengthT > builtin_int_vector_length)
        this->builtin_int_vector = (int32_t*)realloc(this->builtin_int_vector, builtin_int_vector_lengthT * sizeof(int32_t));
      builtin_int_vector_length = builtin_int_vector_lengthT;
      for( uint32_t i = 0; i < builtin_int_vector_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_builtin_int_vector;
      u_st_builtin_int_vector.base = 0;
      u_st_builtin_int_vector.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_builtin_int_vector.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_builtin_int_vector.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_builtin_int_vector.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_builtin_int_vector = u_st_builtin_int_vector.real;
      offset += sizeof(this->st_builtin_int_vector);
        memcpy( &(this->builtin_int_vector[i]), &(this->st_builtin_int_vector), sizeof(int32_t));
      }
      for( uint32_t i = 0; i < 3; i++){
      offset += this->string_array[i].deserialize(inbuffer + offset);
      }
      uint32_t string_vector_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      string_vector_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      string_vector_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      string_vector_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->string_vector_length);
      if(string_vector_lengthT > string_vector_length)
        this->string_vector = (std_msgs::String*)realloc(this->string_vector, string_vector_lengthT * sizeof(std_msgs::String));
      string_vector_length = string_vector_lengthT;
      for( uint32_t i = 0; i < string_vector_length; i++){
      offset += this->st_string_vector.deserialize(inbuffer + offset);
        memcpy( &(this->string_vector[i]), &(this->st_string_vector), sizeof(std_msgs::String));
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        bool real;
        uint8_t base;
      } u_builtin_boolean_arrayi;
      u_builtin_boolean_arrayi.base = 0;
      u_builtin_boolean_arrayi.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->builtin_boolean_array[i] = u_builtin_boolean_arrayi.real;
      offset += sizeof(this->builtin_boolean_array[i]);
      }
     return offset;
    }

    const char * getType(){ return "variant_msgs/Test"; };
    const char * getMD5(){ return "17d92d9cea3499753cb392766b3203a1"; };

  };

}
#endif