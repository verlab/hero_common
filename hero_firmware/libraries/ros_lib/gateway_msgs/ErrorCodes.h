#ifndef _ROS_gateway_msgs_ErrorCodes_h
#define _ROS_gateway_msgs_ErrorCodes_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace gateway_msgs
{

  class ErrorCodes : public ros::Msg
  {
    public:
      enum { SUCCESS =  0 };
      enum { NO_HUB_CONNECTION =  1 };
      enum { HUB_CONNECTION_ALREADY_EXISTS =  11 };
      enum { HUB_CONNECTION_UNRESOLVABLE =  12 };
      enum { HUB_CONNECTION_BLACKLISTED =  13 };
      enum { HUB_CONNECTION_FAILED =  14 };
      enum { HUB_CONNECTION_NOT_IN_NONEMPTY_WHITELIST =  15 };
      enum { HUB_NAME_NOT_FOUND =  16 };
      enum { HUB_CONNECTION_LOST =  17 };
      enum { HUB_UNKNOWN_ERROR =  19 };
      enum { FLIP_RULE_ALREADY_EXISTS =  22 };
      enum { FLIP_PATTERN_ALREDY_EXISTS =  23 };
      enum { FLIP_REMOTE_GATEWAY_FIREWALLING =  24 };
      enum { ADVERTISEMENT_EXISTS =  31 };
      enum { ADVERTISEMENT_NOT_FOUND =  32 };
      enum { UNKNOWN_ADVERTISEMENT_ERROR =  39 };
      enum { PULL_RULE_ALREADY_EXISTS =  41 };
      enum { REMOTE_GATEWAY_NOT_VISIBLE =  51 };
      enum { REMOTE_GATEWAY_SELF_IS_NOT =  52 };
      enum { REMOTE_GATEWAY_TARGET_HAS_MULTIPLE_MATCHES =  53 };

    ErrorCodes()
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

    const char * getType(){ return "gateway_msgs/ErrorCodes"; };
    const char * getMD5(){ return "cc2f69c68d11f625f99f07d82c572d47"; };

  };

}
#endif