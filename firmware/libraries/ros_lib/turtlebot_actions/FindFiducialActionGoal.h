#ifndef _ROS_turtlebot_actions_FindFiducialActionGoal_h
#define _ROS_turtlebot_actions_FindFiducialActionGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalID.h"
#include "turtlebot_actions/FindFiducialGoal.h"

namespace turtlebot_actions
{

  class FindFiducialActionGoal : public ros::Msg
  {
    public:
      std_msgs::Header header;
      actionlib_msgs::GoalID goal_id;
      turtlebot_actions::FindFiducialGoal goal;

    FindFiducialActionGoal():
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

    const char * getType(){ return "turtlebot_actions/FindFiducialActionGoal"; };
    const char * getMD5(){ return "c6a34d64b9eb5980711e7f6f5b5b4380"; };

  };

}
#endif