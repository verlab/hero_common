#ifndef _ROS_stdr_msgs_KinematicMsg_h
#define _ROS_stdr_msgs_KinematicMsg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace stdr_msgs
{

  class KinematicMsg : public ros::Msg
  {
    public:
      typedef const char* _type_type;
      _type_type type;
      typedef float _a_ux_ux_type;
      _a_ux_ux_type a_ux_ux;
      typedef float _a_ux_uy_type;
      _a_ux_uy_type a_ux_uy;
      typedef float _a_ux_w_type;
      _a_ux_w_type a_ux_w;
      typedef float _a_uy_ux_type;
      _a_uy_ux_type a_uy_ux;
      typedef float _a_uy_uy_type;
      _a_uy_uy_type a_uy_uy;
      typedef float _a_uy_w_type;
      _a_uy_w_type a_uy_w;
      typedef float _a_w_ux_type;
      _a_w_ux_type a_w_ux;
      typedef float _a_w_uy_type;
      _a_w_uy_type a_w_uy;
      typedef float _a_w_w_type;
      _a_w_w_type a_w_w;
      typedef float _a_g_ux_type;
      _a_g_ux_type a_g_ux;
      typedef float _a_g_uy_type;
      _a_g_uy_type a_g_uy;
      typedef float _a_g_w_type;
      _a_g_w_type a_g_w;

    KinematicMsg():
      type(""),
      a_ux_ux(0),
      a_ux_uy(0),
      a_ux_w(0),
      a_uy_ux(0),
      a_uy_uy(0),
      a_uy_w(0),
      a_w_ux(0),
      a_w_uy(0),
      a_w_w(0),
      a_g_ux(0),
      a_g_uy(0),
      a_g_w(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_type = strlen(this->type);
      varToArr(outbuffer + offset, length_type);
      offset += 4;
      memcpy(outbuffer + offset, this->type, length_type);
      offset += length_type;
      union {
        float real;
        uint32_t base;
      } u_a_ux_ux;
      u_a_ux_ux.real = this->a_ux_ux;
      *(outbuffer + offset + 0) = (u_a_ux_ux.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_a_ux_ux.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_a_ux_ux.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_a_ux_ux.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->a_ux_ux);
      union {
        float real;
        uint32_t base;
      } u_a_ux_uy;
      u_a_ux_uy.real = this->a_ux_uy;
      *(outbuffer + offset + 0) = (u_a_ux_uy.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_a_ux_uy.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_a_ux_uy.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_a_ux_uy.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->a_ux_uy);
      union {
        float real;
        uint32_t base;
      } u_a_ux_w;
      u_a_ux_w.real = this->a_ux_w;
      *(outbuffer + offset + 0) = (u_a_ux_w.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_a_ux_w.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_a_ux_w.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_a_ux_w.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->a_ux_w);
      union {
        float real;
        uint32_t base;
      } u_a_uy_ux;
      u_a_uy_ux.real = this->a_uy_ux;
      *(outbuffer + offset + 0) = (u_a_uy_ux.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_a_uy_ux.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_a_uy_ux.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_a_uy_ux.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->a_uy_ux);
      union {
        float real;
        uint32_t base;
      } u_a_uy_uy;
      u_a_uy_uy.real = this->a_uy_uy;
      *(outbuffer + offset + 0) = (u_a_uy_uy.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_a_uy_uy.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_a_uy_uy.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_a_uy_uy.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->a_uy_uy);
      union {
        float real;
        uint32_t base;
      } u_a_uy_w;
      u_a_uy_w.real = this->a_uy_w;
      *(outbuffer + offset + 0) = (u_a_uy_w.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_a_uy_w.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_a_uy_w.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_a_uy_w.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->a_uy_w);
      union {
        float real;
        uint32_t base;
      } u_a_w_ux;
      u_a_w_ux.real = this->a_w_ux;
      *(outbuffer + offset + 0) = (u_a_w_ux.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_a_w_ux.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_a_w_ux.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_a_w_ux.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->a_w_ux);
      union {
        float real;
        uint32_t base;
      } u_a_w_uy;
      u_a_w_uy.real = this->a_w_uy;
      *(outbuffer + offset + 0) = (u_a_w_uy.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_a_w_uy.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_a_w_uy.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_a_w_uy.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->a_w_uy);
      union {
        float real;
        uint32_t base;
      } u_a_w_w;
      u_a_w_w.real = this->a_w_w;
      *(outbuffer + offset + 0) = (u_a_w_w.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_a_w_w.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_a_w_w.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_a_w_w.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->a_w_w);
      union {
        float real;
        uint32_t base;
      } u_a_g_ux;
      u_a_g_ux.real = this->a_g_ux;
      *(outbuffer + offset + 0) = (u_a_g_ux.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_a_g_ux.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_a_g_ux.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_a_g_ux.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->a_g_ux);
      union {
        float real;
        uint32_t base;
      } u_a_g_uy;
      u_a_g_uy.real = this->a_g_uy;
      *(outbuffer + offset + 0) = (u_a_g_uy.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_a_g_uy.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_a_g_uy.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_a_g_uy.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->a_g_uy);
      union {
        float real;
        uint32_t base;
      } u_a_g_w;
      u_a_g_w.real = this->a_g_w;
      *(outbuffer + offset + 0) = (u_a_g_w.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_a_g_w.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_a_g_w.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_a_g_w.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->a_g_w);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_type;
      arrToVar(length_type, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_type-1]=0;
      this->type = (char *)(inbuffer + offset-1);
      offset += length_type;
      union {
        float real;
        uint32_t base;
      } u_a_ux_ux;
      u_a_ux_ux.base = 0;
      u_a_ux_ux.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_a_ux_ux.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_a_ux_ux.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_a_ux_ux.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->a_ux_ux = u_a_ux_ux.real;
      offset += sizeof(this->a_ux_ux);
      union {
        float real;
        uint32_t base;
      } u_a_ux_uy;
      u_a_ux_uy.base = 0;
      u_a_ux_uy.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_a_ux_uy.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_a_ux_uy.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_a_ux_uy.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->a_ux_uy = u_a_ux_uy.real;
      offset += sizeof(this->a_ux_uy);
      union {
        float real;
        uint32_t base;
      } u_a_ux_w;
      u_a_ux_w.base = 0;
      u_a_ux_w.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_a_ux_w.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_a_ux_w.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_a_ux_w.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->a_ux_w = u_a_ux_w.real;
      offset += sizeof(this->a_ux_w);
      union {
        float real;
        uint32_t base;
      } u_a_uy_ux;
      u_a_uy_ux.base = 0;
      u_a_uy_ux.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_a_uy_ux.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_a_uy_ux.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_a_uy_ux.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->a_uy_ux = u_a_uy_ux.real;
      offset += sizeof(this->a_uy_ux);
      union {
        float real;
        uint32_t base;
      } u_a_uy_uy;
      u_a_uy_uy.base = 0;
      u_a_uy_uy.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_a_uy_uy.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_a_uy_uy.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_a_uy_uy.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->a_uy_uy = u_a_uy_uy.real;
      offset += sizeof(this->a_uy_uy);
      union {
        float real;
        uint32_t base;
      } u_a_uy_w;
      u_a_uy_w.base = 0;
      u_a_uy_w.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_a_uy_w.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_a_uy_w.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_a_uy_w.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->a_uy_w = u_a_uy_w.real;
      offset += sizeof(this->a_uy_w);
      union {
        float real;
        uint32_t base;
      } u_a_w_ux;
      u_a_w_ux.base = 0;
      u_a_w_ux.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_a_w_ux.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_a_w_ux.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_a_w_ux.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->a_w_ux = u_a_w_ux.real;
      offset += sizeof(this->a_w_ux);
      union {
        float real;
        uint32_t base;
      } u_a_w_uy;
      u_a_w_uy.base = 0;
      u_a_w_uy.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_a_w_uy.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_a_w_uy.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_a_w_uy.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->a_w_uy = u_a_w_uy.real;
      offset += sizeof(this->a_w_uy);
      union {
        float real;
        uint32_t base;
      } u_a_w_w;
      u_a_w_w.base = 0;
      u_a_w_w.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_a_w_w.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_a_w_w.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_a_w_w.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->a_w_w = u_a_w_w.real;
      offset += sizeof(this->a_w_w);
      union {
        float real;
        uint32_t base;
      } u_a_g_ux;
      u_a_g_ux.base = 0;
      u_a_g_ux.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_a_g_ux.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_a_g_ux.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_a_g_ux.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->a_g_ux = u_a_g_ux.real;
      offset += sizeof(this->a_g_ux);
      union {
        float real;
        uint32_t base;
      } u_a_g_uy;
      u_a_g_uy.base = 0;
      u_a_g_uy.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_a_g_uy.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_a_g_uy.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_a_g_uy.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->a_g_uy = u_a_g_uy.real;
      offset += sizeof(this->a_g_uy);
      union {
        float real;
        uint32_t base;
      } u_a_g_w;
      u_a_g_w.base = 0;
      u_a_g_w.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_a_g_w.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_a_g_w.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_a_g_w.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->a_g_w = u_a_g_w.real;
      offset += sizeof(this->a_g_w);
     return offset;
    }

    const char * getType(){ return "stdr_msgs/KinematicMsg"; };
    const char * getMD5(){ return "75d30a9f55f18dd9353f0abaabfaf261"; };

  };

}
#endif