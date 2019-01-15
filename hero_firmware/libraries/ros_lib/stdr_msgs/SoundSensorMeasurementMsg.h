#ifndef _ROS_stdr_msgs_SoundSensorMeasurementMsg_h
#define _ROS_stdr_msgs_SoundSensorMeasurementMsg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace stdr_msgs
{

  class SoundSensorMeasurementMsg : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef float _sound_dbs_type;
      _sound_dbs_type sound_dbs;

    SoundSensorMeasurementMsg():
      header(),
      sound_dbs(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_sound_dbs;
      u_sound_dbs.real = this->sound_dbs;
      *(outbuffer + offset + 0) = (u_sound_dbs.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_sound_dbs.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_sound_dbs.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_sound_dbs.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->sound_dbs);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_sound_dbs;
      u_sound_dbs.base = 0;
      u_sound_dbs.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_sound_dbs.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_sound_dbs.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_sound_dbs.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->sound_dbs = u_sound_dbs.real;
      offset += sizeof(this->sound_dbs);
     return offset;
    }

    const char * getType(){ return "stdr_msgs/SoundSensorMeasurementMsg"; };
    const char * getMD5(){ return "1f73a234937f6d19824ea2a78f157d78"; };

  };

}
#endif