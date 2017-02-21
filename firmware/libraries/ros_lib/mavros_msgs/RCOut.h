#ifndef _ROS_mavros_msgs_RCOut_h
#define _ROS_mavros_msgs_RCOut_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace mavros_msgs
{

  class RCOut : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t channels_length;
      uint16_t st_channels;
      uint16_t * channels;

    RCOut():
      header(),
      channels_length(0), channels(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = channels_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < channels_length; i++){
      *(outbuffer + offset + 0) = (this->channels[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->channels[i] >> (8 * 1)) & 0xFF;
      offset += sizeof(this->channels[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t channels_lengthT = *(inbuffer + offset++);
      if(channels_lengthT > channels_length)
        this->channels = (uint16_t*)realloc(this->channels, channels_lengthT * sizeof(uint16_t));
      offset += 3;
      channels_length = channels_lengthT;
      for( uint8_t i = 0; i < channels_length; i++){
      this->st_channels =  ((uint16_t) (*(inbuffer + offset)));
      this->st_channels |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->st_channels);
        memcpy( &(this->channels[i]), &(this->st_channels), sizeof(uint16_t));
      }
     return offset;
    }

    const char * getType(){ return "mavros_msgs/RCOut"; };
    const char * getMD5(){ return "52cacf104bab5ae3b103cfe176590713"; };

  };

}
#endif