#ifndef _ROS_turtlebot_actions_TurtlebotMoveGoal_h
#define _ROS_turtlebot_actions_TurtlebotMoveGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace turtlebot_actions
{

  class TurtlebotMoveGoal : public ros::Msg
  {
    public:
      float turn_distance;
      float forward_distance;

    TurtlebotMoveGoal():
      turn_distance(0),
      forward_distance(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_turn_distance;
      u_turn_distance.real = this->turn_distance;
      *(outbuffer + offset + 0) = (u_turn_distance.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_turn_distance.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_turn_distance.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_turn_distance.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->turn_distance);
      union {
        float real;
        uint32_t base;
      } u_forward_distance;
      u_forward_distance.real = this->forward_distance;
      *(outbuffer + offset + 0) = (u_forward_distance.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_forward_distance.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_forward_distance.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_forward_distance.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->forward_distance);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_turn_distance;
      u_turn_distance.base = 0;
      u_turn_distance.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_turn_distance.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_turn_distance.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_turn_distance.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->turn_distance = u_turn_distance.real;
      offset += sizeof(this->turn_distance);
      union {
        float real;
        uint32_t base;
      } u_forward_distance;
      u_forward_distance.base = 0;
      u_forward_distance.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_forward_distance.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_forward_distance.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_forward_distance.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->forward_distance = u_forward_distance.real;
      offset += sizeof(this->forward_distance);
     return offset;
    }

    const char * getType(){ return "turtlebot_actions/TurtlebotMoveGoal"; };
    const char * getMD5(){ return "c971f114b08a2a1ad79af4c9ca9f358c"; };

  };

}
#endif