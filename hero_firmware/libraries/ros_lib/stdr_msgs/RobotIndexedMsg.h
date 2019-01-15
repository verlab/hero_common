#ifndef _ROS_stdr_msgs_RobotIndexedMsg_h
#define _ROS_stdr_msgs_RobotIndexedMsg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "stdr_msgs/RobotMsg.h"

namespace stdr_msgs
{

  class RobotIndexedMsg : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;
      typedef stdr_msgs::RobotMsg _robot_type;
      _robot_type robot;

    RobotIndexedMsg():
      name(""),
      robot()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      offset += this->robot.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
      offset += this->robot.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "stdr_msgs/RobotIndexedMsg"; };
    const char * getMD5(){ return "f74cd2b918be4e39c8fb0e1bebbbf480"; };

  };

}
#endif