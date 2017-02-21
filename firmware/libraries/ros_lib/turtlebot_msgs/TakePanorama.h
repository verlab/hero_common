#ifndef _ROS_SERVICE_TakePanorama_h
#define _ROS_SERVICE_TakePanorama_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace turtlebot_msgs
{

static const char TAKEPANORAMA[] = "turtlebot_msgs/TakePanorama";

  class TakePanoramaRequest : public ros::Msg
  {
    public:
      uint8_t mode;
      float pano_angle;
      float snap_interval;
      float rot_vel;
      enum { SNAPANDROTATE = 0 };
      enum { CONTINUOUS = 1 };
      enum { STOP = 2 };

    TakePanoramaRequest():
      mode(0),
      pano_angle(0),
      snap_interval(0),
      rot_vel(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->mode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->mode);
      union {
        float real;
        uint32_t base;
      } u_pano_angle;
      u_pano_angle.real = this->pano_angle;
      *(outbuffer + offset + 0) = (u_pano_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pano_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pano_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pano_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pano_angle);
      union {
        float real;
        uint32_t base;
      } u_snap_interval;
      u_snap_interval.real = this->snap_interval;
      *(outbuffer + offset + 0) = (u_snap_interval.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_snap_interval.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_snap_interval.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_snap_interval.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->snap_interval);
      union {
        float real;
        uint32_t base;
      } u_rot_vel;
      u_rot_vel.real = this->rot_vel;
      *(outbuffer + offset + 0) = (u_rot_vel.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rot_vel.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rot_vel.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rot_vel.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rot_vel);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->mode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->mode);
      union {
        float real;
        uint32_t base;
      } u_pano_angle;
      u_pano_angle.base = 0;
      u_pano_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pano_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pano_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pano_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pano_angle = u_pano_angle.real;
      offset += sizeof(this->pano_angle);
      union {
        float real;
        uint32_t base;
      } u_snap_interval;
      u_snap_interval.base = 0;
      u_snap_interval.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_snap_interval.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_snap_interval.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_snap_interval.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->snap_interval = u_snap_interval.real;
      offset += sizeof(this->snap_interval);
      union {
        float real;
        uint32_t base;
      } u_rot_vel;
      u_rot_vel.base = 0;
      u_rot_vel.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_rot_vel.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_rot_vel.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_rot_vel.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->rot_vel = u_rot_vel.real;
      offset += sizeof(this->rot_vel);
     return offset;
    }

    const char * getType(){ return TAKEPANORAMA; };
    const char * getMD5(){ return "f52c694c82704221735cc576c7587ecc"; };

  };

  class TakePanoramaResponse : public ros::Msg
  {
    public:
      uint8_t status;
      enum { STARTED = 0 };
      enum { IN_PROGRESS = 1 };
      enum { STOPPED = 2 };

    TakePanoramaResponse():
      status(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->status >> (8 * 0)) & 0xFF;
      offset += sizeof(this->status);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->status =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->status);
     return offset;
    }

    const char * getType(){ return TAKEPANORAMA; };
    const char * getMD5(){ return "1ebe3e03b034aa9578d367d7cf6ed627"; };

  };

  class TakePanorama {
    public:
    typedef TakePanoramaRequest Request;
    typedef TakePanoramaResponse Response;
  };

}
#endif
