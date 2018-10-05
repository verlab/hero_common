#ifndef _ROS_stdr_msgs_SpawnRobotResult_h
#define _ROS_stdr_msgs_SpawnRobotResult_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "stdr_msgs/RobotIndexedMsg.h"

namespace stdr_msgs
{

  class SpawnRobotResult : public ros::Msg
  {
    public:
      typedef stdr_msgs::RobotIndexedMsg _indexedDescription_type;
      _indexedDescription_type indexedDescription;
      typedef const char* _message_type;
      _message_type message;

    SpawnRobotResult():
      indexedDescription(),
      message("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->indexedDescription.serialize(outbuffer + offset);
      uint32_t length_message = strlen(this->message);
      varToArr(outbuffer + offset, length_message);
      offset += 4;
      memcpy(outbuffer + offset, this->message, length_message);
      offset += length_message;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->indexedDescription.deserialize(inbuffer + offset);
      uint32_t length_message;
      arrToVar(length_message, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_message-1]=0;
      this->message = (char *)(inbuffer + offset-1);
      offset += length_message;
     return offset;
    }

    const char * getType(){ return "stdr_msgs/SpawnRobotResult"; };
    const char * getMD5(){ return "8217dc1798cb6a09c560cd62f710182e"; };

  };

}
#endif