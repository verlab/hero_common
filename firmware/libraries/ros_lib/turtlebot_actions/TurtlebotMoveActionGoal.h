#ifndef _ROS_turtlebot_actions_TurtlebotMoveActionGoal_h
#define _ROS_turtlebot_actions_TurtlebotMoveActionGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalID.h"
#include "turtlebot_actions/TurtlebotMoveGoal.h"

namespace turtlebot_actions
{

  class TurtlebotMoveActionGoal : public ros::Msg
  {
    public:
      std_msgs::Header header;
      actionlib_msgs::GoalID goal_id;
      turtlebot_actions::TurtlebotMoveGoal goal;

    TurtlebotMoveActionGoal():
      header(),
      goal_id(),
      goal()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->goal_id.serialize(outbuffer + offset);
      offset += this->goal.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->goal_id.deserialize(inbuffer + offset);
      offset += this->goal.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "turtlebot_actions/TurtlebotMoveActionGoal"; };
    const char * getMD5(){ return "7e462cf7fe57fc76afd36fde5d415bc1"; };

  };

}
#endif