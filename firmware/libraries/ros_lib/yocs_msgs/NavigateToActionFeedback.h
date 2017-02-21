#ifndef _ROS_yocs_msgs_NavigateToActionFeedback_h
#define _ROS_yocs_msgs_NavigateToActionFeedback_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalStatus.h"
#include "yocs_msgs/NavigateToFeedback.h"

namespace yocs_msgs
{

  class NavigateToActionFeedback : public ros::Msg
  {
    public:
      std_msgs::Header header;
      actionlib_msgs::GoalStatus status;
      yocs_msgs::NavigateToFeedback feedback;

    NavigateToActionFeedback():
      header(),
      status(),
      feedback()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->status.serialize(outbuffer + offset);
      offset += this->feedback.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->status.deserialize(inbuffer + offset);
      offset += this->feedback.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "yocs_msgs/NavigateToActionFeedback"; };
    const char * getMD5(){ return "7d846f575816c69a71f167110b82fcca"; };

  };

}
#endif