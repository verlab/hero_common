#ifndef _ROS_yocs_msgs_NavigateToAction_h
#define _ROS_yocs_msgs_NavigateToAction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "yocs_msgs/NavigateToActionGoal.h"
#include "yocs_msgs/NavigateToActionResult.h"
#include "yocs_msgs/NavigateToActionFeedback.h"

namespace yocs_msgs
{

  class NavigateToAction : public ros::Msg
  {
    public:
      yocs_msgs::NavigateToActionGoal action_goal;
      yocs_msgs::NavigateToActionResult action_result;
      yocs_msgs::NavigateToActionFeedback action_feedback;

    NavigateToAction():
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

    const char * getType(){ return "yocs_msgs/NavigateToAction"; };
    const char * getMD5(){ return "74483e4684b0588107a129113d0f5a01"; };

  };

}
#endif