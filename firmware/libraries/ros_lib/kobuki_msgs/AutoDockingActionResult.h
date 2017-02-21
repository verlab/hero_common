#ifndef _ROS_kobuki_msgs_AutoDockingActionResult_h
#define _ROS_kobuki_msgs_AutoDockingActionResult_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalStatus.h"
#include "kobuki_msgs/AutoDockingResult.h"

namespace kobuki_msgs
{

  class AutoDockingActionResult : public ros::Msg
  {
    public:
      std_msgs::Header header;
      actionlib_msgs::GoalStatus status;
      kobuki_msgs::AutoDockingResult result;

    AutoDockingActionResult():
      header(),
      status(),
      result()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->status.serialize(outbuffer + offset);
      offset += this->result.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->status.deserialize(inbuffer + offset);
      offset += this->result.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "kobuki_msgs/AutoDockingActionResult"; };
    const char * getMD5(){ return "3fb2b9cd9cec6b4cb23b224521dd7679"; };

  };

}
#endif