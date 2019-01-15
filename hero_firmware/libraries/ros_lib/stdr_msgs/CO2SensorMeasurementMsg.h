#ifndef _ROS_stdr_msgs_CO2SensorMeasurementMsg_h
#define _ROS_stdr_msgs_CO2SensorMeasurementMsg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace stdr_msgs
{

  class CO2SensorMeasurementMsg : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef float _co2_ppm_type;
      _co2_ppm_type co2_ppm;

    CO2SensorMeasurementMsg():
      header(),
      co2_ppm(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_co2_ppm;
      u_co2_ppm.real = this->co2_ppm;
      *(outbuffer + offset + 0) = (u_co2_ppm.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_co2_ppm.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_co2_ppm.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_co2_ppm.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->co2_ppm);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_co2_ppm;
      u_co2_ppm.base = 0;
      u_co2_ppm.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_co2_ppm.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_co2_ppm.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_co2_ppm.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->co2_ppm = u_co2_ppm.real;
      offset += sizeof(this->co2_ppm);
     return offset;
    }

    const char * getType(){ return "stdr_msgs/CO2SensorMeasurementMsg"; };
    const char * getMD5(){ return "ea3141a4e89d798f2735cb324ffcd870"; };

  };

}
#endif