#ifndef _ROS_kobuki_msgs_AutoDockingGoal_h
#define _ROS_kobuki_msgs_AutoDockingGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace kobuki_msgs
{

  class AutoDockingGoal : public ros::Msg
  {
    public:

    AutoDockingGoal()
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

    const char * getType(){ return "kobuki_msgs/AutoDockingGoal"; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

}
#endif