#ifndef _ROS_stdr_msgs_DeleteRobotAction_h
#define _ROS_stdr_msgs_DeleteRobotAction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "stdr_msgs/DeleteRobotActionGoal.h"
#include "stdr_msgs/DeleteRobotActionResult.h"
#include "stdr_msgs/DeleteRobotActionFeedback.h"

namespace stdr_msgs
{

  class DeleteRobotAction : public ros::Msg
  {
    public:
      typedef stdr_msgs::DeleteRobotActionGoal _action_goal_type;
      _action_goal_type action_goal;
      typedef stdr_msgs::DeleteRobotActionResult _action_result_type;
      _action_result_type action_result;
      typedef stdr_msgs::DeleteRobotActionFeedback _action_feedback_type;
      _action_feedback_type action_feedback;

    DeleteRobotAction():
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

    const char * getType(){ return "stdr_msgs/DeleteRobotAction"; };
    const char * getMD5(){ return "380d84e297a0fec2ae31cb6218729730"; };

  };

}
#endif