#ifndef _ROS_asctec_msgs_LLStatus_h
#define _ROS_asctec_msgs_LLStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace asctec_msgs
{

  class LLStatus : public ros::Msg
  {
    public:
      std_msgs::Header header;
      int16_t battery_voltage_1;
      int16_t battery_voltage_2;
      int16_t status;
      int16_t cpu_load;
      int8_t compass_enabled;
      int8_t chksum_error;
      int8_t flying;
      int8_t motors_on;
      int16_t flightMode;
      int16_t up_time;

    LLStatus():
      header(),
      battery_voltage_1(0),
      battery_voltage_2(0),
      status(0),
      cpu_load(0),
      compass_enabled(0),
      chksum_error(0),
      flying(0),
      motors_on(0),
      flightMode(0),
      up_time(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        int16_t real;
        uint16_t base;
      } u_battery_voltage_1;
      u_battery_voltage_1.real = this->battery_voltage_1;
      *(outbuffer + offset + 0) = (u_battery_voltage_1.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_battery_voltage_1.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->battery_voltage_1);
      union {
        int16_t real;
        uint16_t base;
      } u_battery_voltage_2;
      u_battery_voltage_2.real = this->battery_voltage_2;
      *(outbuffer + offset + 0) = (u_battery_voltage_2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_battery_voltage_2.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->battery_voltage_2);
      union {
        int16_t real;
        uint16_t base;
      } u_status;
      u_status.real = this->status;
      *(outbuffer + offset + 0) = (u_status.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_status.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->status);
      union {
        int16_t real;
        uint16_t base;
      } u_cpu_load;
      u_cpu_load.real = this->cpu_load;
      *(outbuffer + offset + 0) = (u_cpu_load.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_cpu_load.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->cpu_load);
      union {
        int8_t real;
        uint8_t base;
      } u_compass_enabled;
      u_compass_enabled.real = this->compass_enabled;
      *(outbuffer + offset + 0) = (u_compass_enabled.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->compass_enabled);
      union {
        int8_t real;
        uint8_t base;
      } u_chksum_error;
      u_chksum_error.real = this->chksum_error;
      *(outbuffer + offset + 0) = (u_chksum_error.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->chksum_error);
      union {
        int8_t real;
        uint8_t base;
      } u_flying;
      u_flying.real = this->flying;
      *(outbuffer + offset + 0) = (u_flying.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->flying);
      union {
        int8_t real;
        uint8_t base;
      } u_motors_on;
      u_motors_on.real = this->motors_on;
      *(outbuffer + offset + 0) = (u_motors_on.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->motors_on);
      union {
        int16_t real;
        uint16_t base;
      } u_flightMode;
      u_flightMode.real = this->flightMode;
      *(outbuffer + offset + 0) = (u_flightMode.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_flightMode.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->flightMode);
      union {
        int16_t real;
        uint16_t base;
      } u_up_time;
      u_up_time.real = this->up_time;
      *(outbuffer + offset + 0) = (u_up_time.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_up_time.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->up_time);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        int16_t real;
        uint16_t base;
      } u_battery_voltage_1;
      u_battery_voltage_1.base = 0;
      u_battery_voltage_1.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_battery_voltage_1.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->battery_voltage_1 = u_battery_voltage_1.real;
      offset += sizeof(this->battery_voltage_1);
      union {
        int16_t real;
        uint16_t base;
      } u_battery_voltage_2;
      u_battery_voltage_2.base = 0;
      u_battery_voltage_2.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_battery_voltage_2.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->battery_voltage_2 = u_battery_voltage_2.real;
      offset += sizeof(this->battery_voltage_2);
      union {
        int16_t real;
        uint16_t base;
      } u_status;
      u_status.base = 0;
      u_status.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_status.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->status = u_status.real;
      offset += sizeof(this->status);
      union {
        int16_t real;
        uint16_t base;
      } u_cpu_load;
      u_cpu_load.base = 0;
      u_cpu_load.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_cpu_load.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->cpu_load = u_cpu_load.real;
      offset += sizeof(this->cpu_load);
      union {
        int8_t real;
        uint8_t base;
      } u_compass_enabled;
      u_compass_enabled.base = 0;
      u_compass_enabled.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->compass_enabled = u_compass_enabled.real;
      offset += sizeof(this->compass_enabled);
      union {
        int8_t real;
        uint8_t base;
      } u_chksum_error;
      u_chksum_error.base = 0;
      u_chksum_error.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->chksum_error = u_chksum_error.real;
      offset += sizeof(this->chksum_error);
      union {
        int8_t real;
        uint8_t base;
      } u_flying;
      u_flying.base = 0;
      u_flying.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->flying = u_flying.real;
      offset += sizeof(this->flying);
      union {
        int8_t real;
        uint8_t base;
      } u_motors_on;
      u_motors_on.base = 0;
      u_motors_on.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->motors_on = u_motors_on.real;
      offset += sizeof(this->motors_on);
      union {
        int16_t real;
        uint16_t base;
      } u_flightMode;
      u_flightMode.base = 0;
      u_flightMode.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_flightMode.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->flightMode = u_flightMode.real;
      offset += sizeof(this->flightMode);
      union {
        int16_t real;
        uint16_t base;
      } u_up_time;
      u_up_time.base = 0;
      u_up_time.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_up_time.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->up_time = u_up_time.real;
      offset += sizeof(this->up_time);
     return offset;
    }

    const char * getType(){ return "asctec_msgs/LLStatus"; };
    const char * getMD5(){ return "e0dae36eea5774367686a40e1843c5e2"; };

  };

}
#endif