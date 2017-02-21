#ifndef _ROS_yocs_msgs_DockingInteractorActionGoal_h
#define _ROS_yocs_msgs_DockingInteractorActionGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalID.h"
#include "yocs_msgs/DockingInteractorGoal.h"

namespace yocs_msgs
{

  class DockingInteractorActionGoal : public ros::Msg
  {
    public:
      std_msgs::Header header;
      actionlib_msgs::GoalID goal_id;
      yocs_msgs::DockingInteractorGoal goal;

    DockingInteractorActionGoal():
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

    const char * getType(){ return "yocs_msgs/DockingInteractorActionGoal"; };
    const char * getMD5(){ return "c5820befe28db119fe6fe4a6c9e700c9"; };

  };

}
#endif