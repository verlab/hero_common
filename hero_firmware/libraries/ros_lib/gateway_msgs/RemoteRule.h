#ifndef _ROS_gateway_msgs_RemoteRule_h
#define _ROS_gateway_msgs_RemoteRule_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "gateway_msgs/Rule.h"

namespace gateway_msgs
{

  class RemoteRule : public ros::Msg
  {
    public:
      typedef const char* _gateway_type;
      _gateway_type gateway;
      typedef gateway_msgs::Rule _rule_type;
      _rule_type rule;

    RemoteRule():
      gateway(""),
      rule()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_gateway = strlen(this->gateway);
      varToArr(outbuffer + offset, length_gateway);
      offset += 4;
      memcpy(outbuffer + offset, this->gateway, length_gateway);
      offset += length_gateway;
      offset += this->rule.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_gateway;
      arrToVar(length_gateway, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_gateway; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_gateway-1]=0;
      this->gateway = (char *)(inbuffer + offset-1);
      offset += length_gateway;
      offset += this->rule.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "gateway_msgs/RemoteRule"; };
    const char * getMD5(){ return "14f4c5aaf33b32b22c50fd514747f99f"; };

  };

}
#endif