#ifndef _ROS_mav_msgs_Thrust_h
#define _ROS_mav_msgs_Thrust_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mav_msgs
{

  class Thrust : public ros::Msg
  {
    public:
      typedef float _thrust_type;
      _thrust_type thrust;

    Thrust():
      thrust(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->thrust);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->thrust));
     return offset;
    }

    const char * getType(){ return "mav_msgs/Thrust"; };
    const char * getMD5(){ return "0decd0228ce387bc8806e2d54bac566a"; };

  };

}
#endif