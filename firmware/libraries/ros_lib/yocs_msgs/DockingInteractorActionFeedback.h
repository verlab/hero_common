#ifndef _ROS_yocs_msgs_DockingInteractorActionFeedback_h
#define _ROS_yocs_msgs_DockingInteractorActionFeedback_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalStatus.h"
#include "yocs_msgs/DockingInteractorFeedback.h"

namespace yocs_msgs
{

  class DockingInteractorActionFeedback : public ros::Msg
  {
    public:
      std_msgs::Header header;
      actionlib_msgs::GoalStatus status;
      yocs_msgs::DockingInteractorFeedback feedback;

    DockingInteractorActionFeedback():
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

    const char * getType(){ return "yocs_msgs/DockingInteractorActionFeedback"; };
    const char * getMD5(){ return "47319e8d1c9c76c26f34236b20a39a9a"; };

  };

}
#endif