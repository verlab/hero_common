#ifndef _ROS_asctec_msgs_IMURawData_h
#define _ROS_asctec_msgs_IMURawData_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace asctec_msgs
{

  class IMURawData : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef int32_t _pressure_type;
      _pressure_type pressure;
      typedef int16_t _gyro_x_type;
      _gyro_x_type gyro_x;
      typedef int16_t _gyro_y_type;
      _gyro_y_type gyro_y;
      typedef int16_t _gyro_z_type;
      _gyro_z_type gyro_z;
      typedef int16_t _mag_x_type;
      _mag_x_type mag_x;
      typedef int16_t _mag_y_type;
      _mag_y_type mag_y;
      typedef int16_t _mag_z_type;
      _mag_z_type mag_z;
      typedef int16_t _acc_x_type;
      _acc_x_type acc_x;
      typedef int16_t _acc_y_type;
      _acc_y_type acc_y;
      typedef int16_t _acc_z_type;
      _acc_z_type acc_z;
      typedef int16_t _temp_gyro_type;
      _temp_gyro_type temp_gyro;
      typedef int32_t _temp_ADC_type;
      _temp_ADC_type temp_ADC;

    IMURawData():
      header(),
      pressure(0),
      gyro_x(0),
      gyro_y(0),
      gyro_z(0),
      mag_x(0),
      mag_y(0),
      mag_z(0),
      acc_x(0),
      acc_y(0),
      acc_z(0),
      temp_gyro(0),
      temp_ADC(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_pressure;
      u_pressure.real = this->pressure;
      *(outbuffer + offset + 0) = (u_pressure.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pressure.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pressure.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pressure.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pressure);
      union {
        int16_t real;
        uint16_t base;
      } u_gyro_x;
      u_gyro_x.real = this->gyro_x;
      *(outbuffer + offset + 0) = (u_gyro_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_gyro_x.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->gyro_x);
      union {
        int16_t real;
        uint16_t base;
      } u_gyro_y;
      u_gyro_y.real = this->gyro_y;
      *(outbuffer + offset + 0) = (u_gyro_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_gyro_y.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->gyro_y);
      union {
        int16_t real;
        uint16_t base;
      } u_gyro_z;
      u_gyro_z.real = this->gyro_z;
      *(outbuffer + offset + 0) = (u_gyro_z.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_gyro_z.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->gyro_z);
      union {
        int16_t real;
        uint16_t base;
      } u_mag_x;
      u_mag_x.real = this->mag_x;
      *(outbuffer + offset + 0) = (u_mag_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_mag_x.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->mag_x);
      union {
        int16_t real;
        uint16_t base;
      } u_mag_y;
      u_mag_y.real = this->mag_y;
      *(outbuffer + offset + 0) = (u_mag_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_mag_y.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->mag_y);
      union {
        int16_t real;
        uint16_t base;
      } u_mag_z;
      u_mag_z.real = this->mag_z;
      *(outbuffer + offset + 0) = (u_mag_z.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_mag_z.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->mag_z);
      union {
        int16_t real;
        uint16_t base;
      } u_acc_x;
      u_acc_x.real = this->acc_x;
      *(outbuffer + offset + 0) = (u_acc_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_acc_x.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->acc_x);
      union {
        int16_t real;
        uint16_t base;
      } u_acc_y;
      u_acc_y.real = this->acc_y;
      *(outbuffer + offset + 0) = (u_acc_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_acc_y.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->acc_y);
      union {
        int16_t real;
        uint16_t base;
      } u_acc_z;
      u_acc_z.real = this->acc_z;
      *(outbuffer + offset + 0) = (u_acc_z.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_acc_z.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->acc_z);
      union {
        int16_t real;
        uint16_t base;
      } u_temp_gyro;
      u_temp_gyro.real = this->temp_gyro;
      *(outbuffer + offset + 0) = (u_temp_gyro.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_temp_gyro.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->temp_gyro);
      union {
        int32_t real;
        uint32_t base;
      } u_temp_ADC;
      u_temp_ADC.real = this->temp_ADC;
      *(outbuffer + offset + 0) = (u_temp_ADC.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_temp_ADC.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_temp_ADC.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_temp_ADC.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->temp_ADC);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_pressure;
      u_pressure.base = 0;
      u_pressure.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pressure.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pressure.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pressure.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pressure = u_pressure.real;
      offset += sizeof(this->pressure);
      union {
        int16_t real;
        uint16_t base;
      } u_gyro_x;
      u_gyro_x.base = 0;
      u_gyro_x.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_gyro_x.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->gyro_x = u_gyro_x.real;
      offset += sizeof(this->gyro_x);
      union {
        int16_t real;
        uint16_t base;
      } u_gyro_y;
      u_gyro_y.base = 0;
      u_gyro_y.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_gyro_y.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->gyro_y = u_gyro_y.real;
      offset += sizeof(this->gyro_y);
      union {
        int16_t real;
        uint16_t base;
      } u_gyro_z;
      u_gyro_z.base = 0;
      u_gyro_z.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_gyro_z.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->gyro_z = u_gyro_z.real;
      offset += sizeof(this->gyro_z);
      union {
        int16_t real;
        uint16_t base;
      } u_mag_x;
      u_mag_x.base = 0;
      u_mag_x.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_mag_x.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->mag_x = u_mag_x.real;
      offset += sizeof(this->mag_x);
      union {
        int16_t real;
        uint16_t base;
      } u_mag_y;
      u_mag_y.base = 0;
      u_mag_y.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_mag_y.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->mag_y = u_mag_y.real;
      offset += sizeof(this->mag_y);
      union {
        int16_t real;
        uint16_t base;
      } u_mag_z;
      u_mag_z.base = 0;
      u_mag_z.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_mag_z.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->mag_z = u_mag_z.real;
      offset += sizeof(this->mag_z);
      union {
        int16_t real;
        uint16_t base;
      } u_acc_x;
      u_acc_x.base = 0;
      u_acc_x.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_acc_x.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->acc_x = u_acc_x.real;
      offset += sizeof(this->acc_x);
      union {
        int16_t real;
        uint16_t base;
      } u_acc_y;
      u_acc_y.base = 0;
      u_acc_y.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_acc_y.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->acc_y = u_acc_y.real;
      offset += sizeof(this->acc_y);
      union {
        int16_t real;
        uint16_t base;
      } u_acc_z;
      u_acc_z.base = 0;
      u_acc_z.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_acc_z.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->acc_z = u_acc_z.real;
      offset += sizeof(this->acc_z);
      union {
        int16_t real;
        uint16_t base;
      } u_temp_gyro;
      u_temp_gyro.base = 0;
      u_temp_gyro.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_temp_gyro.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->temp_gyro = u_temp_gyro.real;
      offset += sizeof(this->temp_gyro);
      union {
        int32_t real;
        uint32_t base;
      } u_temp_ADC;
      u_temp_ADC.base = 0;
      u_temp_ADC.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_temp_ADC.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_temp_ADC.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_temp_ADC.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->temp_ADC = u_temp_ADC.real;
      offset += sizeof(this->temp_ADC);
     return offset;
    }

    const char * getType(){ return "asctec_msgs/IMURawData"; };
    const char * getMD5(){ return "2cfd4b9ba0bc72be7f937c948d990cd9"; };

  };

}
#endif