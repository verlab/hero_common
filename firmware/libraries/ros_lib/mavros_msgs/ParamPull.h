#ifndef _ROS_SERVICE_ParamPull_h
#define _ROS_SERVICE_ParamPull_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mavros_msgs
{

static const char PARAMPULL[] = "mavros_msgs/ParamPull";

  class ParamPullRequest : public ros::Msg
  {
    public:
      bool force_pull;

    ParamPullRequest():
      force_pull(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_force_pull;
      u_force_pull.real = this->force_pull;
      *(outbuffer + offset + 0) = (u_force_pull.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->force_pull);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_force_pull;
      u_force_pull.base = 0;
      u_force_pull.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->force_pull = u_force_pull.real;
      offset += sizeof(this->force_pull);
     return offset;
    }

    const char * getType(){ return PARAMPULL; };
    const char * getMD5(){ return "16415b4e049d3f92df764eeb461102b7"; };

  };

  class ParamPullResponse : public ros::Msg
  {
    public:
      bool success;
      uint32_t param_received;

    ParamPullResponse():
      success(0),
      param_received(0)
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
      *(outbuffer + offset + 0) = (this->param_received >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->param_received >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->param_received >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->param_received >> (8 * 3)) & 0xFF;
      offset += sizeof(this->param_received);
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
      this->param_received =  ((uint32_t) (*(inbuffer + offset)));
      this->param_received |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->param_received |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->param_received |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->param_received);
     return offset;
    }

    const char * getType(){ return PARAMPULL; };
    const char * getMD5(){ return "5601e883220b149a3209512e966299f0"; };

  };

  class ParamPull {
    public:
    typedef ParamPullRequest Request;
    typedef ParamPullResponse Response;
  };

}
#endif
