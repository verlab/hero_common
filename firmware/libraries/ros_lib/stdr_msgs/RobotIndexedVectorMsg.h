#ifndef _ROS_stdr_msgs_RobotIndexedVectorMsg_h
#define _ROS_stdr_msgs_RobotIndexedVectorMsg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "stdr_msgs/RobotIndexedMsg.h"

namespace stdr_msgs
{

  class RobotIndexedVectorMsg : public ros::Msg
  {
    public:
      uint8_t robots_length;
      stdr_msgs::RobotIndexedMsg st_robots;
      stdr_msgs::RobotIndexedMsg * robots;

    RobotIndexedVectorMsg():
      robots_length(0), robots(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = robots_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < robots_length; i++){
      offset += this->robots[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t robots_lengthT = *(inbuffer + offset++);
      if(robots_lengthT > robots_length)
        this->robots = (stdr_msgs::RobotIndexedMsg*)realloc(this->robots, robots_lengthT * sizeof(stdr_msgs::RobotIndexedMsg));
      offset += 3;
      robots_length = robots_lengthT;
      for( uint8_t i = 0; i < robots_length; i++){
      offset += this->st_robots.deserialize(inbuffer + offset);
        memcpy( &(this->robots[i]), &(this->st_robots), sizeof(stdr_msgs::RobotIndexedMsg));
      }
     return offset;
    }

    const char * getType(){ return "stdr_msgs/RobotIndexedVectorMsg"; };
    const char * getMD5(){ return "5ba49d43b5f1ad43f9cbea11348366c5"; };

  };

}
#endif