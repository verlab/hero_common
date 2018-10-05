#ifndef _ROS_espuck_driver_Microphone_h
#define _ROS_espuck_driver_Microphone_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace espuck_driver
{

  class Microphone : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t microphone_length;
      typedef int16_t _microphone_type;
      _microphone_type st_microphone;
      _microphone_type * microphone;

    Microphone():
      header(),
      microphone_length(0), microphone(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->microphone_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->microphone_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->microphone_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->microphone_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->microphone_length);
      for( uint32_t i = 0; i < microphone_length; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_microphonei;
      u_microphonei.real = this->microphone[i];
      *(outbuffer + offset + 0) = (u_microphonei.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_microphonei.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->microphone[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t microphone_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      microphone_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      microphone_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      microphone_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->microphone_length);
      if(microphone_lengthT > microphone_length)
        this->microphone = (int16_t*)realloc(this->microphone, microphone_lengthT * sizeof(int16_t));
      microphone_length = microphone_lengthT;
      for( uint32_t i = 0; i < microphone_length; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_st_microphone;
      u_st_microphone.base = 0;
      u_st_microphone.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_microphone.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->st_microphone = u_st_microphone.real;
      offset += sizeof(this->st_microphone);
        memcpy( &(this->microphone[i]), &(this->st_microphone), sizeof(int16_t));
      }
     return offset;
    }

    const char * getType(){ return "espuck_driver/Microphone"; };
    const char * getMD5(){ return "c9a3651191aeb2d2d1d3e420edf56397"; };

  };

}
#endif