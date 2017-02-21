#ifndef _ROS_yocs_msgs_LocalizeAction_h
#define _ROS_yocs_msgs_LocalizeAction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "yocs_msgs/LocalizeActionGoal.h"
#include "yocs_msgs/LocalizeActionResult.h"
#include "yocs_msgs/LocalizeActionFeedback.h"

namespace yocs_msgs
{

  class LocalizeAction : public ros::Msg
  {
    public:
      yocs_msgs::LocalizeActionGoal action_goal;
      yocs_msgs::LocalizeActionResult action_result;
      yocs_msgs::LocalizeActionFeedback action_feedback;

    LocalizeAction():
      action_goal(),
      action_result(),
      action_feedback()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->action_goal.serialize(outbuffer + offset);
      offset += this->action_result.serialize(outbuffer + offset);
      offset += this->action_feedback.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->action_goal.deserialize(inbuffer + offset);
      offset += this->action_result.deserialize(inbuffer + offset);
      offset += this->action_feedback.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "yocs_msgs/LocalizeAction"; };
    const char * getMD5(){ return "fd676593c44fcb6e96ae1a023d9f596d"; };

  };

}
#endif