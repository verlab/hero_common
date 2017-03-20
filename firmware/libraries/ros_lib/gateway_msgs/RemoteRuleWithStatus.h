#ifndef _ROS_gateway_msgs_RemoteRuleWithStatus_h
#define _ROS_gateway_msgs_RemoteRuleWithStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "gateway_msgs/RemoteRule.h"

namespace gateway_msgs
{

  class RemoteRuleWithStatus : public ros::Msg
  {
    public:
      typedef gateway_msgs::RemoteRule _remote_rule_type;
      _remote_rule_type remote_rule;
      typedef const char* _status_type;
      _status_type status;
      enum { UNKNOWN = unknown };
      enum { PENDING = pending };
      enum { ACCEPTED = accepted };
      enum { BLOCKED = blocked };
      enum { RESEND = resend };

    RemoteRuleWithStatus():
      remote_rule(),
      status("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->remote_rule.serialize(outbuffer + offset);
      uint32_t length_status = strlen(this->status);
      varToArr(outbuffer + offset, length_status);
      offset += 4;
      memcpy(outbuffer + offset, this->status, length_status);
      offset += length_status;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->remote_rule.deserialize(inbuffer + offset);
      uint32_t length_status;
      arrToVar(length_status, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_status; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_status-1]=0;
      this->status = (char *)(inbuffer + offset-1);
      offset += length_status;
     return offset;
    }

    const char * getType(){ return "gateway_msgs/RemoteRuleWithStatus"; };
    const char * getMD5(){ return "7892d8834068a87e345fff91adc26a5e"; };

  };

}
#endif