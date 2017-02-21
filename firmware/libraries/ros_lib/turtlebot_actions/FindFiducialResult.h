#ifndef _ROS_turtlebot_actions_FindFiducialResult_h
#define _ROS_turtlebot_actions_FindFiducialResult_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/PoseStamped.h"

namespace turtlebot_actions
{

  class FindFiducialResult : public ros::Msg
  {
    public:
      geometry_msgs::PoseStamped pose;

    FindFiducialResult():
      pose()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->pose.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->pose.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "turtlebot_actions/FindFiducialResult"; };
    const char * getMD5(){ return "3f8930d968a3e84d471dff917bb1cdae"; };

  };

}
#endif