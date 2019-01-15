#ifndef _ROS_stdr_msgs_RegisterRobotAction_h
#define _ROS_stdr_msgs_RegisterRobotAction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "stdr_msgs/RegisterRobotActionGoal.h"
#include "stdr_msgs/RegisterRobotActionResult.h"
#include "stdr_msgs/RegisterRobotActionFeedback.h"

namespace stdr_msgs
{

  class RegisterRobotAction : public ros::Msg
  {
    public:
      typedef stdr_msgs::RegisterRobotActionGoal _action_goal_type;
      _action_goal_type action_goal;
      typedef stdr_msgs::RegisterRobotActionResult _action_result_type;
      _action_result_type action_result;
      typedef stdr_msgs::RegisterRobotActionFeedback _action_feedback_type;
      _action_feedback_type action_feedback;

    RegisterRobotAction():
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

    const char * getType(){ return "stdr_msgs/RegisterRobotAction"; };
    const char * getMD5(){ return "b39b50bd76f14707645fb1a5dcce213f"; };

  };

}
#endif