#ifndef _ROS_gateway_msgs_RemoteGateway_h
#define _ROS_gateway_msgs_RemoteGateway_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "gateway_msgs/ConnectionStatistics.h"
#include "gateway_msgs/Rule.h"
#include "gateway_msgs/RemoteRule.h"

namespace gateway_msgs
{

  class RemoteGateway : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;
      typedef const char* _ip_type;
      _ip_type ip;
      typedef bool _firewall_type;
      _firewall_type firewall;
      typedef gateway_msgs::ConnectionStatistics _conn_stats_type;
      _conn_stats_type conn_stats;
      uint32_t public_interface_length;
      typedef gateway_msgs::Rule _public_interface_type;
      _public_interface_type st_public_interface;
      _public_interface_type * public_interface;
      uint32_t flipped_interface_length;
      typedef gateway_msgs::RemoteRule _flipped_interface_type;
      _flipped_interface_type st_flipped_interface;
      _flipped_interface_type * flipped_interface;
      uint32_t pulled_interface_length;
      typedef gateway_msgs::RemoteRule _pulled_interface_type;
      _pulled_interface_type st_pulled_interface;
      _pulled_interface_type * pulled_interface;
      enum { WIRED =  1 };
      enum { WIRELESS =  2 };

    RemoteGateway():
      name(""),
      ip(""),
      firewall(0),
      conn_stats(),
      public_interface_length(0), public_interface(NULL),
      flipped_interface_length(0), flipped_interface(NULL),
      pulled_interface_length(0), pulled_interface(NULL)
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
      uint32_t length_ip = strlen(this->ip);
      varToArr(outbuffer + offset, length_ip);
      offset += 4;
      memcpy(outbuffer + offset, this->ip, length_ip);
      offset += length_ip;
      union {
        bool real;
        uint8_t base;
      } u_firewall;
      u_firewall.real = this->firewall;
      *(outbuffer + offset + 0) = (u_firewall.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->firewall);
      offset += this->conn_stats.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->public_interface_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->public_interface_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->public_interface_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->public_interface_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->public_interface_length);
      for( uint32_t i = 0; i < public_interface_length; i++){
      offset += this->public_interface[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->flipped_interface_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->flipped_interface_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->flipped_interface_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->flipped_interface_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->flipped_interface_length);
      for( uint32_t i = 0; i < flipped_interface_length; i++){
      offset += this->flipped_interface[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->pulled_interface_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->pulled_interface_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->pulled_interface_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->pulled_interface_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pulled_interface_length);
      for( uint32_t i = 0; i < pulled_interface_length; i++){
      offset += this->pulled_interface[i].serialize(outbuffer + offset);
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
      uint32_t length_ip;
      arrToVar(length_ip, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_ip; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_ip-1]=0;
      this->ip = (char *)(inbuffer + offset-1);
      offset += length_ip;
      union {
        bool real;
        uint8_t base;
      } u_firewall;
      u_firewall.base = 0;
      u_firewall.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->firewall = u_firewall.real;
      offset += sizeof(this->firewall);
      offset += this->conn_stats.deserialize(inbuffer + offset);
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
      uint32_t flipped_interface_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      flipped_interface_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      flipped_interface_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      flipped_interface_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->flipped_interface_length);
      if(flipped_interface_lengthT > flipped_interface_length)
        this->flipped_interface = (gateway_msgs::RemoteRule*)realloc(this->flipped_interface, flipped_interface_lengthT * sizeof(gateway_msgs::RemoteRule));
      flipped_interface_length = flipped_interface_lengthT;
      for( uint32_t i = 0; i < flipped_interface_length; i++){
      offset += this->st_flipped_interface.deserialize(inbuffer + offset);
        memcpy( &(this->flipped_interface[i]), &(this->st_flipped_interface), sizeof(gateway_msgs::RemoteRule));
      }
      uint32_t pulled_interface_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      pulled_interface_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      pulled_interface_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      pulled_interface_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->pulled_interface_length);
      if(pulled_interface_lengthT > pulled_interface_length)
        this->pulled_interface = (gateway_msgs::RemoteRule*)realloc(this->pulled_interface, pulled_interface_lengthT * sizeof(gateway_msgs::RemoteRule));
      pulled_interface_length = pulled_interface_lengthT;
      for( uint32_t i = 0; i < pulled_interface_length; i++){
      offset += this->st_pulled_interface.deserialize(inbuffer + offset);
        memcpy( &(this->pulled_interface[i]), &(this->st_pulled_interface), sizeof(gateway_msgs::RemoteRule));
      }
     return offset;
    }

    const char * getType(){ return "gateway_msgs/RemoteGateway"; };
    const char * getMD5(){ return "58607c66cd963e494a28cb3f919087f2"; };

  };

}
#endif