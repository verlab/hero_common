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
      typedef uint8_t _robot_id_type;
      _robot_id_type robot_id;
      typedef int8_t _wheel_right_type;
      _wheel_right_type wheel_right;
      typedef int8_t _wheel_left_type;
      _wheel_left_type wheel_left;

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
      union {
        int8_t real;
        uint8_t base;
      } u_wheel_right;
      u_wheel_right.real = this->wheel_right;
      *(outbuffer + offset + 0) = (u_wheel_right.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->wheel_right);
      union {
        int8_t real;
        uint8_t base;
      } u_wheel_left;
      u_wheel_left.real = this->wheel_left;
      *(outbuffer + offset + 0) = (u_wheel_left.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->wheel_left);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->robot_id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->robot_id);
      union {
        int8_t real;
        uint8_t base;
      } u_wheel_right;
      u_wheel_right.base = 0;
      u_wheel_right.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->wheel_right = u_wheel_right.real;
      offset += sizeof(this->wheel_right);
      union {
        int8_t real;
        uint8_t base;
      } u_wheel_left;
      u_wheel_left.base = 0;
      u_wheel_left.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->wheel_left = u_wheel_left.real;
      offset += sizeof(this->wheel_left);
     return offset;
    }

    const char * getType(){ return "swarm_driver/Command"; };
    const char * getMD5(){ return "d76b8052249a64fe0c4d7bda68ee48ae"; };

  };

}
#endif