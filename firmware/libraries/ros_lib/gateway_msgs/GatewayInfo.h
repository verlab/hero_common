#ifndef _ROS_gateway_msgs_GatewayInfo_h
#define _ROS_gateway_msgs_GatewayInfo_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "gateway_msgs/Rule.h"
#include "gateway_msgs/RemoteRuleWithStatus.h"
#include "gateway_msgs/RemoteRule.h"

namespace gateway_msgs
{

  class GatewayInfo : public ros::Msg
  {
    public:
      const char* name;
      bool connected;
      const char* ip;
      uint8_t hub_names_length;
      char* st_hub_names;
      char* * hub_names;
      uint8_t hub_uris_length;
      char* st_hub_uris;
      char* * hub_uris;
      bool firewall;
      uint8_t public_watchlist_length;
      gateway_msgs::Rule st_public_watchlist;
      gateway_msgs::Rule * public_watchlist;
      uint8_t public_interface_length;
      gateway_msgs::Rule st_public_interface;
      gateway_msgs::Rule * public_interface;
      uint8_t flipped_connections_length;
      gateway_msgs::RemoteRuleWithStatus st_flipped_connections;
      gateway_msgs::RemoteRuleWithStatus * flipped_connections;
      uint8_t flip_watchlist_length;
      gateway_msgs::RemoteRule st_flip_watchlist;
      gateway_msgs::RemoteRule * flip_watchlist;
      uint8_t flipped_in_connections_length;
      gateway_msgs::RemoteRule st_flipped_in_connections;
      gateway_msgs::RemoteRule * flipped_in_connections;
      uint8_t pull_watchlist_length;
      gateway_msgs::RemoteRule st_pull_watchlist;
      gateway_msgs::RemoteRule * pull_watchlist;
      uint8_t pulled_connections_length;
      gateway_msgs::RemoteRule st_pulled_connections;
      gateway_msgs::RemoteRule * pulled_connections;

    GatewayInfo():
      name(""),
      connected(0),
      ip(""),
      hub_names_length(0), hub_names(NULL),
      hub_uris_length(0), hub_uris(NULL),
      firewall(0),
      public_watchlist_length(0), public_watchlist(NULL),
      public_interface_length(0), public_interface(NULL),
      flipped_connections_length(0), flipped_connections(NULL),
      flip_watchlist_length(0), flip_watchlist(NULL),
      flipped_in_connections_length(0), flipped_in_connections(NULL),
      pull_watchlist_length(0), pull_watchlist(NULL),
      pulled_connections_length(0), pulled_connections(NULL)
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
      union {
        bool real;
        uint8_t base;
      } u_connected;
      u_connected.real = this->connected;
      *(outbuffer + offset + 0) = (u_connected.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->connected);
      uint32_t length_ip = strlen(this->ip);
      memcpy(outbuffer + offset, &length_ip, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->ip, length_ip);
      offset += length_ip;
      *(outbuffer + offset++) = hub_names_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < hub_names_length; i++){
      uint32_t length_hub_namesi = strlen(this->hub_names[i]);
      memcpy(outbuffer + offset, &length_hub_namesi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->hub_names[i], length_hub_namesi);
      offset += length_hub_namesi;
      }
      *(outbuffer + offset++) = hub_uris_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < hub_uris_length; i++){
      uint32_t length_hub_urisi = strlen(this->hub_uris[i]);
      memcpy(outbuffer + offset, &length_hub_urisi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->hub_uris[i], length_hub_urisi);
      offset += length_hub_urisi;
      }
      union {
        bool real;
        uint8_t base;
      } u_firewall;
      u_firewall.real = this->firewall;
      *(outbuffer + offset + 0) = (u_firewall.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->firewall);
      *(outbuffer + offset++) = public_watchlist_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < public_watchlist_length; i++){
      offset += this->public_watchlist[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = public_interface_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < public_interface_length; i++){
      offset += this->public_interface[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = flipped_connections_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < flipped_connections_length; i++){
      offset += this->flipped_connections[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = flip_watchlist_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < flip_watchlist_length; i++){
      offset += this->flip_watchlist[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = flipped_in_connections_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < flipped_in_connections_length; i++){
      offset += this->flipped_in_connections[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = pull_watchlist_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < pull_watchlist_length; i++){
      offset += this->pull_watchlist[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = pulled_connections_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < pulled_connections_length; i++){
      offset += this->pulled_connections[i].serialize(outbuffer + offset);
      }
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
      union {
        bool real;
        uint8_t base;
      } u_connected;
      u_connected.base = 0;
      u_connected.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->connected = u_connected.real;
      offset += sizeof(this->connected);
      uint32_t length_ip;
      memcpy(&length_ip, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_ip; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_ip-1]=0;
      this->ip = (char *)(inbuffer + offset-1);
      offset += length_ip;
      uint8_t hub_names_lengthT = *(inbuffer + offset++);
      if(hub_names_lengthT > hub_names_length)
        this->hub_names = (char**)realloc(this->hub_names, hub_names_lengthT * sizeof(char*));
      offset += 3;
      hub_names_length = hub_names_lengthT;
      for( uint8_t i = 0; i < hub_names_length; i++){
      uint32_t length_st_hub_names;
      memcpy(&length_st_hub_names, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_hub_names; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_hub_names-1]=0;
      this->st_hub_names = (char *)(inbuffer + offset-1);
      offset += length_st_hub_names;
        memcpy( &(this->hub_names[i]), &(this->st_hub_names), sizeof(char*));
      }
      uint8_t hub_uris_lengthT = *(inbuffer + offset++);
      if(hub_uris_lengthT > hub_uris_length)
        this->hub_uris = (char**)realloc(this->hub_uris, hub_uris_lengthT * sizeof(char*));
      offset += 3;
      hub_uris_length = hub_uris_lengthT;
      for( uint8_t i = 0; i < hub_uris_length; i++){
      uint32_t length_st_hub_uris;
      memcpy(&length_st_hub_uris, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_hub_uris; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_hub_uris-1]=0;
      this->st_hub_uris = (char *)(inbuffer + offset-1);
      offset += length_st_hub_uris;
        memcpy( &(this->hub_uris[i]), &(this->st_hub_uris), sizeof(char*));
      }
      union {
        bool real;
        uint8_t base;
      } u_firewall;
      u_firewall.base = 0;
      u_firewall.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->firewall = u_firewall.real;
      offset += sizeof(this->firewall);
      uint8_t public_watchlist_lengthT = *(inbuffer + offset++);
      if(public_watchlist_lengthT > public_watchlist_length)
        this->public_watchlist = (gateway_msgs::Rule*)realloc(this->public_watchlist, public_watchlist_lengthT * sizeof(gateway_msgs::Rule));
      offset += 3;
      public_watchlist_length = public_watchlist_lengthT;
      for( uint8_t i = 0; i < public_watchlist_length; i++){
      offset += this->st_public_watchlist.deserialize(inbuffer + offset);
        memcpy( &(this->public_watchlist[i]), &(this->st_public_watchlist), sizeof(gateway_msgs::Rule));
      }
      uint8_t public_interface_lengthT = *(inbuffer + offset++);
      if(public_interface_lengthT > public_interface_length)
        this->public_interface = (gateway_msgs::Rule*)realloc(this->public_interface, public_interface_lengthT * sizeof(gateway_msgs::Rule));
      offset += 3;
      public_interface_length = public_interface_lengthT;
      for( uint8_t i = 0; i < public_interface_length; i++){
      offset += this->st_public_interface.deserialize(inbuffer + offset);
        memcpy( &(this->public_interface[i]), &(this->st_public_interface), sizeof(gateway_msgs::Rule));
      }
      uint8_t flipped_connections_lengthT = *(inbuffer + offset++);
      if(flipped_connections_lengthT > flipped_connections_length)
        this->flipped_connections = (gateway_msgs::RemoteRuleWithStatus*)realloc(this->flipped_connections, flipped_connections_lengthT * sizeof(gateway_msgs::RemoteRuleWithStatus));
      offset += 3;
      flipped_connections_length = flipped_connections_lengthT;
      for( uint8_t i = 0; i < flipped_connections_length; i++){
      offset += this->st_flipped_connections.deserialize(inbuffer + offset);
        memcpy( &(this->flipped_connections[i]), &(this->st_flipped_connections), sizeof(gateway_msgs::RemoteRuleWithStatus));
      }
      uint8_t flip_watchlist_lengthT = *(inbuffer + offset++);
      if(flip_watchlist_lengthT > flip_watchlist_length)
        this->flip_watchlist = (gateway_msgs::RemoteRule*)realloc(this->flip_watchlist, flip_watchlist_lengthT * sizeof(gateway_msgs::RemoteRule));
      offset += 3;
      flip_watchlist_length = flip_watchlist_lengthT;
      for( uint8_t i = 0; i < flip_watchlist_length; i++){
      offset += this->st_flip_watchlist.deserialize(inbuffer + offset);
        memcpy( &(this->flip_watchlist[i]), &(this->st_flip_watchlist), sizeof(gateway_msgs::RemoteRule));
      }
      uint8_t flipped_in_connections_lengthT = *(inbuffer + offset++);
      if(flipped_in_connections_lengthT > flipped_in_connections_length)
        this->flipped_in_connections = (gateway_msgs::RemoteRule*)realloc(this->flipped_in_connections, flipped_in_connections_lengthT * sizeof(gateway_msgs::RemoteRule));
      offset += 3;
      flipped_in_connections_length = flipped_in_connections_lengthT;
      for( uint8_t i = 0; i < flipped_in_connections_length; i++){
      offset += this->st_flipped_in_connections.deserialize(inbuffer + offset);
        memcpy( &(this->flipped_in_connections[i]), &(this->st_flipped_in_connections), sizeof(gateway_msgs::RemoteRule));
      }
      uint8_t pull_watchlist_lengthT = *(inbuffer + offset++);
      if(pull_watchlist_lengthT > pull_watchlist_length)
        this->pull_watchlist = (gateway_msgs::RemoteRule*)realloc(this->pull_watchlist, pull_watchlist_lengthT * sizeof(gateway_msgs::RemoteRule));
      offset += 3;
      pull_watchlist_length = pull_watchlist_lengthT;
      for( uint8_t i = 0; i < pull_watchlist_length; i++){
      offset += this->st_pull_watchlist.deserialize(inbuffer + offset);
        memcpy( &(this->pull_watchlist[i]), &(this->st_pull_watchlist), sizeof(gateway_msgs::RemoteRule));
      }
      uint8_t pulled_connections_lengthT = *(inbuffer + offset++);
      if(pulled_connections_lengthT > pulled_connections_length)
        this->pulled_connections = (gateway_msgs::RemoteRule*)realloc(this->pulled_connections, pulled_connections_lengthT * sizeof(gateway_msgs::RemoteRule));
      offset += 3;
      pulled_connections_length = pulled_connections_lengthT;
      for( uint8_t i = 0; i < pulled_connections_length; i++){
      offset += this->st_pulled_connections.deserialize(inbuffer + offset);
        memcpy( &(this->pulled_connections[i]), &(this->st_pulled_connections), sizeof(gateway_msgs::RemoteRule));
      }
     return offset;
    }

    const char * getType(){ return "gateway_msgs/GatewayInfo"; };
    const char * getMD5(){ return "8e8f7efa326aa247c5cb6a9692ec8014"; };

  };

}
#endif