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
      typedef teleop_tools_msgs::IncrementActionGoal _action_goal_type;
      _action_goal_type action_goal;
      typedef teleop_tools_msgs::IncrementActionResult _action_result_type;
      _action_result_type action_result;
      typedef teleop_tools_msgs::IncrementActionFeedback _action_feedback_type;
      _action_feedback_type action_feedback;

    IncrementAction():
      action_goal(),
      action_result(),
      action_feedback()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->action_goal.serialize(outbuffer + offset);
      offset += this->action_result.serialize(outbuffer + offset);
      offset += this->action_feedback.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->action_goal.deserialize(inbuffer + offset);
      offset += this->action_result.deserialize(inbuffer + offset);
      offset += this->action_feedback.deserialize(inbuffer + offset);
     return offset;
    }

    virtual const char * getType() override { return "teleop_tools_msgs/IncrementAction"; };
    virtual const char * getMD5() override { return "797aeed74214fd3316231275503262ab"; };

  };

}
#endif
