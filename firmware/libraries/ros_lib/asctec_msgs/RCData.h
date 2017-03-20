#ifndef _ROS_asctec_msgs_RCData_h
#define _ROS_asctec_msgs_RCData_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace asctec_msgs
{

  class RCData : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      int16_t channels_in[8];
      int16_t channels_out[8];
      typedef int16_t _lock_type;
      _lock_type lock;

    RCData():
      header(),
      channels_in(),
      channels_out(),
      lock(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      for( uint32_t i = 0; i < 8; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_channels_ini;
      u_channels_ini.real = this->channels_in[i];
      *(outbuffer + offset + 0) = (u_channels_ini.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_channels_ini.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->channels_in[i]);
      }
      for( uint32_t i = 0; i < 8; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_channels_outi;
      u_channels_outi.real = this->channels_out[i];
      *(outbuffer + offset + 0) = (u_channels_outi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_channels_outi.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->channels_out[i]);
      }
      union {
        int16_t real;
        uint16_t base;
      } u_lock;
      u_lock.real = this->lock;
      *(outbuffer + offset + 0) = (u_lock.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_lock.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->lock);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      for( uint32_t i = 0; i < 8; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_channels_ini;
      u_channels_ini.base = 0;
      u_channels_ini.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_channels_ini.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->channels_in[i] = u_channels_ini.real;
      offset += sizeof(this->channels_in[i]);
      }
      for( uint32_t i = 0; i < 8; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_channels_outi;
      u_channels_outi.base = 0;
      u_channels_outi.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_channels_outi.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->channels_out[i] = u_channels_outi.real;
      offset += sizeof(this->channels_out[i]);
      }
      union {
        int16_t real;
        uint16_t base;
      } u_lock;
      u_lock.base = 0;
      u_lock.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_lock.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->lock = u_lock.real;
      offset += sizeof(this->lock);
     return offset;
    }

    const char * getType(){ return "asctec_msgs/RCData"; };
    const char * getMD5(){ return "d486363e6033911606202acafb1bc1a0"; };

  };

}
#endif