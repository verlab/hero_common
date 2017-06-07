#ifndef _ROS_SERVICE_ChangeDesPose_h
#define _ROS_SERVICE_ChangeDesPose_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mav_srvs
{

static const char CHANGEDESPOSE[] = "mav_srvs/ChangeDesPose";

  class ChangeDesPoseRequest : public ros::Msg
  {
    public:
      typedef double _delta_x_type;
      _delta_x_type delta_x;
      typedef double _delta_y_type;
      _delta_y_type delta_y;
      typedef double _delta_z_type;
      _delta_z_type delta_z;
      typedef double _delta_yaw_type;
      _delta_yaw_type delta_yaw;

    ChangeDesPoseRequest():
      delta_x(0),
      delta_y(0),
      delta_z(0),
      delta_yaw(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        double real;
        uint64_t base;
      } u_delta_x;
      u_delta_x.real = this->delta_x;
      *(outbuffer + offset + 0) = (u_delta_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_delta_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_delta_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_delta_x.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_delta_x.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_delta_x.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_delta_x.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_delta_x.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->delta_x);
      union {
        double real;
        uint64_t base;
      } u_delta_y;
      u_delta_y.real = this->delta_y;
      *(outbuffer + offset + 0) = (u_delta_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_delta_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_delta_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_delta_y.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_delta_y.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_delta_y.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_delta_y.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_delta_y.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->delta_y);
      union {
        double real;
        uint64_t base;
      } u_delta_z;
      u_delta_z.real = this->delta_z;
      *(outbuffer + offset + 0) = (u_delta_z.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_delta_z.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_delta_z.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_delta_z.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_delta_z.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_delta_z.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_delta_z.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_delta_z.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->delta_z);
      union {
        double real;
        uint64_t base;
      } u_delta_yaw;
      u_delta_yaw.real = this->delta_yaw;
      *(outbuffer + offset + 0) = (u_delta_yaw.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_delta_yaw.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_delta_yaw.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_delta_yaw.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_delta_yaw.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_delta_yaw.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_delta_yaw.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_delta_yaw.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->delta_yaw);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        double real;
        uint64_t base;
      } u_delta_x;
      u_delta_x.base = 0;
      u_delta_x.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_delta_x.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_delta_x.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_delta_x.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_delta_x.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_delta_x.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_delta_x.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_delta_x.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->delta_x = u_delta_x.real;
      offset += sizeof(this->delta_x);
      union {
        double real;
        uint64_t base;
      } u_delta_y;
      u_delta_y.base = 0;
      u_delta_y.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_delta_y.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_delta_y.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_delta_y.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_delta_y.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_delta_y.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_delta_y.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_delta_y.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->delta_y = u_delta_y.real;
      offset += sizeof(this->delta_y);
      union {
        double real;
        uint64_t base;
      } u_delta_z;
      u_delta_z.base = 0;
      u_delta_z.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_delta_z.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_delta_z.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_delta_z.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_delta_z.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_delta_z.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_delta_z.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_delta_z.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->delta_z = u_delta_z.real;
      offset += sizeof(this->delta_z);
      union {
        double real;
        uint64_t base;
      } u_delta_yaw;
      u_delta_yaw.base = 0;
      u_delta_yaw.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_delta_yaw.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_delta_yaw.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_delta_yaw.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_delta_yaw.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_delta_yaw.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_delta_yaw.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_delta_yaw.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->delta_yaw = u_delta_yaw.real;
      offset += sizeof(this->delta_yaw);
     return offset;
    }

    const char * getType(){ return CHANGEDESPOSE; };
    const char * getMD5(){ return "d7fc6ebd227f042943398b515a57e14f"; };

  };

  class ChangeDesPoseResponse : public ros::Msg
  {
    public:

    ChangeDesPoseResponse()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return CHANGEDESPOSE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class ChangeDesPose {
    public:
    typedef ChangeDesPoseRequest Request;
    typedef ChangeDesPoseResponse Response;
  };

}
#endif
