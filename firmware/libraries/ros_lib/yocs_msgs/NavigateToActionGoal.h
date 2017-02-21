#ifndef _ROS_yocs_msgs_NavigateToActionGoal_h
#define _ROS_yocs_msgs_NavigateToActionGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalID.h"
#include "yocs_msgs/NavigateToGoal.h"

namespace yocs_msgs
{

  class NavigateToActionGoal : public ros::Msg
  {
    public:
      std_msgs::Header header;
      actionlib_msgs::GoalID goal_id;
      yocs_msgs::NavigateToGoal goal;

    NavigateToActionGoal():
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

    const char * getType(){ return "yocs_msgs/NavigateToActionGoal"; };
    const char * getMD5(){ return "ffa50cda52f07e2549da7c2006eeb671"; };

  };

}
#endif