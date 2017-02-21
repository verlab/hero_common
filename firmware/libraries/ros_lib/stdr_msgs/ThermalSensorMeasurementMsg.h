#ifndef _ROS_stdr_msgs_ThermalSensorMeasurementMsg_h
#define _ROS_stdr_msgs_ThermalSensorMeasurementMsg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace stdr_msgs
{

  class ThermalSensorMeasurementMsg : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t thermal_source_degrees_length;
      float st_thermal_source_degrees;
      float * thermal_source_degrees;

    ThermalSensorMeasurementMsg():
      header(),
      thermal_source_degrees_length(0), thermal_source_degrees(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = thermal_source_degrees_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < thermal_source_degrees_length; i++){
      union {
        float real;
        uint32_t base;
      } u_thermal_source_degreesi;
      u_thermal_source_degreesi.real = this->thermal_source_degrees[i];
      *(outbuffer + offset + 0) = (u_thermal_source_degreesi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_thermal_source_degreesi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_thermal_source_degreesi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_thermal_source_degreesi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->thermal_source_degrees[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t thermal_source_degrees_lengthT = *(inbuffer + offset++);
      if(thermal_source_degrees_lengthT > thermal_source_degrees_length)
        this->thermal_source_degrees = (float*)realloc(this->thermal_source_degrees, thermal_source_degrees_lengthT * sizeof(float));
      offset += 3;
      thermal_source_degrees_length = thermal_source_degrees_lengthT;
      for( uint8_t i = 0; i < thermal_source_degrees_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_thermal_source_degrees;
      u_st_thermal_source_degrees.base = 0;
      u_st_thermal_source_degrees.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_thermal_source_degrees.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_thermal_source_degrees.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_thermal_source_degrees.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_thermal_source_degrees = u_st_thermal_source_degrees.real;
      offset += sizeof(this->st_thermal_source_degrees);
        memcpy( &(this->thermal_source_degrees[i]), &(this->st_thermal_source_degrees), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "stdr_msgs/ThermalSensorMeasurementMsg"; };
    const char * getMD5(){ return "e4b704fefcd6eb849f164e31d5084251"; };

  };

}
#endif