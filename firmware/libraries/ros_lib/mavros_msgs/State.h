#ifndef _ROS_mavros_msgs_State_h
#define _ROS_mavros_msgs_State_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace mavros_msgs
{

  class State : public ros::Msg
  {
    public:
      std_msgs::Header header;
      bool connected;
      bool armed;
      bool guided;
      const char* mode;

    State():
      header(),
      connected(0),
      armed(0),
      guided(0),
      mode("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_connected;
      u_connected.real = this->connected;
      *(outbuffer + offset + 0) = (u_connected.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->connected);
      union {
        bool real;
        uint8_t base;
      } u_armed;
      u_armed.real = this->armed;
      *(outbuffer + offset + 0) = (u_armed.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->armed);
      union {
        bool real;
        uint8_t base;
      } u_guided;
      u_guided.real = this->guided;
      *(outbuffer + offset + 0) = (u_guided.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->guided);
      uint32_t length_mode = strlen(this->mode);
      memcpy(outbuffer + offset, &length_mode, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->mode, length_mode);
      offset += length_mode;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_connected;
      u_connected.base = 0;
      u_connected.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->connected = u_connected.real;
      offset += sizeof(this->connected);
      union {
        bool real;
        uint8_t base;
      } u_armed;
      u_armed.base = 0;
      u_armed.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->armed = u_armed.real;
      offset += sizeof(this->armed);
      union {
        bool real;
        uint8_t base;
      } u_guided;
      u_guided.base = 0;
      u_guided.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->guided = u_guided.real;
      offset += sizeof(this->guided);
      uint32_t length_mode;
      memcpy(&length_mode, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_mode; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_mode-1]=0;
      this->mode = (char *)(inbuffer + offset-1);
      offset += length_mode;
     return offset;
    }

    const char * getType(){ return "mavros_msgs/State"; };
    const char * getMD5(){ return "9e3d873fae342c8f48a8bd64c53d991e"; };

  };

}
#endif