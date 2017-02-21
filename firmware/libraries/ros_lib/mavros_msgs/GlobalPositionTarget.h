#ifndef _ROS_mavros_msgs_GlobalPositionTarget_h
#define _ROS_mavros_msgs_GlobalPositionTarget_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Vector3.h"

namespace mavros_msgs
{

  class GlobalPositionTarget : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t coordinate_frame;
      uint16_t type_mask;
      float latitude;
      float longitude;
      float altitude;
      geometry_msgs::Vector3 velocity;
      geometry_msgs::Vector3 acceleration_or_force;
      float yaw;
      float yaw_rate;
      enum { FRAME_GLOBAL_INT =  5 };
      enum { FRAME_GLOBAL_REL_ALT =  6 };
      enum { FRAME_GLOBAL_TERRAIN_ALT =  11 };
      enum { IGNORE_LATITUDE =  1	 };
      enum { IGNORE_LONGITUDE =  2 };
      enum { IGNORE_ALTITUDE =  4 };
      enum { IGNORE_VX =  8	 };
      enum { IGNORE_VY =  16 };
      enum { IGNORE_VZ =  32 };
      enum { IGNORE_AFX =  64	 };
      enum { IGNORE_AFY =  128 };
      enum { IGNORE_AFZ =  256 };
      enum { FORCE =  512	 };
      enum { IGNORE_YAW =  1024 };
      enum { IGNORE_YAW_RATE =  2048 };

    GlobalPositionTarget():
      header(),
      coordinate_frame(0),
      type_mask(0),
      latitude(0),
      longitude(0),
      altitude(0),
      velocity(),
      acceleration_or_force(),
      yaw(0),
      yaw_rate(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->coordinate_frame >> (8 * 0)) & 0xFF;
      offset += sizeof(this->coordinate_frame);
      *(outbuffer + offset + 0) = (this->type_mask >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->type_mask >> (8 * 1)) & 0xFF;
      offset += sizeof(this->type_mask);
      offset += serializeAvrFloat64(outbuffer + offset, this->latitude);
      offset += serializeAvrFloat64(outbuffer + offset, this->longitude);
      union {
        float real;
        uint32_t base;
      } u_altitude;
      u_altitude.real = this->altitude;
      *(outbuffer + offset + 0) = (u_altitude.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_altitude.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_altitude.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_altitude.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->altitude);
      offset += this->velocity.serialize(outbuffer + offset);
      offset += this->acceleration_or_force.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_yaw;
      u_yaw.real = this->yaw;
      *(outbuffer + offset + 0) = (u_yaw.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_yaw.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_yaw.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_yaw.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->yaw);
      union {
        float real;
        uint32_t base;
      } u_yaw_rate;
      u_yaw_rate.real = this->yaw_rate;
      *(outbuffer + offset + 0) = (u_yaw_rate.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_yaw_rate.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_yaw_rate.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_yaw_rate.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->yaw_rate);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->coordinate_frame =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->coordinate_frame);
      this->type_mask =  ((uint16_t) (*(inbuffer + offset)));
      this->type_mask |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->type_mask);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->latitude));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->longitude));
      union {
        float real;
        uint32_t base;
      } u_altitude;
      u_altitude.base = 0;
      u_altitude.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_altitude.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_altitude.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_altitude.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->altitude = u_altitude.real;
      offset += sizeof(this->altitude);
      offset += this->velocity.deserialize(inbuffer + offset);
      offset += this->acceleration_or_force.deserialize(inbuffer + offset);
      union {
        float real;
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
        float real;
        uint32_t base;
      } u_yaw_rate;
      u_yaw_rate.base = 0;
      u_yaw_rate.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_yaw_rate.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_yaw_rate.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_yaw_rate.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->yaw_rate = u_yaw_rate.real;
      offset += sizeof(this->yaw_rate);
     return offset;
    }

    const char * getType(){ return "mavros_msgs/GlobalPositionTarget"; };
    const char * getMD5(){ return "076ded0190b9e045f9c55264659ef102"; };

  };

}
#endif