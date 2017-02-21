#ifndef _ROS_rocon_app_manager_msgs_Constants_h
#define _ROS_rocon_app_manager_msgs_Constants_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rocon_app_manager_msgs
{

  class Constants : public ros::Msg
  {
    public:
      enum { NO_REMOTE_CONNECTION = none };
      enum { NO_REMOTE_CONTROLLER = none };

    Constants()
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

    const char * getType(){ return "rocon_app_manager_msgs/Constants"; };
    const char * getMD5(){ return "8dc55825f8d5b0d293568ddca66ef50f"; };

  };

}
#endif