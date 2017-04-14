#ifndef _ROS_verlab_image_gps_gps_msgs_h
#define _ROS_verlab_image_gps_gps_msgs_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace verlab_image_gps
{

  class gps_msgs : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef int32_t _latitude_type;
      _latitude_type latitude;
      typedef int32_t _longitude_type;
      _longitude_type longitude;
      typedef int32_t _height_type;
      _height_type height;
      typedef int32_t _speed_x_type;
      _speed_x_type speed_x;
      typedef int32_t _speed_y_type;
      _speed_y_type speed_y;
      typedef int32_t _heading_type;
      _heading_type heading;
      typedef int32_t _position_accuracy_type;
      _position_accuracy_type position_accuracy;
      typedef int32_t _height_accuracy_type;
      _height_accuracy_type height_accuracy;
      typedef int32_t _speed_accuracy_type;
      _speed_accuracy_type speed_accuracy;
      typedef int32_t _sat_num_type;
      _sat_num_type sat_num;
      typedef int32_t _status_type;
      _status_type status;
      typedef int32_t _time_of_week_type;
      _time_of_week_type time_of_week;
      typedef int32_t _week_type;
      _week_type week;

    gps_msgs():
      header(),
      latitude(0),
      longitude(0),
      height(0),
      speed_x(0),
      speed_y(0),
      heading(0),
      position_accuracy(0),
      height_accuracy(0),
      speed_accuracy(0),
      sat_num(0),
      status(0),
      time_of_week(0),
      week(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_latitude;
      u_latitude.real = this->latitude;
      *(outbuffer + offset + 0) = (u_latitude.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_latitude.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_latitude.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_latitude.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->latitude);
      union {
        int32_t real;
        uint32_t base;
      } u_longitude;
      u_longitude.real = this->longitude;
      *(outbuffer + offset + 0) = (u_longitude.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_longitude.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_longitude.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_longitude.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->longitude);
      union {
        int32_t real;
        uint32_t base;
      } u_height;
      u_height.real = this->height;
      *(outbuffer + offset + 0) = (u_height.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_height.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_height.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_height.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->height);
      union {
        int32_t real;
        uint32_t base;
      } u_speed_x;
      u_speed_x.real = this->speed_x;
      *(outbuffer + offset + 0) = (u_speed_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_speed_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_speed_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_speed_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->speed_x);
      union {
        int32_t real;
        uint32_t base;
      } u_speed_y;
      u_speed_y.real = this->speed_y;
      *(outbuffer + offset + 0) = (u_speed_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_speed_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_speed_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_speed_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->speed_y);
      union {
        int32_t real;
        uint32_t base;
      } u_heading;
      u_heading.real = this->heading;
      *(outbuffer + offset + 0) = (u_heading.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_heading.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_heading.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_heading.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->heading);
      union {
        int32_t real;
        uint32_t base;
      } u_position_accuracy;
      u_position_accuracy.real = this->position_accuracy;
      *(outbuffer + offset + 0) = (u_position_accuracy.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_position_accuracy.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_position_accuracy.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_position_accuracy.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->position_accuracy);
      union {
        int32_t real;
        uint32_t base;
      } u_height_accuracy;
      u_height_accuracy.real = this->height_accuracy;
      *(outbuffer + offset + 0) = (u_height_accuracy.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_height_accuracy.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_height_accuracy.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_height_accuracy.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->height_accuracy);
      union {
        int32_t real;
        uint32_t base;
      } u_speed_accuracy;
      u_speed_accuracy.real = this->speed_accuracy;
      *(outbuffer + offset + 0) = (u_speed_accuracy.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_speed_accuracy.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_speed_accuracy.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_speed_accuracy.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->speed_accuracy);
      union {
        int32_t real;
        uint32_t base;
      } u_sat_num;
      u_sat_num.real = this->sat_num;
      *(outbuffer + offset + 0) = (u_sat_num.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_sat_num.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_sat_num.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_sat_num.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->sat_num);
      union {
        int32_t real;
        uint32_t base;
      } u_status;
      u_status.real = this->status;
      *(outbuffer + offset + 0) = (u_status.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_status.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_status.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_status.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->status);
      union {
        int32_t real;
        uint32_t base;
      } u_time_of_week;
      u_time_of_week.real = this->time_of_week;
      *(outbuffer + offset + 0) = (u_time_of_week.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_time_of_week.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_time_of_week.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_time_of_week.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time_of_week);
      union {
        int32_t real;
        uint32_t base;
      } u_week;
      u_week.real = this->week;
      *(outbuffer + offset + 0) = (u_week.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_week.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_week.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_week.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->week);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_latitude;
      u_latitude.base = 0;
      u_latitude.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_latitude.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_latitude.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_latitude.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->latitude = u_latitude.real;
      offset += sizeof(this->latitude);
      union {
        int32_t real;
        uint32_t base;
      } u_longitude;
      u_longitude.base = 0;
      u_longitude.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_longitude.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_longitude.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_longitude.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->longitude = u_longitude.real;
      offset += sizeof(this->longitude);
      union {
        int32_t real;
        uint32_t base;
      } u_height;
      u_height.base = 0;
      u_height.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_height.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_height.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_height.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->height = u_height.real;
      offset += sizeof(this->height);
      union {
        int32_t real;
        uint32_t base;
      } u_speed_x;
      u_speed_x.base = 0;
      u_speed_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_speed_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_speed_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_speed_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->speed_x = u_speed_x.real;
      offset += sizeof(this->speed_x);
      union {
        int32_t real;
        uint32_t base;
      } u_speed_y;
      u_speed_y.base = 0;
      u_speed_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_speed_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_speed_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_speed_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->speed_y = u_speed_y.real;
      offset += sizeof(this->speed_y);
      union {
        int32_t real;
        uint32_t base;
      } u_heading;
      u_heading.base = 0;
      u_heading.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_heading.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_heading.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_heading.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->heading = u_heading.real;
      offset += sizeof(this->heading);
      union {
        int32_t real;
        uint32_t base;
      } u_position_accuracy;
      u_position_accuracy.base = 0;
      u_position_accuracy.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_position_accuracy.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_position_accuracy.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_position_accuracy.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->position_accuracy = u_position_accuracy.real;
      offset += sizeof(this->position_accuracy);
      union {
        int32_t real;
        uint32_t base;
      } u_height_accuracy;
      u_height_accuracy.base = 0;
      u_height_accuracy.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_height_accuracy.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_height_accuracy.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_height_accuracy.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->height_accuracy = u_height_accuracy.real;
      offset += sizeof(this->height_accuracy);
      union {
        int32_t real;
        uint32_t base;
      } u_speed_accuracy;
      u_speed_accuracy.base = 0;
      u_speed_accuracy.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_speed_accuracy.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_speed_accuracy.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_speed_accuracy.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->speed_accuracy = u_speed_accuracy.real;
      offset += sizeof(this->speed_accuracy);
      union {
        int32_t real;
        uint32_t base;
      } u_sat_num;
      u_sat_num.base = 0;
      u_sat_num.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_sat_num.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_sat_num.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_sat_num.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->sat_num = u_sat_num.real;
      offset += sizeof(this->sat_num);
      union {
        int32_t real;
        uint32_t base;
      } u_status;
      u_status.base = 0;
      u_status.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_status.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_status.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_status.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->status = u_status.real;
      offset += sizeof(this->status);
      union {
        int32_t real;
        uint32_t base;
      } u_time_of_week;
      u_time_of_week.base = 0;
      u_time_of_week.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_time_of_week.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_time_of_week.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_time_of_week.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->time_of_week = u_time_of_week.real;
      offset += sizeof(this->time_of_week);
      union {
        int32_t real;
        uint32_t base;
      } u_week;
      u_week.base = 0;
      u_week.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_week.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_week.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_week.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->week = u_week.real;
      offset += sizeof(this->week);
     return offset;
    }

    const char * getType(){ return "verlab_image_gps/gps_msgs"; };
    const char * getMD5(){ return "ec6025802e0ada9342cc070b44ff24c8"; };

  };

}
#endif