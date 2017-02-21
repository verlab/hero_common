#ifndef _ROS_yocs_msgs_NavigationControl_h
#define _ROS_yocs_msgs_NavigationControl_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace yocs_msgs
{

  class NavigationControl : public ros::Msg
  {
    public:
      int8_t control;
      const char* goal_name;
      enum { STOP =  0 };
      enum { START =  1 };
      enum { PAUSE =  2 };

    NavigationControl():
      control(0),
      goal_name("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_control;
      u_control.real = this->control;
      *(outbuffer + offset + 0) = (u_control.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->control);
      uint32_t length_goal_name = strlen(this->goal_name);
      memcpy(outbuffer + offset, &length_goal_name, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->goal_name, length_goal_name);
      offset += length_goal_name;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_control;
      u_control.base = 0;
      u_control.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->control = u_control.real;
      offset += sizeof(this->control);
      uint32_t length_goal_name;
      memcpy(&length_goal_name, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_goal_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_goal_name-1]=0;
      this->goal_name = (char *)(inbuffer + offset-1);
      offset += length_goal_name;
     return offset;
    }

    const char * getType(){ return "yocs_msgs/NavigationControl"; };
    const char * getMD5(){ return "f2ddf02b376d1d00aed5addfb5cfe0ba"; };

  };

}
#endif