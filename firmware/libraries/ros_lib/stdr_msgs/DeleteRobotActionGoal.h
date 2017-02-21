#ifndef _ROS_stdr_msgs_DeleteRobotActionGoal_h
#define _ROS_stdr_msgs_DeleteRobotActionGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalID.h"
#include "stdr_msgs/DeleteRobotGoal.h"

namespace stdr_msgs
{

  class DeleteRobotActionGoal : public ros::Msg
  {
    public:
      std_msgs::Header header;
      actionlib_msgs::GoalID goal_id;
      stdr_msgs::DeleteRobotGoal goal;

    DeleteRobotActionGoal():
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

    const char * getType(){ return "stdr_msgs/DeleteRobotActionGoal"; };
    const char * getMD5(){ return "f8a902c408091c6ebd335b6782af1972"; };

  };

}
#endif