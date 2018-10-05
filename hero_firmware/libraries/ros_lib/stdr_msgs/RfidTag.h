#ifndef _ROS_stdr_msgs_RfidTag_h
#define _ROS_stdr_msgs_RfidTag_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose2D.h"

namespace stdr_msgs
{

  class RfidTag : public ros::Msg
  {
    public:
      typedef const char* _tag_id_type;
      _tag_id_type tag_id;
      typedef const char* _message_type;
      _message_type message;
      typedef geometry_msgs::Pose2D _pose_type;
      _pose_type pose;

    RfidTag():
      tag_id(""),
      message(""),
      pose()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_tag_id = strlen(this->tag_id);
      varToArr(outbuffer + offset, length_tag_id);
      offset += 4;
      memcpy(outbuffer + offset, this->tag_id, length_tag_id);
      offset += length_tag_id;
      uint32_t length_message = strlen(this->message);
      varToArr(outbuffer + offset, length_message);
      offset += 4;
      memcpy(outbuffer + offset, this->message, length_message);
      offset += length_message;
      offset += this->pose.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_tag_id;
      arrToVar(length_tag_id, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_tag_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_tag_id-1]=0;
      this->tag_id = (char *)(inbuffer + offset-1);
      offset += length_tag_id;
      uint32_t length_message;
      arrToVar(length_message, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_message-1]=0;
      this->message = (char *)(inbuffer + offset-1);
      offset += length_message;
      offset += this->pose.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "stdr_msgs/RfidTag"; };
    const char * getMD5(){ return "e37433c890cfe140ccbef22419fae16c"; };

  };

}
#endif