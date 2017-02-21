#ifndef _ROS_zeroconf_msgs_DiscoveredService_h
#define _ROS_zeroconf_msgs_DiscoveredService_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace zeroconf_msgs
{

  class DiscoveredService : public ros::Msg
  {
    public:
      const char* name;
      const char* type;
      const char* domain;
      const char* description;
      const char* hostname;
      uint8_t ipv4_addresses_length;
      char* st_ipv4_addresses;
      char* * ipv4_addresses;
      uint8_t ipv6_addresses_length;
      char* st_ipv6_addresses;
      char* * ipv6_addresses;
      int32_t port;
      uint32_t cookie;
      bool is_local;
      bool our_own;
      bool wide_area;
      bool multicast;
      bool cached;

    DiscoveredService():
      name(""),
      type(""),
      domain(""),
      description(""),
      hostname(""),
      ipv4_addresses_length(0), ipv4_addresses(NULL),
      ipv6_addresses_length(0), ipv6_addresses(NULL),
      port(0),
      cookie(0),
      is_local(0),
      our_own(0),
      wide_area(0),
      multicast(0),
      cached(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_name = strlen(this->name);
      memcpy(outbuffer + offset, &length_name, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      uint32_t length_type = strlen(this->type);
      memcpy(outbuffer + offset, &length_type, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->type, length_type);
      offset += length_type;
      uint32_t length_domain = strlen(this->domain);
      memcpy(outbuffer + offset, &length_domain, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->domain, length_domain);
      offset += length_domain;
      uint32_t length_description = strlen(this->description);
      memcpy(outbuffer + offset, &length_description, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->description, length_description);
      offset += length_description;
      uint32_t length_hostname = strlen(this->hostname);
      memcpy(outbuffer + offset, &length_hostname, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->hostname, length_hostname);
      offset += length_hostname;
      *(outbuffer + offset++) = ipv4_addresses_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < ipv4_addresses_length; i++){
      uint32_t length_ipv4_addressesi = strlen(this->ipv4_addresses[i]);
      memcpy(outbuffer + offset, &length_ipv4_addressesi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->ipv4_addresses[i], length_ipv4_addressesi);
      offset += length_ipv4_addressesi;
      }
      *(outbuffer + offset++) = ipv6_addresses_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < ipv6_addresses_length; i++){
      uint32_t length_ipv6_addressesi = strlen(this->ipv6_addresses[i]);
      memcpy(outbuffer + offset, &length_ipv6_addressesi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->ipv6_addresses[i], length_ipv6_addressesi);
      offset += length_ipv6_addressesi;
      }
      union {
        int32_t real;
        uint32_t base;
      } u_port;
      u_port.real = this->port;
      *(outbuffer + offset + 0) = (u_port.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_port.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_port.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_port.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->port);
      *(outbuffer + offset + 0) = (this->cookie >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->cookie >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->cookie >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->cookie >> (8 * 3)) & 0xFF;
      offset += sizeof(this->cookie);
      union {
        bool real;
        uint8_t base;
      } u_is_local;
      u_is_local.real = this->is_local;
      *(outbuffer + offset + 0) = (u_is_local.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->is_local);
      union {
        bool real;
        uint8_t base;
      } u_our_own;
      u_our_own.real = this->our_own;
      *(outbuffer + offset + 0) = (u_our_own.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->our_own);
      union {
        bool real;
        uint8_t base;
      } u_wide_area;
      u_wide_area.real = this->wide_area;
      *(outbuffer + offset + 0) = (u_wide_area.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->wide_area);
      union {
        bool real;
        uint8_t base;
      } u_multicast;
      u_multicast.real = this->multicast;
      *(outbuffer + offset + 0) = (u_multicast.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->multicast);
      union {
        bool real;
        uint8_t base;
      } u_cached;
      u_cached.real = this->cached;
      *(outbuffer + offset + 0) = (u_cached.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->cached);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_name;
      memcpy(&length_name, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
      uint32_t length_type;
      memcpy(&length_type, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_type-1]=0;
      this->type = (char *)(inbuffer + offset-1);
      offset += length_type;
      uint32_t length_domain;
      memcpy(&length_domain, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_domain; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_domain-1]=0;
      this->domain = (char *)(inbuffer + offset-1);
      offset += length_domain;
      uint32_t length_description;
      memcpy(&length_description, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_description; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_description-1]=0;
      this->description = (char *)(inbuffer + offset-1);
      offset += length_description;
      uint32_t length_hostname;
      memcpy(&length_hostname, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_hostname; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_hostname-1]=0;
      this->hostname = (char *)(inbuffer + offset-1);
      offset += length_hostname;
      uint8_t ipv4_addresses_lengthT = *(inbuffer + offset++);
      if(ipv4_addresses_lengthT > ipv4_addresses_length)
        this->ipv4_addresses = (char**)realloc(this->ipv4_addresses, ipv4_addresses_lengthT * sizeof(char*));
      offset += 3;
      ipv4_addresses_length = ipv4_addresses_lengthT;
      for( uint8_t i = 0; i < ipv4_addresses_length; i++){
      uint32_t length_st_ipv4_addresses;
      memcpy(&length_st_ipv4_addresses, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_ipv4_addresses; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_ipv4_addresses-1]=0;
      this->st_ipv4_addresses = (char *)(inbuffer + offset-1);
      offset += length_st_ipv4_addresses;
        memcpy( &(this->ipv4_addresses[i]), &(this->st_ipv4_addresses), sizeof(char*));
      }
      uint8_t ipv6_addresses_lengthT = *(inbuffer + offset++);
      if(ipv6_addresses_lengthT > ipv6_addresses_length)
        this->ipv6_addresses = (char**)realloc(this->ipv6_addresses, ipv6_addresses_lengthT * sizeof(char*));
      offset += 3;
      ipv6_addresses_length = ipv6_addresses_lengthT;
      for( uint8_t i = 0; i < ipv6_addresses_length; i++){
      uint32_t length_st_ipv6_addresses;
      memcpy(&length_st_ipv6_addresses, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_ipv6_addresses; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_ipv6_addresses-1]=0;
      this->st_ipv6_addresses = (char *)(inbuffer + offset-1);
      offset += length_st_ipv6_addresses;
        memcpy( &(this->ipv6_addresses[i]), &(this->st_ipv6_addresses), sizeof(char*));
      }
      union {
        int32_t real;
        uint32_t base;
      } u_port;
      u_port.base = 0;
      u_port.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_port.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_port.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_port.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->port = u_port.real;
      offset += sizeof(this->port);
      this->cookie =  ((uint32_t) (*(inbuffer + offset)));
      this->cookie |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->cookie |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->cookie |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->cookie);
      union {
        bool real;
        uint8_t base;
      } u_is_local;
      u_is_local.base = 0;
      u_is_local.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->is_local = u_is_local.real;
      offset += sizeof(this->is_local);
      union {
        bool real;
        uint8_t base;
      } u_our_own;
      u_our_own.base = 0;
      u_our_own.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->our_own = u_our_own.real;
      offset += sizeof(this->our_own);
      union {
        bool real;
        uint8_t base;
      } u_wide_area;
      u_wide_area.base = 0;
      u_wide_area.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->wide_area = u_wide_area.real;
      offset += sizeof(this->wide_area);
      union {
        bool real;
        uint8_t base;
      } u_multicast;
      u_multicast.base = 0;
      u_multicast.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->multicast = u_multicast.real;
      offset += sizeof(this->multicast);
      union {
        bool real;
        uint8_t base;
      } u_cached;
      u_cached.base = 0;
      u_cached.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->cached = u_cached.real;
      offset += sizeof(this->cached);
     return offset;
    }

    const char * getType(){ return "zeroconf_msgs/DiscoveredService"; };
    const char * getMD5(){ return "3aabc6dd9875ef180c75536ad9a51d86"; };

  };

}
#endif