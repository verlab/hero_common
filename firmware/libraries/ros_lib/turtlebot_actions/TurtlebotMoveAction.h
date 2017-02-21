#ifndef _ROS_turtlebot_actions_TurtlebotMoveAction_h
#define _ROS_turtlebot_actions_TurtlebotMoveAction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "turtlebot_actions/TurtlebotMoveActionGoal.h"
#include "turtlebot_actions/TurtlebotMoveActionResult.h"
#include "turtlebot_actions/TurtlebotMoveActionFeedback.h"

namespace turtlebot_actions
{

  class TurtlebotMoveAction : public ros::Msg
  {
    public:
      turtlebot_actions::TurtlebotMoveActionGoal action_goal;
      turtlebot_actions::TurtlebotMoveActionResult action_result;
      turtlebot_actions::TurtlebotMoveActionFeedback action_feedback;

    TurtlebotMoveAction():
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

    const char * getType(){ return "turtlebot_actions/TurtlebotMoveAction"; };
    const char * getMD5(){ return "339929f411dcfd188670046028b412ee"; };

  };

}
#endif