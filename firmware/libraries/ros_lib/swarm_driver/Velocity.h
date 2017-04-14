#ifndef _ROS_swarm_driver_Velocity_h
#define _ROS_swarm_driver_Velocity_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace swarm_driver
{

  class Velocity : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef float _linear_type;
      _linear_type linear;
      typedef float _angular_type;
      _angular_type angular;

    Velocity():
      header(),
      linear(0),
      angular(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_linear;
      u_linear.real = this->linear;
      *(outbuffer + offset + 0) = (u_linear.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_linear.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_linear.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_linear.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->linear);
      union {
        float real;
        uint32_t base;
      } u_angular;
      u_angular.real = this->angular;
      *(outbuffer + offset + 0) = (u_angular.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angular.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_angular.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_angular.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angular);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_linear;
      u_linear.base = 0;
      u_linear.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_linear.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_linear.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_linear.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->linear = u_linear.real;
      offset += sizeof(this->linear);
      union {
        float real;
        uint32_t base;
      } u_angular;
      u_angular.base = 0;
      u_angular.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angular.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_angular.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_angular.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angular = u_angular.real;
      offset += sizeof(this->angular);
     return offset;
    }

    const char * getType(){ return "swarm_driver/Velocity"; };
    const char * getMD5(){ return "215d3ee11f20ae66e36af8ba0b3fba98"; };

  };

}
#endif