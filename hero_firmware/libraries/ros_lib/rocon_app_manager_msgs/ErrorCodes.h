#ifndef _ROS_rocon_app_manager_msgs_ErrorCodes_h
#define _ROS_rocon_app_manager_msgs_ErrorCodes_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rocon_app_manager_msgs
{

  class ErrorCodes : public ros::Msg
  {
    public:
      enum { SUCCESS =  0 };
      enum { UNKNOWN =  1 };
      enum { MULTI_RAPP_NOT_SUPPORTED =  10 };
      enum { RAPP_IS_NOT_RUNNING =  20 };
      enum { RAPP_IS_NOT_AVAILABLE =  21 };
      enum { LOCAL_INVITATIONS_ONLY =  30 };
      enum { NO_LOCAL_GATEWAY =  31 };
      enum { ALREADY_REMOTE_CONTROLLED =  32 };
      enum { NOT_CURRENT_REMOTE_CONTROLLER =  33 };
      enum { INVITING_CONTROLLER_NOT_WHITELISTED =  34 };
      enum { INVITING_CONTROLLER_BLACKLISTED =  35 };
      enum { CLIENT_CONNECTION_DISRUPTED =  36 };

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

    const char * getType(){ return "rocon_app_manager_msgs/ErrorCodes"; };
    const char * getMD5(){ return "cec38b743e8d5698477f7be4d8bfebb8"; };

  };

}
#endif