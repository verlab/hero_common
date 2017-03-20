#ifndef _ROS_kobuki_msgs_AutoDockingAction_h
#define _ROS_kobuki_msgs_AutoDockingAction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "kobuki_msgs/AutoDockingActionGoal.h"
#include "kobuki_msgs/AutoDockingActionResult.h"
#include "kobuki_msgs/AutoDockingActionFeedback.h"

namespace kobuki_msgs
{

  class AutoDockingAction : public ros::Msg
  {
    public:
      typedef kobuki_msgs::AutoDockingActionGoal _action_goal_type;
      _action_goal_type action_goal;
      typedef kobuki_msgs::AutoDockingActionResult _action_result_type;
      _action_result_type action_result;
      typedef kobuki_msgs::AutoDockingActionFeedback _action_feedback_type;
      _action_feedback_type action_feedback;

    AutoDockingAction():
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

    const char * getType(){ return "kobuki_msgs/AutoDockingAction"; };
    const char * getMD5(){ return "44be114f3afc06365a090db0a5e982b5"; };

  };

}
#endif