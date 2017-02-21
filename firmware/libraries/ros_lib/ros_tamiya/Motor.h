#ifndef _ROS_ros_tamiya_Motor_h
#define _ROS_ros_tamiya_Motor_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace ros_tamiya
{

  class Motor : public ros::Msg
  {
    public:
      int32_t motor_position;
      int32_t sterring_position;

    Motor():
      motor_position(0),
      sterring_position(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_motor_position;
      u_motor_position.real = this->motor_position;
      *(outbuffer + offset + 0) = (u_motor_position.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_position.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_position.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_position.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_position);
      union {
        int32_t real;
        uint32_t base;
      } u_sterring_position;
      u_sterring_position.real = this->sterring_position;
      *(outbuffer + offset + 0) = (u_sterring_position.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_sterring_position.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_sterring_position.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_sterring_position.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->sterring_position);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_motor_position;
      u_motor_position.base = 0;
      u_motor_position.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_position.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_position.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_position.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_position = u_motor_position.real;
      offset += sizeof(this->motor_position);
      union {
        int32_t real;
        uint32_t base;
      } u_sterring_position;
      u_sterring_position.base = 0;
      u_sterring_position.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_sterring_position.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_sterring_position.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_sterring_position.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->sterring_position = u_sterring_position.real;
      offset += sizeof(this->sterring_position);
     return offset;
    }

    const char * getType(){ return "ros_tamiya/Motor"; };
    const char * getMD5(){ return "5bab86f765adc2b3b101f81664723437"; };

  };

}
#endif