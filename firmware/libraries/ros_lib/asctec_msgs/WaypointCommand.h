#ifndef _ROS_asctec_msgs_WaypointCommand_h
#define _ROS_asctec_msgs_WaypointCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace asctec_msgs
{

  class WaypointCommand : public ros::Msg
  {
    public:
      std_msgs::Header header;
      const char* cmd;

    WaypointCommand():
      header(),
      cmd("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      uint32_t length_cmd = strlen(this->cmd);
      memcpy(outbuffer + offset, &length_cmd, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->cmd, length_cmd);
      offset += length_cmd;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t length_cmd;
      memcpy(&length_cmd, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_cmd; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_cmd-1]=0;
      this->cmd = (char *)(inbuffer + offset-1);
      offset += length_cmd;
     return offset;
    }

    const char * getType(){ return "asctec_msgs/WaypointCommand"; };
    const char * getMD5(){ return "4276af4fed90fb499f3ed97a1942bbe3"; };

  };

}
#endif