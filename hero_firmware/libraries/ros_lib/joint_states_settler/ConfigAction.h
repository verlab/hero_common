#ifndef _ROS_joint_states_settler_ConfigAction_h
#define _ROS_joint_states_settler_ConfigAction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "joint_states_settler/ConfigActionGoal.h"
#include "joint_states_settler/ConfigActionResult.h"
#include "joint_states_settler/ConfigActionFeedback.h"

namespace joint_states_settler
{

  class ConfigAction : public ros::Msg
  {
    public:
      typedef joint_states_settler::ConfigActionGoal _action_goal_type;
      _action_goal_type action_goal;
      typedef joint_states_settler::ConfigActionResult _action_result_type;
      _action_result_type action_result;
      typedef joint_states_settler::ConfigActionFeedback _action_feedback_type;
      _action_feedback_type action_feedback;

    ConfigAction():
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

    virtual const char * getType() override { return "joint_states_settler/ConfigAction"; };
    virtual const char * getMD5() override { return "baa9ae56369a6c832695f8fd10a504f5"; };

  };

}
#endif
