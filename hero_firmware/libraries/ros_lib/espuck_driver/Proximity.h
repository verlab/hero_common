#ifndef _ROS_espuck_driver_Proximity_h
#define _ROS_espuck_driver_Proximity_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace espuck_driver
{

  class Proximity : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef float _field_of_view_type;
      _field_of_view_type field_of_view;
      typedef float _max_range_type;
      _max_range_type max_range;
      typedef float _min_range_type;
      _min_range_type min_range;
      uint32_t data_length;
      typedef float _data_type;
      _data_type st_data;
      _data_type * data;

    Proximity():
      header(),
      field_of_view(0),
      max_range(0),
      min_range(0),
      data_length(0), data(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_field_of_view;
      u_field_of_view.real = this->field_of_view;
      *(outbuffer + offset + 0) = (u_field_of_view.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_field_of_view.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_field_of_view.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_field_of_view.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->field_of_view);
      union {
        float real;
        uint32_t base;
      } u_max_range;
      u_max_range.real = this->max_range;
      *(outbuffer + offset + 0) = (u_max_range.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_max_range.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_max_range.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_max_range.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->max_range);
      union {
        float real;
        uint32_t base;
      } u_min_range;
      u_min_range.real = this->min_range;
      *(outbuffer + offset + 0) = (u_min_range.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_min_range.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_min_range.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_min_range.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->min_range);
      *(outbuffer + offset + 0) = (this->data_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->data_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->data_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->data_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->data_length);
      for( uint32_t i = 0; i < data_length; i++){
      union {
        float real;
        uint32_t base;
      } u_datai;
      u_datai.real = this->data[i];
      *(outbuffer + offset + 0) = (u_datai.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_datai.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_datai.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_datai.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->data[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_field_of_view;
      u_field_of_view.base = 0;
      u_field_of_view.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_field_of_view.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_field_of_view.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_field_of_view.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->field_of_view = u_field_of_view.real;
      offset += sizeof(this->field_of_view);
      union {
        float real;
        uint32_t base;
      } u_max_range;
      u_max_range.base = 0;
      u_max_range.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_max_range.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_max_range.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_max_range.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->max_range = u_max_range.real;
      offset += sizeof(this->max_range);
      union {
        float real;
        uint32_t base;
      } u_min_range;
      u_min_range.base = 0;
      u_min_range.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_min_range.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_min_range.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_min_range.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->min_range = u_min_range.real;
      offset += sizeof(this->min_range);
      uint32_t data_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      data_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      data_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      data_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->data_length);
      if(data_lengthT > data_length)
        this->data = (float*)realloc(this->data, data_lengthT * sizeof(float));
      data_length = data_lengthT;
      for( uint32_t i = 0; i < data_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_data;
      u_st_data.base = 0;
      u_st_data.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_data.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_data.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_data.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_data = u_st_data.real;
      offset += sizeof(this->st_data);
        memcpy( &(this->data[i]), &(this->st_data), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "espuck_driver/Proximity"; };
    const char * getMD5(){ return "bc3b3609b17034b50911f704c4d9124f"; };

  };

}
#endif