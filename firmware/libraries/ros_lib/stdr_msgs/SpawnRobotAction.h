#ifndef _ROS_stdr_msgs_SpawnRobotAction_h
#define _ROS_stdr_msgs_SpawnRobotAction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "stdr_msgs/SpawnRobotActionGoal.h"
#include "stdr_msgs/SpawnRobotActionResult.h"
#include "stdr_msgs/SpawnRobotActionFeedback.h"

namespace stdr_msgs
{

  class SpawnRobotAction : public ros::Msg
  {
    public:
      stdr_msgs::SpawnRobotActionGoal action_goal;
      stdr_msgs::SpawnRobotActionResult action_result;
      stdr_msgs::SpawnRobotActionFeedback action_feedback;

    SpawnRobotAction():
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

    const char * getType(){ return "stdr_msgs/SpawnRobotAction"; };
    const char * getMD5(){ return "697ea3eab380b9d78321ff3994dc302d"; };

  };

}
#endif