#ifndef _ROS_capabilities_CapabilitySpec_h
#define _ROS_capabilities_CapabilitySpec_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace capabilities
{

  class CapabilitySpec : public ros::Msg
  {
    public:
      typedef const char* _package_type;
      _package_type package;
      typedef const char* _type_type;
      _type_type type;
      typedef const char* _content_type;
      _content_type content;
      typedef const char* _default_provider_type;
      _default_provider_type default_provider;

    CapabilitySpec():
      package(""),
      type(""),
      content(""),
      default_provider("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_package = strlen(this->package);
      varToArr(outbuffer + offset, length_package);
      offset += 4;
      memcpy(outbuffer + offset, this->package, length_package);
      offset += length_package;
      uint32_t length_type = strlen(this->type);
      varToArr(outbuffer + offset, length_type);
      offset += 4;
      memcpy(outbuffer + offset, this->type, length_type);
      offset += length_type;
      uint32_t length_content = strlen(this->content);
      varToArr(outbuffer + offset, length_content);
      offset += 4;
      memcpy(outbuffer + offset, this->content, length_content);
      offset += length_content;
      uint32_t length_default_provider = strlen(this->default_provider);
      varToArr(outbuffer + offset, length_default_provider);
      offset += 4;
      memcpy(outbuffer + offset, this->default_provider, length_default_provider);
      offset += length_default_provider;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_package;
      arrToVar(length_package, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_package; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_package-1]=0;
      this->package = (char *)(inbuffer + offset-1);
      offset += length_package;
      uint32_t length_type;
      arrToVar(length_type, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_type-1]=0;
      this->type = (char *)(inbuffer + offset-1);
      offset += length_type;
      uint32_t length_content;
      arrToVar(length_content, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_content; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_content-1]=0;
      this->content = (char *)(inbuffer + offset-1);
      offset += length_content;
      uint32_t length_default_provider;
      arrToVar(length_default_provider, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_default_provider; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_default_provider-1]=0;
      this->default_provider = (char *)(inbuffer + offset-1);
      offset += length_default_provider;
     return offset;
    }

    const char * getType(){ return "capabilities/CapabilitySpec"; };
    const char * getMD5(){ return "410c606586817322b7ad85c73e4a4c9f"; };

  };

}
#endif