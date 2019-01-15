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
      uint32_t robots_length;
      typedef stdr_msgs::RobotIndexedMsg _robots_type;
      _robots_type st_robots;
      _robots_type * robots;

    RobotIndexedVectorMsg():
      robots_length(0), robots(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->robots_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->robots_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->robots_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->robots_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->robots_length);
      for( uint32_t i = 0; i < robots_length; i++){
      offset += this->robots[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t robots_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      robots_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      robots_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      robots_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->robots_length);
      if(robots_lengthT > robots_length)
        this->robots = (stdr_msgs::RobotIndexedMsg*)realloc(this->robots, robots_lengthT * sizeof(stdr_msgs::RobotIndexedMsg));
      robots_length = robots_lengthT;
      for( uint32_t i = 0; i < robots_length; i++){
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