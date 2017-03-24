#ifndef _ROS_swarm_driver_Sensors_h
#define _ROS_swarm_driver_Sensors_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace swarm_driver
{

  class Sensors : public ros::Msg
  {
    public:
      typedef uint8_t _robot_id_type;
      _robot_id_type robot_id;
      typedef int8_t _data_type;
      _data_type data;

    Sensors():
      robot_id(0),
      data(0)
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
      } u_data;
      u_data.real = this->data;
      *(outbuffer + offset + 0) = (u_data.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->data);
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
      } u_data;
      u_data.base = 0;
      u_data.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->data = u_data.real;
      offset += sizeof(this->data);
     return offset;
    }

    const char * getType(){ return "swarm_driver/Sensors"; };
    const char * getMD5(){ return "ef65d686c085b3e29a1d0cc549f68c0f"; };

  };

}
#endif