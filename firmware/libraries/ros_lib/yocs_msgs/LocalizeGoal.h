#ifndef _ROS_yocs_msgs_LocalizeGoal_h
#define _ROS_yocs_msgs_LocalizeGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace yocs_msgs
{

  class LocalizeGoal : public ros::Msg
  {
    public:
      int8_t command;
      float distortion;
      enum { STAND_AND_LOCALIZE = 10 };
      enum { SPIN_AND_LOCALIZE = 20 };

    LocalizeGoal():
      command(0),
      distortion(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_command;
      u_command.real = this->command;
      *(outbuffer + offset + 0) = (u_command.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->command);
      union {
        float real;
        uint32_t base;
      } u_distortion;
      u_distortion.real = this->distortion;
      *(outbuffer + offset + 0) = (u_distortion.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_distortion.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_distortion.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_distortion.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->distortion);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_command;
      u_command.base = 0;
      u_command.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->command = u_command.real;
      offset += sizeof(this->command);
      union {
        float real;
        uint32_t base;
      } u_distortion;
      u_distortion.base = 0;
      u_distortion.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_distortion.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_distortion.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_distortion.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->distortion = u_distortion.real;
      offset += sizeof(this->distortion);
     return offset;
    }

    const char * getType(){ return "yocs_msgs/LocalizeGoal"; };
    const char * getMD5(){ return "6383995712d8736902464bbea6b0fb6d"; };

  };

}
#endif