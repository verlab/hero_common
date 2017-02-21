#ifndef _ROS_swarm_driver_Command_h
#define _ROS_swarm_driver_Command_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace swarm_driver
{

  class Command : public ros::Msg
  {
    public:
      uint8_t robot_id;
      uint8_t wheel_right;
      uint8_t wheel_left;

    Command():
      robot_id(0),
      wheel_right(0),
      wheel_left(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->robot_id >> (8 * 0)) & 0xFF;
      offset += sizeof(this->robot_id);
      *(outbuffer + offset + 0) = (this->wheel_right >> (8 * 0)) & 0xFF;
      offset += sizeof(this->wheel_right);
      *(outbuffer + offset + 0) = (this->wheel_left >> (8 * 0)) & 0xFF;
      offset += sizeof(this->wheel_left);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->robot_id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->robot_id);
      this->wheel_right =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->wheel_right);
      this->wheel_left =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->wheel_left);
     return offset;
    }

    const char * getType(){ return "swarm_driver/Command"; };
    const char * getMD5(){ return "9b5f0d2673ef536e966e7b091fe3f66e"; };

  };

}
#endif