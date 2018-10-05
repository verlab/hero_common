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
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t thermal_source_degrees_length;
      typedef float _thermal_source_degrees_type;
      _thermal_source_degrees_type st_thermal_source_degrees;
      _thermal_source_degrees_type * thermal_source_degrees;

    ThermalSensorMeasurementMsg():
      header(),
      thermal_source_degrees_length(0), thermal_source_degrees(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->thermal_source_degrees_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->thermal_source_degrees_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->thermal_source_degrees_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->thermal_source_degrees_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->thermal_source_degrees_length);
      for( uint32_t i = 0; i < thermal_source_degrees_length; i++){
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
      uint32_t thermal_source_degrees_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      thermal_source_degrees_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      thermal_source_degrees_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      thermal_source_degrees_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->thermal_source_degrees_length);
      if(thermal_source_degrees_lengthT > thermal_source_degrees_length)
        this->thermal_source_degrees = (float*)realloc(this->thermal_source_degrees, thermal_source_degrees_lengthT * sizeof(float));
      thermal_source_degrees_length = thermal_source_degrees_lengthT;
      for( uint32_t i = 0; i < thermal_source_degrees_length; i++){
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