#ifndef _ROS_SERVICE_CommandTriggerControl_h
#define _ROS_SERVICE_CommandTriggerControl_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mavros_msgs
{

static const char COMMANDTRIGGERCONTROL[] = "mavros_msgs/CommandTriggerControl";

  class CommandTriggerControlRequest : public ros::Msg
  {
    public:
      bool trigger_enable;
      float integration_time;

    CommandTriggerControlRequest():
      trigger_enable(0),
      integration_time(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_trigger_enable;
      u_trigger_enable.real = this->trigger_enable;
      *(outbuffer + offset + 0) = (u_trigger_enable.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->trigger_enable);
      union {
        float real;
        uint32_t base;
      } u_integration_time;
      u_integration_time.real = this->integration_time;
      *(outbuffer + offset + 0) = (u_integration_time.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_integration_time.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_integration_time.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_integration_time.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->integration_time);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_trigger_enable;
      u_trigger_enable.base = 0;
      u_trigger_enable.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->trigger_enable = u_trigger_enable.real;
      offset += sizeof(this->trigger_enable);
      union {
        float real;
        uint32_t base;
      } u_integration_time;
      u_integration_time.base = 0;
      u_integration_time.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_integration_time.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_integration_time.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_integration_time.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->integration_time = u_integration_time.real;
      offset += sizeof(this->integration_time);
     return offset;
    }

    const char * getType(){ return COMMANDTRIGGERCONTROL; };
    const char * getMD5(){ return "8b8f5196da8cf0a44cb3975e4f2ea948"; };

  };

  class CommandTriggerControlResponse : public ros::Msg
  {
    public:
      bool success;
      uint8_t result;

    CommandTriggerControlResponse():
      success(0),
      result(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      *(outbuffer + offset + 0) = (this->result >> (8 * 0)) & 0xFF;
      offset += sizeof(this->result);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
      this->result =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->result);
     return offset;
    }

    const char * getType(){ return COMMANDTRIGGERCONTROL; };
    const char * getMD5(){ return "1cd894375e4e3d2861d2222772894fdb"; };

  };

  class CommandTriggerControl {
    public:
    typedef CommandTriggerControlRequest Request;
    typedef CommandTriggerControlResponse Response;
  };

}
#endif
