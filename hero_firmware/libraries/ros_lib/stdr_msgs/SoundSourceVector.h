#ifndef _ROS_stdr_msgs_SoundSourceVector_h
#define _ROS_stdr_msgs_SoundSourceVector_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "stdr_msgs/SoundSource.h"

namespace stdr_msgs
{

  class SoundSourceVector : public ros::Msg
  {
    public:
      uint32_t sound_sources_length;
      typedef stdr_msgs::SoundSource _sound_sources_type;
      _sound_sources_type st_sound_sources;
      _sound_sources_type * sound_sources;

    SoundSourceVector():
      sound_sources_length(0), sound_sources(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->sound_sources_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->sound_sources_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->sound_sources_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->sound_sources_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->sound_sources_length);
      for( uint32_t i = 0; i < sound_sources_length; i++){
      offset += this->sound_sources[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t sound_sources_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      sound_sources_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      sound_sources_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      sound_sources_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->sound_sources_length);
      if(sound_sources_lengthT > sound_sources_length)
        this->sound_sources = (stdr_msgs::SoundSource*)realloc(this->sound_sources, sound_sources_lengthT * sizeof(stdr_msgs::SoundSource));
      sound_sources_length = sound_sources_lengthT;
      for( uint32_t i = 0; i < sound_sources_length; i++){
      offset += this->st_sound_sources.deserialize(inbuffer + offset);
        memcpy( &(this->sound_sources[i]), &(this->st_sound_sources), sizeof(stdr_msgs::SoundSource));
      }
     return offset;
    }

    const char * getType(){ return "stdr_msgs/SoundSourceVector"; };
    const char * getMD5(){ return "b0990ed9e7eeb58876a06c8b484951b4"; };

  };

}
#endif