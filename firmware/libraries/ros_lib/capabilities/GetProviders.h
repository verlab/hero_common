#ifndef _ROS_SERVICE_GetProviders_h
#define _ROS_SERVICE_GetProviders_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace capabilities
{

static const char GETPROVIDERS[] = "capabilities/GetProviders";

  class GetProvidersRequest : public ros::Msg
  {
    public:
      typedef const char* _interface_type;
      _interface_type interface;
      typedef bool _include_semantic_type;
      _include_semantic_type include_semantic;

    GetProvidersRequest():
      interface(""),
      include_semantic(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_interface = strlen(this->interface);
      varToArr(outbuffer + offset, length_interface);
      offset += 4;
      memcpy(outbuffer + offset, this->interface, length_interface);
      offset += length_interface;
      union {
        bool real;
        uint8_t base;
      } u_include_semantic;
      u_include_semantic.real = this->include_semantic;
      *(outbuffer + offset + 0) = (u_include_semantic.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->include_semantic);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_interface;
      arrToVar(length_interface, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_interface; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_interface-1]=0;
      this->interface = (char *)(inbuffer + offset-1);
      offset += length_interface;
      union {
        bool real;
        uint8_t base;
      } u_include_semantic;
      u_include_semantic.base = 0;
      u_include_semantic.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->include_semantic = u_include_semantic.real;
      offset += sizeof(this->include_semantic);
     return offset;
    }

    const char * getType(){ return GETPROVIDERS; };
    const char * getMD5(){ return "ae99773830cfbf75aa47ccf9b6e5018e"; };

  };

  class GetProvidersResponse : public ros::Msg
  {
    public:
      uint32_t providers_length;
      typedef char* _providers_type;
      _providers_type st_providers;
      _providers_type * providers;
      typedef const char* _default_provider_type;
      _default_provider_type default_provider;

    GetProvidersResponse():
      providers_length(0), providers(NULL),
      default_provider("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->providers_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->providers_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->providers_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->providers_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->providers_length);
      for( uint32_t i = 0; i < providers_length; i++){
      uint32_t length_providersi = strlen(this->providers[i]);
      varToArr(outbuffer + offset, length_providersi);
      offset += 4;
      memcpy(outbuffer + offset, this->providers[i], length_providersi);
      offset += length_providersi;
      }
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
      uint32_t providers_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      providers_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      providers_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      providers_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->providers_length);
      if(providers_lengthT > providers_length)
        this->providers = (char**)realloc(this->providers, providers_lengthT * sizeof(char*));
      providers_length = providers_lengthT;
      for( uint32_t i = 0; i < providers_length; i++){
      uint32_t length_st_providers;
      arrToVar(length_st_providers, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_providers; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_providers-1]=0;
      this->st_providers = (char *)(inbuffer + offset-1);
      offset += length_st_providers;
        memcpy( &(this->providers[i]), &(this->st_providers), sizeof(char*));
      }
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

    const char * getType(){ return GETPROVIDERS; };
    const char * getMD5(){ return "f07bf2dab3c1c90f7df32f0732047bbd"; };

  };

  class GetProviders {
    public:
    typedef GetProvidersRequest Request;
    typedef GetProvidersResponse Response;
  };

}
#endif
