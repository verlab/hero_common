#ifndef _ROS_SERVICE_Authentication_h
#define _ROS_SERVICE_Authentication_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ros/time.h"

namespace rosauth
{

static const char AUTHENTICATION[] = "rosauth/Authentication";

  class AuthenticationRequest : public ros::Msg
  {
    public:
      typedef const char* _mac_type;
      _mac_type mac;
      typedef const char* _client_type;
      _client_type client;
      typedef const char* _dest_type;
      _dest_type dest;
      typedef const char* _rand_type;
      _rand_type rand;
      typedef ros::Time _t_type;
      _t_type t;
      typedef const char* _level_type;
      _level_type level;
      typedef ros::Time _end_type;
      _end_type end;

    AuthenticationRequest():
      mac(""),
      client(""),
      dest(""),
      rand(""),
      t(),
      level(""),
      end()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_mac = strlen(this->mac);
      varToArr(outbuffer + offset, length_mac);
      offset += 4;
      memcpy(outbuffer + offset, this->mac, length_mac);
      offset += length_mac;
      uint32_t length_client = strlen(this->client);
      varToArr(outbuffer + offset, length_client);
      offset += 4;
      memcpy(outbuffer + offset, this->client, length_client);
      offset += length_client;
      uint32_t length_dest = strlen(this->dest);
      varToArr(outbuffer + offset, length_dest);
      offset += 4;
      memcpy(outbuffer + offset, this->dest, length_dest);
      offset += length_dest;
      uint32_t length_rand = strlen(this->rand);
      varToArr(outbuffer + offset, length_rand);
      offset += 4;
      memcpy(outbuffer + offset, this->rand, length_rand);
      offset += length_rand;
      *(outbuffer + offset + 0) = (this->t.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->t.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->t.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->t.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->t.sec);
      *(outbuffer + offset + 0) = (this->t.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->t.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->t.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->t.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->t.nsec);
      uint32_t length_level = strlen(this->level);
      varToArr(outbuffer + offset, length_level);
      offset += 4;
      memcpy(outbuffer + offset, this->level, length_level);
      offset += length_level;
      *(outbuffer + offset + 0) = (this->end.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->end.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->end.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->end.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->end.sec);
      *(outbuffer + offset + 0) = (this->end.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->end.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->end.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->end.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->end.nsec);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_mac;
      arrToVar(length_mac, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_mac; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_mac-1]=0;
      this->mac = (char *)(inbuffer + offset-1);
      offset += length_mac;
      uint32_t length_client;
      arrToVar(length_client, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_client; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_client-1]=0;
      this->client = (char *)(inbuffer + offset-1);
      offset += length_client;
      uint32_t length_dest;
      arrToVar(length_dest, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_dest; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_dest-1]=0;
      this->dest = (char *)(inbuffer + offset-1);
      offset += length_dest;
      uint32_t length_rand;
      arrToVar(length_rand, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_rand; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_rand-1]=0;
      this->rand = (char *)(inbuffer + offset-1);
      offset += length_rand;
      this->t.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->t.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->t.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->t.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->t.sec);
      this->t.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->t.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->t.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->t.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->t.nsec);
      uint32_t length_level;
      arrToVar(length_level, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_level; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_level-1]=0;
      this->level = (char *)(inbuffer + offset-1);
      offset += length_level;
      this->end.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->end.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->end.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->end.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->end.sec);
      this->end.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->end.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->end.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->end.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->end.nsec);
     return offset;
    }

    const char * getType(){ return AUTHENTICATION; };
    const char * getMD5(){ return "cad474945b8be70807460ba22a018b32"; };

  };

  class AuthenticationResponse : public ros::Msg
  {
    public:
      typedef bool _authenticated_type;
      _authenticated_type authenticated;

    AuthenticationResponse():
      authenticated(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_authenticated;
      u_authenticated.real = this->authenticated;
      *(outbuffer + offset + 0) = (u_authenticated.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->authenticated);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_authenticated;
      u_authenticated.base = 0;
      u_authenticated.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->authenticated = u_authenticated.real;
      offset += sizeof(this->authenticated);
     return offset;
    }

    const char * getType(){ return AUTHENTICATION; };
    const char * getMD5(){ return "7eb9cf569b3e4581e3eff49da1ca4f39"; };

  };

  class Authentication {
    public:
    typedef AuthenticationRequest Request;
    typedef AuthenticationResponse Response;
  };

}
#endif
