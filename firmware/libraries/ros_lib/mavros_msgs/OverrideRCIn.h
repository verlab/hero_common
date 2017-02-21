#ifndef _ROS_mavros_msgs_OverrideRCIn_h
#define _ROS_mavros_msgs_OverrideRCIn_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mavros_msgs
{

  class OverrideRCIn : public ros::Msg
  {
    public:
      uint16_t channels[8];
      enum { CHAN_RELEASE = 0 };
      enum { CHAN_NOCHANGE = 65535 };

    OverrideRCIn():
      channels()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint8_t i = 0; i < 8; i++){
      *(outbuffer + offset + 0) = (this->channels[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->channels[i] >> (8 * 1)) & 0xFF;
      offset += sizeof(this->channels[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint8_t i = 0; i < 8; i++){
      this->channels[i] =  ((uint16_t) (*(inbuffer + offset)));
      this->channels[i] |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->channels[i]);
      }
     return offset;
    }

    const char * getType(){ return "mavros_msgs/OverrideRCIn"; };
    const char * getMD5(){ return "73b27a463a40a3eda1f9fbb1fc86d6f3"; };

  };

}
#endif