#ifndef _ROS_SERVICE_MoveRobot_h
#define _ROS_SERVICE_MoveRobot_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose2D.h"

namespace stdr_msgs
{

static const char MOVEROBOT[] = "stdr_msgs/MoveRobot";

  class MoveRobotRequest : public ros::Msg
  {
    public:
      typedef geometry_msgs::Pose2D _newPose_type;
      _newPose_type newPose;

    MoveRobotRequest():
      newPose()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->newPose.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->newPose.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return MOVEROBOT; };
    const char * getMD5(){ return "3f8cb1536a8bfe7e956ece9331b2cd07"; };

  };

  class MoveRobotResponse : public ros::Msg
  {
    public:

    MoveRobotResponse()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return MOVEROBOT; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class MoveRobot {
    public:
    typedef MoveRobotRequest Request;
    typedef MoveRobotResponse Response;
  };

}
#endif
