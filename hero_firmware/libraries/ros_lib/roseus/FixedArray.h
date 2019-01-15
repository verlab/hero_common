#ifndef _ROS_roseus_FixedArray_h
#define _ROS_roseus_FixedArray_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ros/time.h"
#include "ros/duration.h"
#include "std_msgs/String.h"

namespace roseus
{

  class FixedArray : public ros::Msg
  {
    public:
      float float32_data[3];
      float float64_data[3];
      int16_t int16_data[3];
      int32_t int32_data[3];
      int64_t int64_data[3];
      int8_t int8_data[3];
      uint16_t uint16_data[3];
      uint32_t uint32_data[3];
      uint64_t uint64_data[3];
      uint8_t uint8_data[17];
      bool bool_data[2];
      ros::Time time_data[2];
      ros::Duration duration_data[2];
      std_msgs::String string_data[2];

    FixedArray():
      float32_data(),
      float64_data(),
      int16_data(),
      int32_data(),
      int64_data(),
      int8_data(),
      uint16_data(),
      uint32_data(),
      uint64_data(),
      uint8_data(),
      bool_data(),
      time_data(),
      duration_data(),
      string_data()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 3; i++){
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
      for( uint32_t i = 0; i < 3; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->float64_data[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_int16_datai;
      u_int16_datai.real = this->int16_data[i];
      *(outbuffer + offset + 0) = (u_int16_datai.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_int16_datai.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->int16_data[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
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
      for( uint32_t i = 0; i < 3; i++){
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
      for( uint32_t i = 0; i < 3; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_int8_datai;
      u_int8_datai.real = this->int8_data[i];
      *(outbuffer + offset + 0) = (u_int8_datai.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->int8_data[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      *(outbuffer + offset + 0) = (this->uint16_data[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->uint16_data[i] >> (8 * 1)) & 0xFF;
      offset += sizeof(this->uint16_data[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      *(outbuffer + offset + 0) = (this->uint32_data[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->uint32_data[i] >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->uint32_data[i] >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->uint32_data[i] >> (8 * 3)) & 0xFF;
      offset += sizeof(this->uint32_data[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
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
      for( uint32_t i = 0; i < 17; i++){
      *(outbuffer + offset + 0) = (this->uint8_data[i] >> (8 * 0)) & 0xFF;
      offset += sizeof(this->uint8_data[i]);
      }
      for( uint32_t i = 0; i < 2; i++){
      union {
        bool real;
        uint8_t base;
      } u_bool_datai;
      u_bool_datai.real = this->bool_data[i];
      *(outbuffer + offset + 0) = (u_bool_datai.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->bool_data[i]);
      }
      for( uint32_t i = 0; i < 2; i++){
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
      for( uint32_t i = 0; i < 2; i++){
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
      for( uint32_t i = 0; i < 2; i++){
      offset += this->string_data[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 3; i++){
      union {
        float real;
        uint32_t base;
      } u_float32_datai;
      u_float32_datai.base = 0;
      u_float32_datai.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_float32_datai.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_float32_datai.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_float32_datai.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->float32_data[i] = u_float32_datai.real;
      offset += sizeof(this->float32_data[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->float64_data[i]));
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_int16_datai;
      u_int16_datai.base = 0;
      u_int16_datai.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_int16_datai.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->int16_data[i] = u_int16_datai.real;
      offset += sizeof(this->int16_data[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_int32_datai;
      u_int32_datai.base = 0;
      u_int32_datai.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_int32_datai.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_int32_datai.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_int32_datai.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->int32_data[i] = u_int32_datai.real;
      offset += sizeof(this->int32_data[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        int64_t real;
        uint64_t base;
      } u_int64_datai;
      u_int64_datai.base = 0;
      u_int64_datai.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_int64_datai.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_int64_datai.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_int64_datai.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_int64_datai.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_int64_datai.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_int64_datai.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_int64_datai.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->int64_data[i] = u_int64_datai.real;
      offset += sizeof(this->int64_data[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_int8_datai;
      u_int8_datai.base = 0;
      u_int8_datai.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->int8_data[i] = u_int8_datai.real;
      offset += sizeof(this->int8_data[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      this->uint16_data[i] =  ((uint16_t) (*(inbuffer + offset)));
      this->uint16_data[i] |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->uint16_data[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      this->uint32_data[i] =  ((uint32_t) (*(inbuffer + offset)));
      this->uint32_data[i] |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->uint32_data[i] |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->uint32_data[i] |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->uint32_data[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      this->uint64_data[i] =  ((uint64_t) (*(inbuffer + offset)));
      this->uint64_data[i] |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->uint64_data[i] |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->uint64_data[i] |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->uint64_data[i] |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      this->uint64_data[i] |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      this->uint64_data[i] |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      this->uint64_data[i] |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      offset += sizeof(this->uint64_data[i]);
      }
      for( uint32_t i = 0; i < 17; i++){
      this->uint8_data[i] =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->uint8_data[i]);
      }
      for( uint32_t i = 0; i < 2; i++){
      union {
        bool real;
        uint8_t base;
      } u_bool_datai;
      u_bool_datai.base = 0;
      u_bool_datai.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->bool_data[i] = u_bool_datai.real;
      offset += sizeof(this->bool_data[i]);
      }
      for( uint32_t i = 0; i < 2; i++){
      this->time_data[i].sec =  ((uint32_t) (*(inbuffer + offset)));
      this->time_data[i].sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->time_data[i].sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->time_data[i].sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->time_data[i].sec);
      this->time_data[i].nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->time_data[i].nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->time_data[i].nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->time_data[i].nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->time_data[i].nsec);
      }
      for( uint32_t i = 0; i < 2; i++){
      this->duration_data[i].sec =  ((uint32_t) (*(inbuffer + offset)));
      this->duration_data[i].sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->duration_data[i].sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->duration_data[i].sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->duration_data[i].sec);
      this->duration_data[i].nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->duration_data[i].nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->duration_data[i].nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->duration_data[i].nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->duration_data[i].nsec);
      }
      for( uint32_t i = 0; i < 2; i++){
      offset += this->string_data[i].deserialize(inbuffer + offset);
      }
     return offset;
    }

    const char * getType(){ return "roseus/FixedArray"; };
    const char * getMD5(){ return "6b30ccf11bc7409743664778a763a8c9"; };

  };

}
#endif