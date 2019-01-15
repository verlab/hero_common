#ifndef _ROS_SERVICE_SetWatcherPeriod_h
#define _ROS_SERVICE_SetWatcherPeriod_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace gateway_msgs
{

static const char SETWATCHERPERIOD[] = "gateway_msgs/SetWatcherPeriod";

  class SetWatcherPeriodRequest : public ros::Msg
  {
    public:
      typedef float _period_type;
      _period_type period;

    SetWatcherPeriodRequest():
      period(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_period;
      u_period.real = this->period;
      *(outbuffer + offset + 0) = (u_period.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_period.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_period.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_period.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->period);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_period;
      u_period.base = 0;
      u_period.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_period.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_period.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_period.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->period = u_period.real;
      offset += sizeof(this->period);
     return offset;
    }

    const char * getType(){ return SETWATCHERPERIOD; };
    const char * getMD5(){ return "3bfcf350fbd9f1aad223e564a8c1f0dd"; };

  };

  class SetWatcherPeriodResponse : public ros::Msg
  {
    public:
      typedef float _last_period_type;
      _last_period_type last_period;

    SetWatcherPeriodResponse():
      last_period(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_last_period;
      u_last_period.real = this->last_period;
      *(outbuffer + offset + 0) = (u_last_period.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_last_period.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_last_period.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_last_period.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->last_period);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_last_period;
      u_last_period.base = 0;
      u_last_period.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_last_period.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_last_period.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_last_period.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->last_period = u_last_period.real;
      offset += sizeof(this->last_period);
     return offset;
    }

    const char * getType(){ return SETWATCHERPERIOD; };
    const char * getMD5(){ return "dbc70bcb9b617c59da49b8be04454dd5"; };

  };

  class SetWatcherPeriod {
    public:
    typedef SetWatcherPeriodRequest Request;
    typedef SetWatcherPeriodResponse Response;
  };

}
#endif
