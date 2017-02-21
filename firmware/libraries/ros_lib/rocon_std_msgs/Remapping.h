#ifndef _ROS_rocon_std_msgs_Remapping_h
#define _ROS_rocon_std_msgs_Remapping_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rocon_std_msgs
{

  class Remapping : public ros::Msg
  {
    public:
      const char* remap_from;
      const char* remap_to;

    Remapping():
      remap_from(""),
      remap_to("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_remap_from = strlen(this->remap_from);
      memcpy(outbuffer + offset, &length_remap_from, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->remap_from, length_remap_from);
      offset += length_remap_from;
      uint32_t length_remap_to = strlen(this->remap_to);
      memcpy(outbuffer + offset, &length_remap_to, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->remap_to, length_remap_to);
      offset += length_remap_to;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_remap_from;
      memcpy(&length_remap_from, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_remap_from; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_remap_from-1]=0;
      this->remap_from = (char *)(inbuffer + offset-1);
      offset += length_remap_from;
      uint32_t length_remap_to;
      memcpy(&length_remap_to, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_remap_to; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_remap_to-1]=0;
      this->remap_to = (char *)(inbuffer + offset-1);
      offset += length_remap_to;
     return offset;
    }

    const char * getType(){ return "rocon_std_msgs/Remapping"; };
    const char * getMD5(){ return "26f16c667d483280bc5d040bf2c0cd8d"; };

  };

}
#endif