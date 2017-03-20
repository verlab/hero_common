#ifndef _ROS_asctec_msgs_WaypointData_h
#define _ROS_asctec_msgs_WaypointData_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace asctec_msgs
{

  class WaypointData : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef uint8_t _wp_number_type;
      _wp_number_type wp_number;
      typedef uint8_t _dummy_1_type;
      _dummy_1_type dummy_1;
      typedef uint16_t _dummy_2_type;
      _dummy_2_type dummy_2;
      typedef uint8_t _properties_type;
      _properties_type properties;
      typedef uint8_t _max_speed_type;
      _max_speed_type max_speed;
      typedef uint16_t _time_type;
      _time_type time;
      typedef uint16_t _pos_acc_type;
      _pos_acc_type pos_acc;
      typedef int16_t _chksum_type;
      _chksum_type chksum;
      typedef int32_t _X_type;
      _X_type X;
      typedef int32_t _Y_type;
      _Y_type Y;
      typedef int32_t _yaw_type;
      _yaw_type yaw;
      typedef int32_t _height_type;
      _height_type height;
      enum { WPPROP_ABSCOORDS = 1 };
      enum { WPPROP_HEIGHTENABLED = 2 };
      enum { WPPROP_YAWENABLED = 4 };
      enum { WPPROP_AUTOMATICGOTO = 16 };
      enum { WPPROP_CAM_TRIGGER = 32 };

    WaypointData():
      header(),
      wp_number(0),
      dummy_1(0),
      dummy_2(0),
      properties(0),
      max_speed(0),
      time(0),
      pos_acc(0),
      chksum(0),
      X(0),
      Y(0),
      yaw(0),
      height(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->wp_number >> (8 * 0)) & 0xFF;
      offset += sizeof(this->wp_number);
      *(outbuffer + offset + 0) = (this->dummy_1 >> (8 * 0)) & 0xFF;
      offset += sizeof(this->dummy_1);
      *(outbuffer + offset + 0) = (this->dummy_2 >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->dummy_2 >> (8 * 1)) & 0xFF;
      offset += sizeof(this->dummy_2);
      *(outbuffer + offset + 0) = (this->properties >> (8 * 0)) & 0xFF;
      offset += sizeof(this->properties);
      *(outbuffer + offset + 0) = (this->max_speed >> (8 * 0)) & 0xFF;
      offset += sizeof(this->max_speed);
      *(outbuffer + offset + 0) = (this->time >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->time >> (8 * 1)) & 0xFF;
      offset += sizeof(this->time);
      *(outbuffer + offset + 0) = (this->pos_acc >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->pos_acc >> (8 * 1)) & 0xFF;
      offset += sizeof(this->pos_acc);
      union {
        int16_t real;
        uint16_t base;
      } u_chksum;
      u_chksum.real = this->chksum;
      *(outbuffer + offset + 0) = (u_chksum.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_chksum.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->chksum);
      union {
        int32_t real;
        uint32_t base;
      } u_X;
      u_X.real = this->X;
      *(outbuffer + offset + 0) = (u_X.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_X.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_X.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_X.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->X);
      union {
        int32_t real;
        uint32_t base;
      } u_Y;
      u_Y.real = this->Y;
      *(outbuffer + offset + 0) = (u_Y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Y);
      union {
        int32_t real;
        uint32_t base;
      } u_yaw;
      u_yaw.real = this->yaw;
      *(outbuffer + offset + 0) = (u_yaw.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_yaw.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_yaw.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_yaw.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->yaw);
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
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->wp_number =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->wp_number);
      this->dummy_1 =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->dummy_1);
      this->dummy_2 =  ((uint16_t) (*(inbuffer + offset)));
      this->dummy_2 |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->dummy_2);
      this->properties =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->properties);
      this->max_speed =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->max_speed);
      this->time =  ((uint16_t) (*(inbuffer + offset)));
      this->time |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->time);
      this->pos_acc =  ((uint16_t) (*(inbuffer + offset)));
      this->pos_acc |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->pos_acc);
      union {
        int16_t real;
        uint16_t base;
      } u_chksum;
      u_chksum.base = 0;
      u_chksum.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_chksum.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->chksum = u_chksum.real;
      offset += sizeof(this->chksum);
      union {
        int32_t real;
        uint32_t base;
      } u_X;
      u_X.base = 0;
      u_X.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_X.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_X.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_X.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->X = u_X.real;
      offset += sizeof(this->X);
      union {
        int32_t real;
        uint32_t base;
      } u_Y;
      u_Y.base = 0;
      u_Y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Y = u_Y.real;
      offset += sizeof(this->Y);
      union {
        int32_t real;
        uint32_t base;
      } u_yaw;
      u_yaw.base = 0;
      u_yaw.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_yaw.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_yaw.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_yaw.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->yaw = u_yaw.real;
      offset += sizeof(this->yaw);
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
     return offset;
    }

    const char * getType(){ return "asctec_msgs/WaypointData"; };
    const char * getMD5(){ return "1aea889573a3c976bdc966a2229943a6"; };

  };

}
#endif