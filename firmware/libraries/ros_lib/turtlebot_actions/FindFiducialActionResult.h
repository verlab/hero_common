#ifndef _ROS_turtlebot_actions_FindFiducialActionResult_h
#define _ROS_turtlebot_actions_FindFiducialActionResult_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalStatus.h"
#include "turtlebot_actions/FindFiducialResult.h"

namespace turtlebot_actions
{

  class FindFiducialActionResult : public ros::Msg
  {
    public:
      std_msgs::Header header;
      actionlib_msgs::GoalStatus status;
      turtlebot_actions::FindFiducialResult result;

    FindFiducialActionResult():
      header(),
      status(),
      result()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->status.serialize(outbuffer + offset);
      offset += this->result.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->status.deserialize(inbuffer + offset);
      offset += this->result.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "turtlebot_actions/FindFiducialActionResult"; };
    const char * getMD5(){ return "6d0edd723ba2f2ae6bcfa76c98c311f7"; };

  };

}
#endif