#ifndef _ROS_teleop_tools_msgs_IncrementAction_h
#define _ROS_teleop_tools_msgs_IncrementAction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "teleop_tools_msgs/IncrementActionGoal.h"
#include "teleop_tools_msgs/IncrementActionResult.h"
#include "teleop_tools_msgs/IncrementActionFeedback.h"

namespace teleop_tools_msgs
{

  class IncrementAction : public ros::Msg
  {
    public:
      teleop_tools_msgs::IncrementActionGoal action_goal;
      teleop_tools_msgs::IncrementActionResult action_result;
      teleop_tools_msgs::IncrementActionFeedback action_feedback;

    IncrementAction():
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

    const char * getType(){ return "teleop_tools_msgs/IncrementAction"; };
    const char * getMD5(){ return "797aeed74214fd3316231275503262ab"; };

  };

}
#endif