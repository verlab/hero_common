#ifndef _ROS_yocs_msgs_NavigationControlStatus_h
#define _ROS_yocs_msgs_NavigationControlStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace yocs_msgs
{

  class NavigationControlStatus : public ros::Msg
  {
    public:
      int8_t status;
      const char* status_desc;
      enum { ERROR =  -1 };
      enum { IDLING =  0 };
      enum { RUNNING =  1 };
      enum { PAUSED =  2 };
      enum { COMPLETED =  3 };
      enum { CANCELLED =  4 };

    NavigationControlStatus():
      status(0),
      status_desc("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_status;
      u_status.real = this->status;
      *(outbuffer + offset + 0) = (u_status.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->status);
      uint32_t length_status_desc = strlen(this->status_desc);
      memcpy(outbuffer + offset, &length_status_desc, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->status_desc, length_status_desc);
      offset += length_status_desc;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_status;
      u_status.base = 0;
      u_status.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->status = u_status.real;
      offset += sizeof(this->status);
      uint32_t length_status_desc;
      memcpy(&length_status_desc, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_status_desc; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_status_desc-1]=0;
      this->status_desc = (char *)(inbuffer + offset-1);
      offset += length_status_desc;
     return offset;
    }

    const char * getType(){ return "yocs_msgs/NavigationControlStatus"; };
    const char * getMD5(){ return "f97c2c5903b273dd04cfb815fadb9f56"; };

  };

}
#endif