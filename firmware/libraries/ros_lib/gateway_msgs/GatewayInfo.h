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
      typedef const char* _name_type;
      _name_type name;
      typedef bool _connected_type;
      _connected_type connected;
      typedef const char* _ip_type;
      _ip_type ip;
      uint32_t hub_names_length;
      typedef char* _hub_names_type;
      _hub_names_type st_hub_names;
      _hub_names_type * hub_names;
      uint32_t hub_uris_length;
      typedef char* _hub_uris_type;
      _hub_uris_type st_hub_uris;
      _hub_uris_type * hub_uris;
      typedef bool _firewall_type;
      _firewall_type firewall;
      uint32_t public_watchlist_length;
      typedef gateway_msgs::Rule _public_watchlist_type;
      _public_watchlist_type st_public_watchlist;
      _public_watchlist_type * public_watchlist;
      uint32_t public_interface_length;
      typedef gateway_msgs::Rule _public_interface_type;
      _public_interface_type st_public_interface;
      _public_interface_type * public_interface;
      uint32_t flipped_connections_length;
      typedef gateway_msgs::RemoteRuleWithStatus _flipped_connections_type;
      _flipped_connections_type st_flipped_connections;
      _flipped_connections_type * flipped_connections;
      uint32_t flip_watchlist_length;
      typedef gateway_msgs::RemoteRule _flip_watchlist_type;
      _flip_watchlist_type st_flip_watchlist;
      _flip_watchlist_type * flip_watchlist;
      uint32_t flipped_in_connections_length;
      typedef gateway_msgs::RemoteRule _flipped_in_connections_type;
      _flipped_in_connections_type st_flipped_in_connections;
      _flipped_in_connections_type * flipped_in_connections;
      uint32_t pull_watchlist_length;
      typedef gateway_msgs::RemoteRule _pull_watchlist_type;
      _pull_watchlist_type st_pull_watchlist;
      _pull_watchlist_type * pull_watchlist;
      uint32_t pulled_connections_length;
      typedef gateway_msgs::RemoteRule _pulled_connections_type;
      _pulled_connections_type st_pulled_connections;
      _pulled_connections_type * pulled_connections;

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
      varToArr(outbuffer + offset, length_name);
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
      varToArr(outbuffer + offset, length_ip);
      offset += 4;
      memcpy(outbuffer + offset, this->ip, length_ip);
      offset += length_ip;
      *(outbuffer + offset + 0) = (this->hub_names_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->hub_names_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->hub_names_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->hub_names_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->hub_names_length);
      for( uint32_t i = 0; i < hub_names_length; i++){
      uint32_t length_hub_namesi = strlen(this->hub_names[i]);
      varToArr(outbuffer + offset, length_hub_namesi);
      offset += 4;
      memcpy(outbuffer + offset, this->hub_names[i], length_hub_namesi);
      offset += length_hub_namesi;
      }
      *(outbuffer + offset + 0) = (this->hub_uris_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->hub_uris_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->hub_uris_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->hub_uris_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->hub_uris_length);
      for( uint32_t i = 0; i < hub_uris_length; i++){
      uint32_t length_hub_urisi = strlen(this->hub_uris[i]);
      varToArr(outbuffer + offset, length_hub_urisi);
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
      *(outbuffer + offset + 0) = (this->public_watchlist_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->public_watchlist_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->public_watchlist_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->public_watchlist_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->public_watchlist_length);
      for( uint32_t i = 0; i < public_watchlist_length; i++){
      offset += this->public_watchlist[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->public_interface_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->public_interface_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->public_interface_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->public_interface_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->public_interface_length);
      for( uint32_t i = 0; i < public_interface_length; i++){
      offset += this->public_interface[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->flipped_connections_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->flipped_connections_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->flipped_connections_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->flipped_connections_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->flipped_connections_length);
      for( uint32_t i = 0; i < flipped_connections_length; i++){
      offset += this->flipped_connections[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->flip_watchlist_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->flip_watchlist_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->flip_watchlist_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->flip_watchlist_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->flip_watchlist_length);
      for( uint32_t i = 0; i < flip_watchlist_length; i++){
      offset += this->flip_watchlist[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->flipped_in_connections_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->flipped_in_connections_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->flipped_in_connections_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->flipped_in_connections_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->flipped_in_connections_length);
      for( uint32_t i = 0; i < flipped_in_connections_length; i++){
      offset += this->flipped_in_connections[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->pull_watchlist_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->pull_watchlist_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->pull_watchlist_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->pull_watchlist_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pull_watchlist_length);
      for( uint32_t i = 0; i < pull_watchlist_length; i++){
      offset += this->pull_watchlist[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->pulled_connections_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->pulled_connections_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->pulled_connections_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->pulled_connections_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pulled_connections_length);
      for( uint32_t i = 0; i < pulled_connections_length; i++){
      offset += this->pulled_connections[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
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
      arrToVar(length_ip, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_ip; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_ip-1]=0;
      this->ip = (char *)(inbuffer + offset-1);
      offset += length_ip;
      uint32_t hub_names_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      hub_names_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      hub_names_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      hub_names_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->hub_names_length);
      if(hub_names_lengthT > hub_names_length)
        this->hub_names = (char**)realloc(this->hub_names, hub_names_lengthT * sizeof(char*));
      hub_names_length = hub_names_lengthT;
      for( uint32_t i = 0; i < hub_names_length; i++){
      uint32_t length_st_hub_names;
      arrToVar(length_st_hub_names, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_hub_names; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_hub_names-1]=0;
      this->st_hub_names = (char *)(inbuffer + offset-1);
      offset += length_st_hub_names;
        memcpy( &(this->hub_names[i]), &(this->st_hub_names), sizeof(char*));
      }
      uint32_t hub_uris_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      hub_uris_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      hub_uris_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      hub_uris_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->hub_uris_length);
      if(hub_uris_lengthT > hub_uris_length)
        this->hub_uris = (char**)realloc(this->hub_uris, hub_uris_lengthT * sizeof(char*));
      hub_uris_length = hub_uris_lengthT;
      for( uint32_t i = 0; i < hub_uris_length; i++){
      uint32_t length_st_hub_uris;
      arrToVar(length_st_hub_uris, (inbuffer + offset));
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
      uint32_t public_watchlist_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      public_watchlist_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      public_watchlist_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      public_watchlist_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->public_watchlist_length);
      if(public_watchlist_lengthT > public_watchlist_length)
        this->public_watchlist = (gateway_msgs::Rule*)realloc(this->public_watchlist, public_watchlist_lengthT * sizeof(gateway_msgs::Rule));
      public_watchlist_length = public_watchlist_lengthT;
      for( uint32_t i = 0; i < public_watchlist_length; i++){
      offset += this->st_public_watchlist.deserialize(inbuffer + offset);
        memcpy( &(this->public_watchlist[i]), &(this->st_public_watchlist), sizeof(gateway_msgs::Rule));
      }
      uint32_t public_interface_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      public_interface_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      public_interface_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      public_interface_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->public_interface_length);
      if(public_interface_lengthT > public_interface_length)
        this->public_interface = (gateway_msgs::Rule*)realloc(this->public_interface, public_interface_lengthT * sizeof(gateway_msgs::Rule));
      public_interface_length = public_interface_lengthT;
      for( uint32_t i = 0; i < public_interface_length; i++){
      offset += this->st_public_interface.deserialize(inbuffer + offset);
        memcpy( &(this->public_interface[i]), &(this->st_public_interface), sizeof(gateway_msgs::Rule));
      }
      uint32_t flipped_connections_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      flipped_connections_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      flipped_connections_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      flipped_connections_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->flipped_connections_length);
      if(flipped_connections_lengthT > flipped_connections_length)
        this->flipped_connections = (gateway_msgs::RemoteRuleWithStatus*)realloc(this->flipped_connections, flipped_connections_lengthT * sizeof(gateway_msgs::RemoteRuleWithStatus));
      flipped_connections_length = flipped_connections_lengthT;
      for( uint32_t i = 0; i < flipped_connections_length; i++){
      offset += this->st_flipped_connections.deserialize(inbuffer + offset);
        memcpy( &(this->flipped_connections[i]), &(this->st_flipped_connections), sizeof(gateway_msgs::RemoteRuleWithStatus));
      }
      uint32_t flip_watchlist_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      flip_watchlist_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      flip_watchlist_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      flip_watchlist_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->flip_watchlist_length);
      if(flip_watchlist_lengthT > flip_watchlist_length)
        this->flip_watchlist = (gateway_msgs::RemoteRule*)realloc(this->flip_watchlist, flip_watchlist_lengthT * sizeof(gateway_msgs::RemoteRule));
      flip_watchlist_length = flip_watchlist_lengthT;
      for( uint32_t i = 0; i < flip_watchlist_length; i++){
      offset += this->st_flip_watchlist.deserialize(inbuffer + offset);
        memcpy( &(this->flip_watchlist[i]), &(this->st_flip_watchlist), sizeof(gateway_msgs::RemoteRule));
      }
      uint32_t flipped_in_connections_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      flipped_in_connections_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      flipped_in_connections_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      flipped_in_connections_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->flipped_in_connections_length);
      if(flipped_in_connections_lengthT > flipped_in_connections_length)
        this->flipped_in_connections = (gateway_msgs::RemoteRule*)realloc(this->flipped_in_connections, flipped_in_connections_lengthT * sizeof(gateway_msgs::RemoteRule));
      flipped_in_connections_length = flipped_in_connections_lengthT;
      for( uint32_t i = 0; i < flipped_in_connections_length; i++){
      offset += this->st_flipped_in_connections.deserialize(inbuffer + offset);
        memcpy( &(this->flipped_in_connections[i]), &(this->st_flipped_in_connections), sizeof(gateway_msgs::RemoteRule));
      }
      uint32_t pull_watchlist_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      pull_watchlist_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      pull_watchlist_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      pull_watchlist_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->pull_watchlist_length);
      if(pull_watchlist_lengthT > pull_watchlist_length)
        this->pull_watchlist = (gateway_msgs::RemoteRule*)realloc(this->pull_watchlist, pull_watchlist_lengthT * sizeof(gateway_msgs::RemoteRule));
      pull_watchlist_length = pull_watchlist_lengthT;
      for( uint32_t i = 0; i < pull_watchlist_length; i++){
      offset += this->st_pull_watchlist.deserialize(inbuffer + offset);
        memcpy( &(this->pull_watchlist[i]), &(this->st_pull_watchlist), sizeof(gateway_msgs::RemoteRule));
      }
      uint32_t pulled_connections_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      pulled_connections_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      pulled_connections_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      pulled_connections_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->pulled_connections_length);
      if(pulled_connections_lengthT > pulled_connections_length)
        this->pulled_connections = (gateway_msgs::RemoteRule*)realloc(this->pulled_connections, pulled_connections_lengthT * sizeof(gateway_msgs::RemoteRule));
      pulled_connections_length = pulled_connections_lengthT;
      for( uint32_t i = 0; i < pulled_connections_length; i++){
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