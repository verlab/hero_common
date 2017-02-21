#ifndef _ROS_yocs_msgs_LocalizeActionFeedback_h
#define _ROS_yocs_msgs_LocalizeActionFeedback_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalStatus.h"
#include "yocs_msgs/LocalizeFeedback.h"

namespace yocs_msgs
{

  class LocalizeActionFeedback : public ros::Msg
  {
    public:
      std_msgs::Header header;
      actionlib_msgs::GoalStatus status;
      yocs_msgs::LocalizeFeedback feedback;

    LocalizeActionFeedback():
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

    const char * getType(){ return "yocs_msgs/LocalizeActionFeedback"; };
    const char * getMD5(){ return "c174906940145c775f10875f0919664b"; };

  };

}
#endif