#ifndef _ROS_mavros_msgs_OpticalFlowRad_h
#define _ROS_mavros_msgs_OpticalFlowRad_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace mavros_msgs
{

  class OpticalFlowRad : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint32_t integration_time_us;
      float integrated_x;
      float integrated_y;
      float integrated_xgyro;
      float integrated_ygyro;
      float integrated_zgyro;
      int16_t temperature;
      uint8_t quality;
      uint32_t time_delta_distance_us;
      float distance;

    OpticalFlowRad():
      header(),
      integration_time_us(0),
      integrated_x(0),
      integrated_y(0),
      integrated_xgyro(0),
      integrated_ygyro(0),
      integrated_zgyro(0),
      temperature(0),
      quality(0),
      time_delta_distance_us(0),
      distance(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->integration_time_us >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->integration_time_us >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->integration_time_us >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->integration_time_us >> (8 * 3)) & 0xFF;
      offset += sizeof(this->integration_time_us);
      union {
        float real;
        uint32_t base;
      } u_integrated_x;
      u_integrated_x.real = this->integrated_x;
      *(outbuffer + offset + 0) = (u_integrated_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_integrated_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_integrated_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_integrated_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->integrated_x);
      union {
        float real;
        uint32_t base;
      } u_integrated_y;
      u_integrated_y.real = this->integrated_y;
      *(outbuffer + offset + 0) = (u_integrated_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_integrated_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_integrated_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_integrated_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->integrated_y);
      union {
        float real;
        uint32_t base;
      } u_integrated_xgyro;
      u_integrated_xgyro.real = this->integrated_xgyro;
      *(outbuffer + offset + 0) = (u_integrated_xgyro.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_integrated_xgyro.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_integrated_xgyro.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_integrated_xgyro.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->integrated_xgyro);
      union {
        float real;
        uint32_t base;
      } u_integrated_ygyro;
      u_integrated_ygyro.real = this->integrated_ygyro;
      *(outbuffer + offset + 0) = (u_integrated_ygyro.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_integrated_ygyro.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_integrated_ygyro.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_integrated_ygyro.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->integrated_ygyro);
      union {
        float real;
        uint32_t base;
      } u_integrated_zgyro;
      u_integrated_zgyro.real = this->integrated_zgyro;
      *(outbuffer + offset + 0) = (u_integrated_zgyro.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_integrated_zgyro.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_integrated_zgyro.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_integrated_zgyro.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->integrated_zgyro);
      union {
        int16_t real;
        uint16_t base;
      } u_temperature;
      u_temperature.real = this->temperature;
      *(outbuffer + offset + 0) = (u_temperature.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_temperature.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->temperature);
      *(outbuffer + offset + 0) = (this->quality >> (8 * 0)) & 0xFF;
      offset += sizeof(this->quality);
      *(outbuffer + offset + 0) = (this->time_delta_distance_us >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->time_delta_distance_us >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->time_delta_distance_us >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->time_delta_distance_us >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time_delta_distance_us);
      union {
        float real;
        uint32_t base;
      } u_distance;
      u_distance.real = this->distance;
      *(outbuffer + offset + 0) = (u_distance.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_distance.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_distance.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_distance.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->distance);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->integration_time_us =  ((uint32_t) (*(inbuffer + offset)));
      this->integration_time_us |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->integration_time_us |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->integration_time_us |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->integration_time_us);
      union {
        float real;
        uint32_t base;
      } u_integrated_x;
      u_integrated_x.base = 0;
      u_integrated_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_integrated_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_integrated_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_integrated_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->integrated_x = u_integrated_x.real;
      offset += sizeof(this->integrated_x);
      union {
        float real;
        uint32_t base;
      } u_integrated_y;
      u_integrated_y.base = 0;
      u_integrated_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_integrated_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_integrated_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_integrated_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->integrated_y = u_integrated_y.real;
      offset += sizeof(this->integrated_y);
      union {
        float real;
        uint32_t base;
      } u_integrated_xgyro;
      u_integrated_xgyro.base = 0;
      u_integrated_xgyro.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_integrated_xgyro.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_integrated_xgyro.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_integrated_xgyro.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->integrated_xgyro = u_integrated_xgyro.real;
      offset += sizeof(this->integrated_xgyro);
      union {
        float real;
        uint32_t base;
      } u_integrated_ygyro;
      u_integrated_ygyro.base = 0;
      u_integrated_ygyro.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_integrated_ygyro.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_integrated_ygyro.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_integrated_ygyro.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->integrated_ygyro = u_integrated_ygyro.real;
      offset += sizeof(this->integrated_ygyro);
      union {
        float real;
        uint32_t base;
      } u_integrated_zgyro;
      u_integrated_zgyro.base = 0;
      u_integrated_zgyro.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_integrated_zgyro.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_integrated_zgyro.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_integrated_zgyro.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->integrated_zgyro = u_integrated_zgyro.real;
      offset += sizeof(this->integrated_zgyro);
      union {
        int16_t real;
        uint16_t base;
      } u_temperature;
      u_temperature.base = 0;
      u_temperature.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_temperature.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->temperature = u_temperature.real;
      offset += sizeof(this->temperature);
      this->quality =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->quality);
      this->time_delta_distance_us =  ((uint32_t) (*(inbuffer + offset)));
      this->time_delta_distance_us |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->time_delta_distance_us |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->time_delta_distance_us |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->time_delta_distance_us);
      union {
        float real;
        uint32_t base;
      } u_distance;
      u_distance.base = 0;
      u_distance.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_distance.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_distance.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_distance.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->distance = u_distance.real;
      offset += sizeof(this->distance);
     return offset;
    }

    const char * getType(){ return "mavros_msgs/OpticalFlowRad"; };
    const char * getMD5(){ return "65d93e03c6188c7ee30415b2a39ad40d"; };

  };

}
#endif