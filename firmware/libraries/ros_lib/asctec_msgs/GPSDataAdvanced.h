#ifndef _ROS_asctec_msgs_GPSDataAdvanced_h
#define _ROS_asctec_msgs_GPSDataAdvanced_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace asctec_msgs
{

  class GPSDataAdvanced : public ros::Msg
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
      typedef int32_t _horizontal_accuracy_type;
      _horizontal_accuracy_type horizontal_accuracy;
      typedef int32_t _vertical_accuracy_type;
      _vertical_accuracy_type vertical_accuracy;
      typedef int32_t _speed_accuracy_type;
      _speed_accuracy_type speed_accuracy;
      typedef int32_t _numSV_type;
      _numSV_type numSV;
      typedef int32_t _status_type;
      _status_type status;
      typedef int32_t _latitude_best_estimate_type;
      _latitude_best_estimate_type latitude_best_estimate;
      typedef int32_t _longitude_best_estimate_type;
      _longitude_best_estimate_type longitude_best_estimate;
      typedef int32_t _speed_x_best_estimate_type;
      _speed_x_best_estimate_type speed_x_best_estimate;
      typedef int32_t _speed_y_best_estimate_type;
      _speed_y_best_estimate_type speed_y_best_estimate;

    GPSDataAdvanced():
      header(),
      latitude(0),
      longitude(0),
      height(0),
      speed_x(0),
      speed_y(0),
      heading(0),
      horizontal_accuracy(0),
      vertical_accuracy(0),
      speed_accuracy(0),
      numSV(0),
      status(0),
      latitude_best_estimate(0),
      longitude_best_estimate(0),
      speed_x_best_estimate(0),
      speed_y_best_estimate(0)
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
      } u_horizontal_accuracy;
      u_horizontal_accuracy.real = this->horizontal_accuracy;
      *(outbuffer + offset + 0) = (u_horizontal_accuracy.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_horizontal_accuracy.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_horizontal_accuracy.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_horizontal_accuracy.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->horizontal_accuracy);
      union {
        int32_t real;
        uint32_t base;
      } u_vertical_accuracy;
      u_vertical_accuracy.real = this->vertical_accuracy;
      *(outbuffer + offset + 0) = (u_vertical_accuracy.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_vertical_accuracy.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_vertical_accuracy.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_vertical_accuracy.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->vertical_accuracy);
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
      } u_numSV;
      u_numSV.real = this->numSV;
      *(outbuffer + offset + 0) = (u_numSV.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_numSV.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_numSV.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_numSV.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->numSV);
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
      } u_latitude_best_estimate;
      u_latitude_best_estimate.real = this->latitude_best_estimate;
      *(outbuffer + offset + 0) = (u_latitude_best_estimate.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_latitude_best_estimate.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_latitude_best_estimate.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_latitude_best_estimate.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->latitude_best_estimate);
      union {
        int32_t real;
        uint32_t base;
      } u_longitude_best_estimate;
      u_longitude_best_estimate.real = this->longitude_best_estimate;
      *(outbuffer + offset + 0) = (u_longitude_best_estimate.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_longitude_best_estimate.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_longitude_best_estimate.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_longitude_best_estimate.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->longitude_best_estimate);
      union {
        int32_t real;
        uint32_t base;
      } u_speed_x_best_estimate;
      u_speed_x_best_estimate.real = this->speed_x_best_estimate;
      *(outbuffer + offset + 0) = (u_speed_x_best_estimate.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_speed_x_best_estimate.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_speed_x_best_estimate.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_speed_x_best_estimate.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->speed_x_best_estimate);
      union {
        int32_t real;
        uint32_t base;
      } u_speed_y_best_estimate;
      u_speed_y_best_estimate.real = this->speed_y_best_estimate;
      *(outbuffer + offset + 0) = (u_speed_y_best_estimate.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_speed_y_best_estimate.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_speed_y_best_estimate.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_speed_y_best_estimate.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->speed_y_best_estimate);
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
      } u_horizontal_accuracy;
      u_horizontal_accuracy.base = 0;
      u_horizontal_accuracy.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_horizontal_accuracy.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_horizontal_accuracy.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_horizontal_accuracy.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->horizontal_accuracy = u_horizontal_accuracy.real;
      offset += sizeof(this->horizontal_accuracy);
      union {
        int32_t real;
        uint32_t base;
      } u_vertical_accuracy;
      u_vertical_accuracy.base = 0;
      u_vertical_accuracy.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_vertical_accuracy.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_vertical_accuracy.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_vertical_accuracy.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->vertical_accuracy = u_vertical_accuracy.real;
      offset += sizeof(this->vertical_accuracy);
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
      } u_numSV;
      u_numSV.base = 0;
      u_numSV.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_numSV.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_numSV.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_numSV.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->numSV = u_numSV.real;
      offset += sizeof(this->numSV);
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
      } u_latitude_best_estimate;
      u_latitude_best_estimate.base = 0;
      u_latitude_best_estimate.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_latitude_best_estimate.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_latitude_best_estimate.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_latitude_best_estimate.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->latitude_best_estimate = u_latitude_best_estimate.real;
      offset += sizeof(this->latitude_best_estimate);
      union {
        int32_t real;
        uint32_t base;
      } u_longitude_best_estimate;
      u_longitude_best_estimate.base = 0;
      u_longitude_best_estimate.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_longitude_best_estimate.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_longitude_best_estimate.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_longitude_best_estimate.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->longitude_best_estimate = u_longitude_best_estimate.real;
      offset += sizeof(this->longitude_best_estimate);
      union {
        int32_t real;
        uint32_t base;
      } u_speed_x_best_estimate;
      u_speed_x_best_estimate.base = 0;
      u_speed_x_best_estimate.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_speed_x_best_estimate.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_speed_x_best_estimate.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_speed_x_best_estimate.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->speed_x_best_estimate = u_speed_x_best_estimate.real;
      offset += sizeof(this->speed_x_best_estimate);
      union {
        int32_t real;
        uint32_t base;
      } u_speed_y_best_estimate;
      u_speed_y_best_estimate.base = 0;
      u_speed_y_best_estimate.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_speed_y_best_estimate.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_speed_y_best_estimate.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_speed_y_best_estimate.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->speed_y_best_estimate = u_speed_y_best_estimate.real;
      offset += sizeof(this->speed_y_best_estimate);
     return offset;
    }

    const char * getType(){ return "asctec_msgs/GPSDataAdvanced"; };
    const char * getMD5(){ return "9ab56d8a7fca6e53fe5619fec119323d"; };

  };

}
#endif