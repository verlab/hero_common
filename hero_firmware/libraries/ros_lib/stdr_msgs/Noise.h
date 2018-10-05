#ifndef _ROS_stdr_msgs_Noise_h
#define _ROS_stdr_msgs_Noise_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace stdr_msgs
{

  class Noise : public ros::Msg
  {
    public:
      typedef bool _noise_type;
      _noise_type noise;
      typedef float _noiseMean_type;
      _noiseMean_type noiseMean;
      typedef float _noiseStd_type;
      _noiseStd_type noiseStd;

    Noise():
      noise(0),
      noiseMean(0),
      noiseStd(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_noise;
      u_noise.real = this->noise;
      *(outbuffer + offset + 0) = (u_noise.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->noise);
      union {
        float real;
        uint32_t base;
      } u_noiseMean;
      u_noiseMean.real = this->noiseMean;
      *(outbuffer + offset + 0) = (u_noiseMean.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_noiseMean.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_noiseMean.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_noiseMean.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->noiseMean);
      union {
        float real;
        uint32_t base;
      } u_noiseStd;
      u_noiseStd.real = this->noiseStd;
      *(outbuffer + offset + 0) = (u_noiseStd.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_noiseStd.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_noiseStd.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_noiseStd.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->noiseStd);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_noise;
      u_noise.base = 0;
      u_noise.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->noise = u_noise.real;
      offset += sizeof(this->noise);
      union {
        float real;
        uint32_t base;
      } u_noiseMean;
      u_noiseMean.base = 0;
      u_noiseMean.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_noiseMean.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_noiseMean.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_noiseMean.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->noiseMean = u_noiseMean.real;
      offset += sizeof(this->noiseMean);
      union {
        float real;
        uint32_t base;
      } u_noiseStd;
      u_noiseStd.base = 0;
      u_noiseStd.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_noiseStd.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_noiseStd.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_noiseStd.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->noiseStd = u_noiseStd.real;
      offset += sizeof(this->noiseStd);
     return offset;
    }

    const char * getType(){ return "stdr_msgs/Noise"; };
    const char * getMD5(){ return "a882ac96256e87f019f2655e9d7f0f81"; };

  };

}
#endif