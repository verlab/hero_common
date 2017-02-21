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
      stdr_msgs::DeleteRobotActionGoal action_goal;
      stdr_msgs::DeleteRobotActionResult action_result;
      stdr_msgs::DeleteRobotActionFeedback action_feedback;

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