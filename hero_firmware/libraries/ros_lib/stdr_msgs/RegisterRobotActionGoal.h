#ifndef _ROS_stdr_msgs_RegisterRobotActionGoal_h
#define _ROS_stdr_msgs_RegisterRobotActionGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalID.h"
#include "stdr_msgs/RegisterRobotGoal.h"

namespace stdr_msgs
{

  class RegisterRobotActionGoal : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef actionlib_msgs::GoalID _goal_id_type;
      _goal_id_type goal_id;
      typedef stdr_msgs::RegisterRobotGoal _goal_type;
      _goal_type goal;

    RegisterRobotActionGoal():
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

    const char * getType(){ return "stdr_msgs/RegisterRobotActionGoal"; };
    const char * getMD5(){ return "f8a902c408091c6ebd335b6782af1972"; };

  };

}
#endif