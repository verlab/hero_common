#ifndef _ROS_create_node_BatteryState_h
#define _ROS_create_node_BatteryState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace create_node
{

  class BatteryState : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef int8_t _temperature_type;
      _temperature_type temperature;
      typedef uint16_t _charge_type;
      _charge_type charge;
      typedef uint16_t _capacity_type;
      _capacity_type capacity;

    BatteryState():
      header(),
      temperature(0),
      charge(0),
      capacity(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        int8_t real;
        uint8_t base;
      } u_temperature;
      u_temperature.real = this->temperature;
      *(outbuffer + offset + 0) = (u_temperature.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->temperature);
      *(outbuffer + offset + 0) = (this->charge >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->charge >> (8 * 1)) & 0xFF;
      offset += sizeof(this->charge);
      *(outbuffer + offset + 0) = (this->capacity >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->capacity >> (8 * 1)) & 0xFF;
      offset += sizeof(this->capacity);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        int8_t real;
        uint8_t base;
      } u_temperature;
      u_temperature.base = 0;
      u_temperature.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->temperature = u_temperature.real;
      offset += sizeof(this->temperature);
      this->charge =  ((uint16_t) (*(inbuffer + offset)));
      this->charge |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->charge);
      this->capacity =  ((uint16_t) (*(inbuffer + offset)));
      this->capacity |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->capacity);
     return offset;
    }

    const char * getType(){ return "create_node/BatteryState"; };
    const char * getMD5(){ return "481447a4e24f212e7b403e4f04aa2ac9"; };

  };

}
#endif