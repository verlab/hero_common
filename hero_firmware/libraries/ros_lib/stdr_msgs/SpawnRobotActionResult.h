#ifndef _ROS_stdr_msgs_SpawnRobotActionResult_h
#define _ROS_stdr_msgs_SpawnRobotActionResult_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalStatus.h"
#include "stdr_msgs/SpawnRobotResult.h"

namespace stdr_msgs
{

  class SpawnRobotActionResult : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef actionlib_msgs::GoalStatus _status_type;
      _status_type status;
      typedef stdr_msgs::SpawnRobotResult _result_type;
      _result_type result;

    SpawnRobotActionResult():
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

    const char * getType(){ return "stdr_msgs/SpawnRobotActionResult"; };
    const char * getMD5(){ return "f95a810c7b5f2579dca2ec191de2a05c"; };

  };

}
#endif