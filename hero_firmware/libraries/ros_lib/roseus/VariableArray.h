#ifndef _ROS_roseus_VariableArray_h
#define _ROS_roseus_VariableArray_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ros/time.h"
#include "ros/duration.h"
#include "std_msgs/String.h"

namespace roseus
{

  class VariableArray : public ros::Msg
  {
    public:
      uint32_t float32_data_length;
      typedef float _float32_data_type;
      _float32_data_type st_float32_data;
      _float32_data_type * float32_data;
      uint32_t float64_data_length;
      typedef float _float64_data_type;
      _float64_data_type st_float64_data;
      _float64_data_type * float64_data;
      uint32_t int16_data_length;
      typedef int16_t _int16_data_type;
      _int16_data_type st_int16_data;
      _int16_data_type * int16_data;
      uint32_t int32_data_length;
      typedef int32_t _int32_data_type;
      _int32_data_type st_int32_data;
      _int32_data_type * int32_data;
      uint32_t int64_data_length;
      typedef int64_t _int64_data_type;
      _int64_data_type st_int64_data;
      _int64_data_type * int64_data;
      uint32_t int8_data_length;
      typedef int8_t _int8_data_type;
      _int8_data_type st_int8_data;
      _int8_data_type * int8_data;
      uint32_t uint16_data_length;
      typedef uint16_t _uint16_data_type;
      _uint16_data_type st_uint16_data;
      _uint16_data_type * uint16_data;
      uint32_t uint32_data_length;
      typedef uint32_t _uint32_data_type;
      _uint32_data_type st_uint32_data;
      _uint32_data_type * uint32_data;
      uint32_t uint64_data_length;
      typedef uint64_t _uint64_data_type;
      _uint64_data_type st_uint64_data;
      _uint64_data_type * uint64_data;
      uint32_t uint8_data_length;
      typedef uint8_t _uint8_data_type;
      _uint8_data_type st_uint8_data;
      _uint8_data_type * uint8_data;
      uint32_t bool_data_length;
      typedef bool _bool_data_type;
      _bool_data_type st_bool_data;
      _bool_data_type * bool_data;
      uint32_t time_data_length;
      typedef ros::Time _time_data_type;
      _time_data_type st_time_data;
      _time_data_type * time_data;
      uint32_t duration_data_length;
      typedef ros::Duration _duration_data_type;
      _duration_data_type st_duration_data;
      _duration_data_type * duration_data;
      uint32_t string_data_length;
      typedef std_msgs::String _string_data_type;
      _string_data_type st_string_data;
      _string_data_type * string_data;

    VariableArray():
      float32_data_length(0), float32_data(NULL),
      float64_data_length(0), float64_data(NULL),
      int16_data_length(0), int16_data(NULL),
      int32_data_length(0), int32_data(NULL),
      int64_data_length(0), int64_data(NULL),
      int8_data_length(0), int8_data(NULL),
      uint16_data_length(0), uint16_data(NULL),
      uint32_data_length(0), uint32_data(NULL),
      uint64_data_length(0), uint64_data(NULL),
      uint8_data_length(0), uint8_data(NULL),
      bool_data_length(0), bool_data(NULL),
      time_data_length(0), time_data(NULL),
      duration_data_length(0), duration_data(NULL),
      string_data_length(0), string_data(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->float32_data_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->float32_data_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->float32_data_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->float32_data_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->float32_data_length);
      for( uint32_t i = 0; i < float32_data_length; i++){
      union {
        float real;
        uint32_t base;
      } u_float32_datai;
      u_float32_datai.real = this->float32_data[i];
      *(outbuffer + offset + 0) = (u_float32_datai.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_float32_datai.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_float32_datai.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_float32_datai.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->float32_data[i]);
      }
      *(outbuffer + offset + 0) = (this->float64_data_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->float64_data_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->float64_data_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->float64_data_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->float64_data_length);
      for( uint32_t i = 0; i < float64_data_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->float64_data[i]);
      }
      *(outbuffer + offset + 0) = (this->int16_data_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->int16_data_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->int16_data_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->int16_data_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->int16_data_length);
      for( uint32_t i = 0; i < int16_data_length; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_int16_datai;
      u_int16_datai.real = this->int16_data[i];
      *(outbuffer + offset + 0) = (u_int16_datai.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_int16_datai.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->int16_data[i]);
      }
      *(outbuffer + offset + 0) = (this->int32_data_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->int32_data_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->int32_data_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->int32_data_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->int32_data_length);
      for( uint32_t i = 0; i < int32_data_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_int32_datai;
      u_int32_datai.real = this->int32_data[i];
      *(outbuffer + offset + 0) = (u_int32_datai.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_int32_datai.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_int32_datai.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_int32_datai.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->int32_data[i]);
      }
      *(outbuffer + offset + 0) = (this->int64_data_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->int64_data_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->int64_data_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->int64_data_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->int64_data_length);
      for( uint32_t i = 0; i < int64_data_length; i++){
      union {
        int64_t real;
        uint64_t base;
      } u_int64_datai;
      u_int64_datai.real = this->int64_data[i];
      *(outbuffer + offset + 0) = (u_int64_datai.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_int64_datai.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_int64_datai.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_int64_datai.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_int64_datai.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_int64_datai.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_int64_datai.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_int64_datai.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->int64_data[i]);
      }
      *(outbuffer + offset + 0) = (this->int8_data_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->int8_data_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->int8_data_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->int8_data_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->int8_data_length);
      for( uint32_t i = 0; i < int8_data_length; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_int8_datai;
      u_int8_datai.real = this->int8_data[i];
      *(outbuffer + offset + 0) = (u_int8_datai.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->int8_data[i]);
      }
      *(outbuffer + offset + 0) = (this->uint16_data_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->uint16_data_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->uint16_data_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->uint16_data_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->uint16_data_length);
      for( uint32_t i = 0; i < uint16_data_length; i++){
      *(outbuffer + offset + 0) = (this->uint16_data[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->uint16_data[i] >> (8 * 1)) & 0xFF;
      offset += sizeof(this->uint16_data[i]);
      }
      *(outbuffer + offset + 0) = (this->uint32_data_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->uint32_data_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->uint32_data_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->uint32_data_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->uint32_data_length);
      for( uint32_t i = 0; i < uint32_data_length; i++){
      *(outbuffer + offset + 0) = (this->uint32_data[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->uint32_data[i] >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->uint32_data[i] >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->uint32_data[i] >> (8 * 3)) & 0xFF;
      offset += sizeof(this->uint32_data[i]);
      }
      *(outbuffer + offset + 0) = (this->uint64_data_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->uint64_data_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->uint64_data_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->uint64_data_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->uint64_data_length);
      for( uint32_t i = 0; i < uint64_data_length; i++){
      *(outbuffer + offset + 0) = (this->uint64_data[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->uint64_data[i] >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->uint64_data[i] >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->uint64_data[i] >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (this->uint64_data[i] >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (this->uint64_data[i] >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (this->uint64_data[i] >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (this->uint64_data[i] >> (8 * 7)) & 0xFF;
      offset += sizeof(this->uint64_data[i]);
      }
      *(outbuffer + offset + 0) = (this->uint8_data_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->uint8_data_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->uint8_data_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->uint8_data_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->uint8_data_length);
      for( uint32_t i = 0; i < uint8_data_length; i++){
      *(outbuffer + offset + 0) = (this->uint8_data[i] >> (8 * 0)) & 0xFF;
      offset += sizeof(this->uint8_data[i]);
      }
      *(outbuffer + offset + 0) = (this->bool_data_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->bool_data_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->bool_data_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->bool_data_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->bool_data_length);
      for( uint32_t i = 0; i < bool_data_length; i++){
      union {
        bool real;
        uint8_t base;
      } u_bool_datai;
      u_bool_datai.real = this->bool_data[i];
      *(outbuffer + offset + 0) = (u_bool_datai.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->bool_data[i]);
      }
      *(outbuffer + offset + 0) = (this->time_data_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->time_data_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->time_data_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->time_data_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time_data_length);
      for( uint32_t i = 0; i < time_data_length; i++){
      *(outbuffer + offset + 0) = (this->time_data[i].sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->time_data[i].sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->time_data[i].sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->time_data[i].sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time_data[i].sec);
      *(outbuffer + offset + 0) = (this->time_data[i].nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->time_data[i].nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->time_data[i].nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->time_data[i].nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time_data[i].nsec);
      }
      *(outbuffer + offset + 0) = (this->duration_data_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->duration_data_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->duration_data_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->duration_data_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->duration_data_length);
      for( uint32_t i = 0; i < duration_data_length; i++){
      *(outbuffer + offset + 0) = (this->duration_data[i].sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->duration_data[i].sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->duration_data[i].sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->duration_data[i].sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->duration_data[i].sec);
      *(outbuffer + offset + 0) = (this->duration_data[i].nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->duration_data[i].nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->duration_data[i].nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->duration_data[i].nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->duration_data[i].nsec);
      }
      *(outbuffer + offset + 0) = (this->string_data_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->string_data_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->string_data_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->string_data_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->string_data_length);
      for( uint32_t i = 0; i < string_data_length; i++){
      offset += this->string_data[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t float32_data_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      float32_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      float32_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      float32_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->float32_data_length);
      if(float32_data_lengthT > float32_data_length)
        this->float32_data = (float*)realloc(this->float32_data, float32_data_lengthT * sizeof(float));
      float32_data_length = float32_data_lengthT;
      for( uint32_t i = 0; i < float32_data_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_float32_data;
      u_st_float32_data.base = 0;
      u_st_float32_data.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_float32_data.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_float32_data.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_float32_data.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_float32_data = u_st_float32_data.real;
      offset += sizeof(this->st_float32_data);
        memcpy( &(this->float32_data[i]), &(this->st_float32_data), sizeof(float));
      }
      uint32_t float64_data_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      float64_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      float64_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      float64_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->float64_data_length);
      if(float64_data_lengthT > float64_data_length)
        this->float64_data = (float*)realloc(this->float64_data, float64_data_lengthT * sizeof(float));
      float64_data_length = float64_data_lengthT;
      for( uint32_t i = 0; i < float64_data_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_float64_data));
        memcpy( &(this->float64_data[i]), &(this->st_float64_data), sizeof(float));
      }
      uint32_t int16_data_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      int16_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      int16_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      int16_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->int16_data_length);
      if(int16_data_lengthT > int16_data_length)
        this->int16_data = (int16_t*)realloc(this->int16_data, int16_data_lengthT * sizeof(int16_t));
      int16_data_length = int16_data_lengthT;
      for( uint32_t i = 0; i < int16_data_length; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_st_int16_data;
      u_st_int16_data.base = 0;
      u_st_int16_data.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_int16_data.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->st_int16_data = u_st_int16_data.real;
      offset += sizeof(this->st_int16_data);
        memcpy( &(this->int16_data[i]), &(this->st_int16_data), sizeof(int16_t));
      }
      uint32_t int32_data_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      int32_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      int32_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      int32_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->int32_data_length);
      if(int32_data_lengthT > int32_data_length)
        this->int32_data = (int32_t*)realloc(this->int32_data, int32_data_lengthT * sizeof(int32_t));
      int32_data_length = int32_data_lengthT;
      for( uint32_t i = 0; i < int32_data_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_int32_data;
      u_st_int32_data.base = 0;
      u_st_int32_data.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_int32_data.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_int32_data.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_int32_data.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_int32_data = u_st_int32_data.real;
      offset += sizeof(this->st_int32_data);
        memcpy( &(this->int32_data[i]), &(this->st_int32_data), sizeof(int32_t));
      }
      uint32_t int64_data_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      int64_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      int64_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      int64_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->int64_data_length);
      if(int64_data_lengthT > int64_data_length)
        this->int64_data = (int64_t*)realloc(this->int64_data, int64_data_lengthT * sizeof(int64_t));
      int64_data_length = int64_data_lengthT;
      for( uint32_t i = 0; i < int64_data_length; i++){
      union {
        int64_t real;
        uint64_t base;
      } u_st_int64_data;
      u_st_int64_data.base = 0;
      u_st_int64_data.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_int64_data.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_int64_data.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_int64_data.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_st_int64_data.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_st_int64_data.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_st_int64_data.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_st_int64_data.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->st_int64_data = u_st_int64_data.real;
      offset += sizeof(this->st_int64_data);
        memcpy( &(this->int64_data[i]), &(this->st_int64_data), sizeof(int64_t));
      }
      uint32_t int8_data_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      int8_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      int8_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      int8_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->int8_data_length);
      if(int8_data_lengthT > int8_data_length)
        this->int8_data = (int8_t*)realloc(this->int8_data, int8_data_lengthT * sizeof(int8_t));
      int8_data_length = int8_data_lengthT;
      for( uint32_t i = 0; i < int8_data_length; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_st_int8_data;
      u_st_int8_data.base = 0;
      u_st_int8_data.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->st_int8_data = u_st_int8_data.real;
      offset += sizeof(this->st_int8_data);
        memcpy( &(this->int8_data[i]), &(this->st_int8_data), sizeof(int8_t));
      }
      uint32_t uint16_data_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      uint16_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      uint16_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      uint16_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->uint16_data_length);
      if(uint16_data_lengthT > uint16_data_length)
        this->uint16_data = (uint16_t*)realloc(this->uint16_data, uint16_data_lengthT * sizeof(uint16_t));
      uint16_data_length = uint16_data_lengthT;
      for( uint32_t i = 0; i < uint16_data_length; i++){
      this->st_uint16_data =  ((uint16_t) (*(inbuffer + offset)));
      this->st_uint16_data |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->st_uint16_data);
        memcpy( &(this->uint16_data[i]), &(this->st_uint16_data), sizeof(uint16_t));
      }
      uint32_t uint32_data_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      uint32_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      uint32_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      uint32_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->uint32_data_length);
      if(uint32_data_lengthT > uint32_data_length)
        this->uint32_data = (uint32_t*)realloc(this->uint32_data, uint32_data_lengthT * sizeof(uint32_t));
      uint32_data_length = uint32_data_lengthT;
      for( uint32_t i = 0; i < uint32_data_length; i++){
      this->st_uint32_data =  ((uint32_t) (*(inbuffer + offset)));
      this->st_uint32_data |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->st_uint32_data |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->st_uint32_data |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->st_uint32_data);
        memcpy( &(this->uint32_data[i]), &(this->st_uint32_data), sizeof(uint32_t));
      }
      uint32_t uint64_data_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      uint64_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      uint64_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      uint64_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->uint64_data_length);
      if(uint64_data_lengthT > uint64_data_length)
        this->uint64_data = (uint64_t*)realloc(this->uint64_data, uint64_data_lengthT * sizeof(uint64_t));
      uint64_data_length = uint64_data_lengthT;
      for( uint32_t i = 0; i < uint64_data_length; i++){
      this->st_uint64_data =  ((uint64_t) (*(inbuffer + offset)));
      this->st_uint64_data |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->st_uint64_data |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->st_uint64_data |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_uint64_data |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      this->st_uint64_data |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      this->st_uint64_data |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      this->st_uint64_data |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      offset += sizeof(this->st_uint64_data);
        memcpy( &(this->uint64_data[i]), &(this->st_uint64_data), sizeof(uint64_t));
      }
      uint32_t uint8_data_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      uint8_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      uint8_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      uint8_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->uint8_data_length);
      if(uint8_data_lengthT > uint8_data_length)
        this->uint8_data = (uint8_t*)realloc(this->uint8_data, uint8_data_lengthT * sizeof(uint8_t));
      uint8_data_length = uint8_data_lengthT;
      for( uint32_t i = 0; i < uint8_data_length; i++){
      this->st_uint8_data =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->st_uint8_data);
        memcpy( &(this->uint8_data[i]), &(this->st_uint8_data), sizeof(uint8_t));
      }
      uint32_t bool_data_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      bool_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      bool_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      bool_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->bool_data_length);
      if(bool_data_lengthT > bool_data_length)
        this->bool_data = (bool*)realloc(this->bool_data, bool_data_lengthT * sizeof(bool));
      bool_data_length = bool_data_lengthT;
      for( uint32_t i = 0; i < bool_data_length; i++){
      union {
        bool real;
        uint8_t base;
      } u_st_bool_data;
      u_st_bool_data.base = 0;
      u_st_bool_data.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->st_bool_data = u_st_bool_data.real;
      offset += sizeof(this->st_bool_data);
        memcpy( &(this->bool_data[i]), &(this->st_bool_data), sizeof(bool));
      }
      uint32_t time_data_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      time_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      time_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      time_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->time_data_length);
      if(time_data_lengthT > time_data_length)
        this->time_data = (ros::Time*)realloc(this->time_data, time_data_lengthT * sizeof(ros::Time));
      time_data_length = time_data_lengthT;
      for( uint32_t i = 0; i < time_data_length; i++){
      this->st_time_data.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->st_time_data.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->st_time_data.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->st_time_data.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->st_time_data.sec);
      this->st_time_data.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->st_time_data.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->st_time_data.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->st_time_data.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->st_time_data.nsec);
        memcpy( &(this->time_data[i]), &(this->st_time_data), sizeof(ros::Time));
      }
      uint32_t duration_data_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      duration_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      duration_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      duration_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->duration_data_length);
      if(duration_data_lengthT > duration_data_length)
        this->duration_data = (ros::Duration*)realloc(this->duration_data, duration_data_lengthT * sizeof(ros::Duration));
      duration_data_length = duration_data_lengthT;
      for( uint32_t i = 0; i < duration_data_length; i++){
      this->st_duration_data.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->st_duration_data.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->st_duration_data.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->st_duration_data.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->st_duration_data.sec);
      this->st_duration_data.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->st_duration_data.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->st_duration_data.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->st_duration_data.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->st_duration_data.nsec);
        memcpy( &(this->duration_data[i]), &(this->st_duration_data), sizeof(ros::Duration));
      }
      uint32_t string_data_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      string_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      string_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      string_data_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->string_data_length);
      if(string_data_lengthT > string_data_length)
        this->string_data = (std_msgs::String*)realloc(this->string_data, string_data_lengthT * sizeof(std_msgs::String));
      string_data_length = string_data_lengthT;
      for( uint32_t i = 0; i < string_data_length; i++){
      offset += this->st_string_data.deserialize(inbuffer + offset);
        memcpy( &(this->string_data[i]), &(this->st_string_data), sizeof(std_msgs::String));
      }
     return offset;
    }

    const char * getType(){ return "roseus/VariableArray"; };
    const char * getMD5(){ return "aebf8af723dcbdb6782481457d175157"; };

  };

}
#endif