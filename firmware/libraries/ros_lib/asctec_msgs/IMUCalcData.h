#ifndef _ROS_asctec_msgs_IMUCalcData_h
#define _ROS_asctec_msgs_IMUCalcData_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace asctec_msgs
{

  class IMUCalcData : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef int32_t _angle_nick_type;
      _angle_nick_type angle_nick;
      typedef int32_t _angle_roll_type;
      _angle_roll_type angle_roll;
      typedef int32_t _angle_yaw_type;
      _angle_yaw_type angle_yaw;
      typedef int32_t _angvel_nick_type;
      _angvel_nick_type angvel_nick;
      typedef int32_t _angvel_roll_type;
      _angvel_roll_type angvel_roll;
      typedef int32_t _angvel_yaw_type;
      _angvel_yaw_type angvel_yaw;
      typedef int16_t _acc_x_calib_type;
      _acc_x_calib_type acc_x_calib;
      typedef int16_t _acc_y_calib_type;
      _acc_y_calib_type acc_y_calib;
      typedef int16_t _acc_z_calib_type;
      _acc_z_calib_type acc_z_calib;
      typedef int16_t _acc_x_type;
      _acc_x_type acc_x;
      typedef int16_t _acc_y_type;
      _acc_y_type acc_y;
      typedef int16_t _acc_z_type;
      _acc_z_type acc_z;
      typedef int32_t _acc_angle_nick_type;
      _acc_angle_nick_type acc_angle_nick;
      typedef int32_t _acc_angle_roll_type;
      _acc_angle_roll_type acc_angle_roll;
      typedef int32_t _acc_absolute_value_type;
      _acc_absolute_value_type acc_absolute_value;
      typedef int32_t _Hx_type;
      _Hx_type Hx;
      typedef int32_t _Hy_type;
      _Hy_type Hy;
      typedef int32_t _Hz_type;
      _Hz_type Hz;
      typedef int32_t _mag_heading_type;
      _mag_heading_type mag_heading;
      typedef int32_t _speed_x_type;
      _speed_x_type speed_x;
      typedef int32_t _speed_y_type;
      _speed_y_type speed_y;
      typedef int32_t _speed_z_type;
      _speed_z_type speed_z;
      typedef int32_t _height_type;
      _height_type height;
      typedef int32_t _dheight_type;
      _dheight_type dheight;
      typedef int32_t _dheight_reference_type;
      _dheight_reference_type dheight_reference;
      typedef int32_t _height_reference_type;
      _height_reference_type height_reference;

    IMUCalcData():
      header(),
      angle_nick(0),
      angle_roll(0),
      angle_yaw(0),
      angvel_nick(0),
      angvel_roll(0),
      angvel_yaw(0),
      acc_x_calib(0),
      acc_y_calib(0),
      acc_z_calib(0),
      acc_x(0),
      acc_y(0),
      acc_z(0),
      acc_angle_nick(0),
      acc_angle_roll(0),
      acc_absolute_value(0),
      Hx(0),
      Hy(0),
      Hz(0),
      mag_heading(0),
      speed_x(0),
      speed_y(0),
      speed_z(0),
      height(0),
      dheight(0),
      dheight_reference(0),
      height_reference(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_angle_nick;
      u_angle_nick.real = this->angle_nick;
      *(outbuffer + offset + 0) = (u_angle_nick.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angle_nick.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_angle_nick.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_angle_nick.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angle_nick);
      union {
        int32_t real;
        uint32_t base;
      } u_angle_roll;
      u_angle_roll.real = this->angle_roll;
      *(outbuffer + offset + 0) = (u_angle_roll.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angle_roll.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_angle_roll.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_angle_roll.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angle_roll);
      union {
        int32_t real;
        uint32_t base;
      } u_angle_yaw;
      u_angle_yaw.real = this->angle_yaw;
      *(outbuffer + offset + 0) = (u_angle_yaw.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angle_yaw.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_angle_yaw.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_angle_yaw.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angle_yaw);
      union {
        int32_t real;
        uint32_t base;
      } u_angvel_nick;
      u_angvel_nick.real = this->angvel_nick;
      *(outbuffer + offset + 0) = (u_angvel_nick.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angvel_nick.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_angvel_nick.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_angvel_nick.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angvel_nick);
      union {
        int32_t real;
        uint32_t base;
      } u_angvel_roll;
      u_angvel_roll.real = this->angvel_roll;
      *(outbuffer + offset + 0) = (u_angvel_roll.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angvel_roll.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_angvel_roll.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_angvel_roll.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angvel_roll);
      union {
        int32_t real;
        uint32_t base;
      } u_angvel_yaw;
      u_angvel_yaw.real = this->angvel_yaw;
      *(outbuffer + offset + 0) = (u_angvel_yaw.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angvel_yaw.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_angvel_yaw.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_angvel_yaw.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angvel_yaw);
      union {
        int16_t real;
        uint16_t base;
      } u_acc_x_calib;
      u_acc_x_calib.real = this->acc_x_calib;
      *(outbuffer + offset + 0) = (u_acc_x_calib.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_acc_x_calib.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->acc_x_calib);
      union {
        int16_t real;
        uint16_t base;
      } u_acc_y_calib;
      u_acc_y_calib.real = this->acc_y_calib;
      *(outbuffer + offset + 0) = (u_acc_y_calib.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_acc_y_calib.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->acc_y_calib);
      union {
        int16_t real;
        uint16_t base;
      } u_acc_z_calib;
      u_acc_z_calib.real = this->acc_z_calib;
      *(outbuffer + offset + 0) = (u_acc_z_calib.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_acc_z_calib.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->acc_z_calib);
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
        int32_t real;
        uint32_t base;
      } u_acc_angle_nick;
      u_acc_angle_nick.real = this->acc_angle_nick;
      *(outbuffer + offset + 0) = (u_acc_angle_nick.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_acc_angle_nick.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_acc_angle_nick.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_acc_angle_nick.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->acc_angle_nick);
      union {
        int32_t real;
        uint32_t base;
      } u_acc_angle_roll;
      u_acc_angle_roll.real = this->acc_angle_roll;
      *(outbuffer + offset + 0) = (u_acc_angle_roll.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_acc_angle_roll.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_acc_angle_roll.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_acc_angle_roll.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->acc_angle_roll);
      union {
        int32_t real;
        uint32_t base;
      } u_acc_absolute_value;
      u_acc_absolute_value.real = this->acc_absolute_value;
      *(outbuffer + offset + 0) = (u_acc_absolute_value.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_acc_absolute_value.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_acc_absolute_value.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_acc_absolute_value.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->acc_absolute_value);
      union {
        int32_t real;
        uint32_t base;
      } u_Hx;
      u_Hx.real = this->Hx;
      *(outbuffer + offset + 0) = (u_Hx.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Hx.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Hx.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Hx.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Hx);
      union {
        int32_t real;
        uint32_t base;
      } u_Hy;
      u_Hy.real = this->Hy;
      *(outbuffer + offset + 0) = (u_Hy.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Hy.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Hy.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Hy.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Hy);
      union {
        int32_t real;
        uint32_t base;
      } u_Hz;
      u_Hz.real = this->Hz;
      *(outbuffer + offset + 0) = (u_Hz.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Hz.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Hz.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Hz.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Hz);
      union {
        int32_t real;
        uint32_t base;
      } u_mag_heading;
      u_mag_heading.real = this->mag_heading;
      *(outbuffer + offset + 0) = (u_mag_heading.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_mag_heading.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_mag_heading.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_mag_heading.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->mag_heading);
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
      } u_speed_z;
      u_speed_z.real = this->speed_z;
      *(outbuffer + offset + 0) = (u_speed_z.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_speed_z.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_speed_z.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_speed_z.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->speed_z);
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
      } u_dheight;
      u_dheight.real = this->dheight;
      *(outbuffer + offset + 0) = (u_dheight.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_dheight.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_dheight.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_dheight.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->dheight);
      union {
        int32_t real;
        uint32_t base;
      } u_dheight_reference;
      u_dheight_reference.real = this->dheight_reference;
      *(outbuffer + offset + 0) = (u_dheight_reference.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_dheight_reference.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_dheight_reference.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_dheight_reference.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->dheight_reference);
      union {
        int32_t real;
        uint32_t base;
      } u_height_reference;
      u_height_reference.real = this->height_reference;
      *(outbuffer + offset + 0) = (u_height_reference.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_height_reference.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_height_reference.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_height_reference.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->height_reference);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_angle_nick;
      u_angle_nick.base = 0;
      u_angle_nick.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angle_nick.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_angle_nick.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_angle_nick.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angle_nick = u_angle_nick.real;
      offset += sizeof(this->angle_nick);
      union {
        int32_t real;
        uint32_t base;
      } u_angle_roll;
      u_angle_roll.base = 0;
      u_angle_roll.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angle_roll.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_angle_roll.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_angle_roll.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angle_roll = u_angle_roll.real;
      offset += sizeof(this->angle_roll);
      union {
        int32_t real;
        uint32_t base;
      } u_angle_yaw;
      u_angle_yaw.base = 0;
      u_angle_yaw.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angle_yaw.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_angle_yaw.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_angle_yaw.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angle_yaw = u_angle_yaw.real;
      offset += sizeof(this->angle_yaw);
      union {
        int32_t real;
        uint32_t base;
      } u_angvel_nick;
      u_angvel_nick.base = 0;
      u_angvel_nick.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angvel_nick.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_angvel_nick.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_angvel_nick.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angvel_nick = u_angvel_nick.real;
      offset += sizeof(this->angvel_nick);
      union {
        int32_t real;
        uint32_t base;
      } u_angvel_roll;
      u_angvel_roll.base = 0;
      u_angvel_roll.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angvel_roll.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_angvel_roll.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_angvel_roll.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angvel_roll = u_angvel_roll.real;
      offset += sizeof(this->angvel_roll);
      union {
        int32_t real;
        uint32_t base;
      } u_angvel_yaw;
      u_angvel_yaw.base = 0;
      u_angvel_yaw.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angvel_yaw.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_angvel_yaw.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_angvel_yaw.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angvel_yaw = u_angvel_yaw.real;
      offset += sizeof(this->angvel_yaw);
      union {
        int16_t real;
        uint16_t base;
      } u_acc_x_calib;
      u_acc_x_calib.base = 0;
      u_acc_x_calib.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_acc_x_calib.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->acc_x_calib = u_acc_x_calib.real;
      offset += sizeof(this->acc_x_calib);
      union {
        int16_t real;
        uint16_t base;
      } u_acc_y_calib;
      u_acc_y_calib.base = 0;
      u_acc_y_calib.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_acc_y_calib.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->acc_y_calib = u_acc_y_calib.real;
      offset += sizeof(this->acc_y_calib);
      union {
        int16_t real;
        uint16_t base;
      } u_acc_z_calib;
      u_acc_z_calib.base = 0;
      u_acc_z_calib.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_acc_z_calib.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->acc_z_calib = u_acc_z_calib.real;
      offset += sizeof(this->acc_z_calib);
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
        int32_t real;
        uint32_t base;
      } u_acc_angle_nick;
      u_acc_angle_nick.base = 0;
      u_acc_angle_nick.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_acc_angle_nick.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_acc_angle_nick.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_acc_angle_nick.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->acc_angle_nick = u_acc_angle_nick.real;
      offset += sizeof(this->acc_angle_nick);
      union {
        int32_t real;
        uint32_t base;
      } u_acc_angle_roll;
      u_acc_angle_roll.base = 0;
      u_acc_angle_roll.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_acc_angle_roll.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_acc_angle_roll.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_acc_angle_roll.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->acc_angle_roll = u_acc_angle_roll.real;
      offset += sizeof(this->acc_angle_roll);
      union {
        int32_t real;
        uint32_t base;
      } u_acc_absolute_value;
      u_acc_absolute_value.base = 0;
      u_acc_absolute_value.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_acc_absolute_value.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_acc_absolute_value.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_acc_absolute_value.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->acc_absolute_value = u_acc_absolute_value.real;
      offset += sizeof(this->acc_absolute_value);
      union {
        int32_t real;
        uint32_t base;
      } u_Hx;
      u_Hx.base = 0;
      u_Hx.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Hx.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Hx.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Hx.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Hx = u_Hx.real;
      offset += sizeof(this->Hx);
      union {
        int32_t real;
        uint32_t base;
      } u_Hy;
      u_Hy.base = 0;
      u_Hy.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Hy.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Hy.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Hy.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Hy = u_Hy.real;
      offset += sizeof(this->Hy);
      union {
        int32_t real;
        uint32_t base;
      } u_Hz;
      u_Hz.base = 0;
      u_Hz.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Hz.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Hz.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Hz.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Hz = u_Hz.real;
      offset += sizeof(this->Hz);
      union {
        int32_t real;
        uint32_t base;
      } u_mag_heading;
      u_mag_heading.base = 0;
      u_mag_heading.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_mag_heading.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_mag_heading.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_mag_heading.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->mag_heading = u_mag_heading.real;
      offset += sizeof(this->mag_heading);
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
      } u_speed_z;
      u_speed_z.base = 0;
      u_speed_z.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_speed_z.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_speed_z.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_speed_z.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->speed_z = u_speed_z.real;
      offset += sizeof(this->speed_z);
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
      } u_dheight;
      u_dheight.base = 0;
      u_dheight.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_dheight.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_dheight.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_dheight.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->dheight = u_dheight.real;
      offset += sizeof(this->dheight);
      union {
        int32_t real;
        uint32_t base;
      } u_dheight_reference;
      u_dheight_reference.base = 0;
      u_dheight_reference.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_dheight_reference.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_dheight_reference.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_dheight_reference.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->dheight_reference = u_dheight_reference.real;
      offset += sizeof(this->dheight_reference);
      union {
        int32_t real;
        uint32_t base;
      } u_height_reference;
      u_height_reference.base = 0;
      u_height_reference.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_height_reference.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_height_reference.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_height_reference.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->height_reference = u_height_reference.real;
      offset += sizeof(this->height_reference);
     return offset;
    }

    const char * getType(){ return "asctec_msgs/IMUCalcData"; };
    const char * getMD5(){ return "69fa9ec7b73af705eabe7dcbfd39ac85"; };

  };

}
#endif