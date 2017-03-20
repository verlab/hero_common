#ifndef _ROS_zeroconf_msgs_PublishedService_h
#define _ROS_zeroconf_msgs_PublishedService_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace zeroconf_msgs
{

  class PublishedService : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;
      typedef const char* _type_type;
      _type_type type;
      typedef const char* _domain_type;
      _domain_type domain;
      typedef int32_t _port_type;
      _port_type port;
      typedef const char* _description_type;
      _description_type description;

    PublishedService():
      name(""),
      type(""),
      domain(""),
      port(0),
      description("")
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
      uint32_t length_type = strlen(this->type);
      varToArr(outbuffer + offset, length_type);
      offset += 4;
      memcpy(outbuffer + offset, this->type, length_type);
      offset += length_type;
      uint32_t length_domain = strlen(this->domain);
      varToArr(outbuffer + offset, length_domain);
      offset += 4;
      memcpy(outbuffer + offset, this->domain, length_domain);
      offset += length_domain;
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
      uint32_t length_description = strlen(this->description);
      varToArr(outbuffer + offset, length_description);
      offset += 4;
      memcpy(outbuffer + offset, this->description, length_description);
      offset += length_description;
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
      uint32_t length_type;
      arrToVar(length_type, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_type-1]=0;
      this->type = (char *)(inbuffer + offset-1);
      offset += length_type;
      uint32_t length_domain;
      arrToVar(length_domain, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_domain; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_domain-1]=0;
      this->domain = (char *)(inbuffer + offset-1);
      offset += length_domain;
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
      uint32_t length_description;
      arrToVar(length_description, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_description; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_description-1]=0;
      this->description = (char *)(inbuffer + offset-1);
      offset += length_description;
     return offset;
    }

    const char * getType(){ return "zeroconf_msgs/PublishedService"; };
    const char * getMD5(){ return "a1b00555a59ffeb95091f591a6ba849a"; };

  };

}
#endif