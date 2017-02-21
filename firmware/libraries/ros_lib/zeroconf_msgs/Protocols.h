#ifndef _ROS_zeroconf_msgs_Protocols_h
#define _ROS_zeroconf_msgs_Protocols_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace zeroconf_msgs
{

  class Protocols : public ros::Msg
  {
    public:
      enum { UNSPECIFIED =  0 };
      enum { IPV4 =  1 };
      enum { IPV6 =  2 };

    Protocols()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return "zeroconf_msgs/Protocols"; };
    const char * getMD5(){ return "6e173730dc50e42e6497a38ee52e9e4d"; };

  };

}
#endif