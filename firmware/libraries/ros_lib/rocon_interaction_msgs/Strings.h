#ifndef _ROS_rocon_interaction_msgs_Strings_h
#define _ROS_rocon_interaction_msgs_Strings_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rocon_interaction_msgs
{

  class Strings : public ros::Msg
  {
    public:
      enum { REMOCONS_NAMESPACE =  /remocons };

    Strings()
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

    const char * getType(){ return "rocon_interaction_msgs/Strings"; };
    const char * getMD5(){ return "7279ef1b62bbde7b3bec17766ef2c127"; };

  };

}
#endif