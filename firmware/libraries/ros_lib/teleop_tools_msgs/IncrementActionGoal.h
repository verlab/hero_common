#ifndef _ROS_teleop_tools_msgs_IncrementActionGoal_h
#define _ROS_teleop_tools_msgs_IncrementActionGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalID.h"
#include "teleop_tools_msgs/IncrementGoal.h"

namespace teleop_tools_msgs
{

  class IncrementActionGoal : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef actionlib_msgs::GoalID _goal_id_type;
      _goal_id_type goal_id;
      typedef teleop_tools_msgs::IncrementGoal _goal_type;
      _goal_type goal;

    IncrementActionGoal():
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

    const char * getType(){ return "teleop_tools_msgs/IncrementActionGoal"; };
    const char * getMD5(){ return "fd0f65b046bd08324be539043a8c21f7"; };

  };

}
#endif