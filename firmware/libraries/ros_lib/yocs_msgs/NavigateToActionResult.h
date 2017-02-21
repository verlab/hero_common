#ifndef _ROS_yocs_msgs_NavigateToActionResult_h
#define _ROS_yocs_msgs_NavigateToActionResult_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalStatus.h"
#include "yocs_msgs/NavigateToResult.h"

namespace yocs_msgs
{

  class NavigateToActionResult : public ros::Msg
  {
    public:
      std_msgs::Header header;
      actionlib_msgs::GoalStatus status;
      yocs_msgs::NavigateToResult result;

    NavigateToActionResult():
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

    const char * getType(){ return "yocs_msgs/NavigateToActionResult"; };
    const char * getMD5(){ return "8b1c61040f1b5f7e7ce4bb6b2de470b0"; };

  };

}
#endif