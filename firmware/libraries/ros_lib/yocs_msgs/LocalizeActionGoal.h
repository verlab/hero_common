#ifndef _ROS_yocs_msgs_LocalizeActionGoal_h
#define _ROS_yocs_msgs_LocalizeActionGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalID.h"
#include "yocs_msgs/LocalizeGoal.h"

namespace yocs_msgs
{

  class LocalizeActionGoal : public ros::Msg
  {
    public:
      std_msgs::Header header;
      actionlib_msgs::GoalID goal_id;
      yocs_msgs::LocalizeGoal goal;

    LocalizeActionGoal():
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

    const char * getType(){ return "yocs_msgs/LocalizeActionGoal"; };
    const char * getMD5(){ return "c021f63ac13aafbf2154fcd41de29d1e"; };

  };

}
#endif