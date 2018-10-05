#ifndef _ROS_teleop_tools_msgs_IncrementFeedback_h
#define _ROS_teleop_tools_msgs_IncrementFeedback_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace teleop_tools_msgs
{

  class IncrementFeedback : public ros::Msg
  {
    public:

    IncrementFeedback()
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

    const char * getType(){ return "teleop_tools_msgs/IncrementFeedback"; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

}
#endif