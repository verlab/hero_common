#ifndef _ROS_SERVICE_GetSemanticInterfaces_h
#define _ROS_SERVICE_GetSemanticInterfaces_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace capabilities
{

static const char GETSEMANTICINTERFACES[] = "capabilities/GetSemanticInterfaces";

  class GetSemanticInterfacesRequest : public ros::Msg
  {
    public:
      typedef const char* _interface_type;
      _interface_type interface;

    GetSemanticInterfacesRequest():
      interface("")
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
     return offset;
    }

    const char * getType(){ return GETSEMANTICINTERFACES; };
    const char * getMD5(){ return "93320216b0fbc8adb649c496cbdb1617"; };

  };

  class GetSemanticInterfacesResponse : public ros::Msg
  {
    public:
      uint32_t semantic_interfaces_length;
      typedef char* _semantic_interfaces_type;
      _semantic_interfaces_type st_semantic_interfaces;
      _semantic_interfaces_type * semantic_interfaces;

    GetSemanticInterfacesResponse():
      semantic_interfaces_length(0), semantic_interfaces(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->semantic_interfaces_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->semantic_interfaces_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->semantic_interfaces_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->semantic_interfaces_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->semantic_interfaces_length);
      for( uint32_t i = 0; i < semantic_interfaces_length; i++){
      uint32_t length_semantic_interfacesi = strlen(this->semantic_interfaces[i]);
      varToArr(outbuffer + offset, length_semantic_interfacesi);
      offset += 4;
      memcpy(outbuffer + offset, this->semantic_interfaces[i], length_semantic_interfacesi);
      offset += length_semantic_interfacesi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t semantic_interfaces_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      semantic_interfaces_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      semantic_interfaces_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      semantic_interfaces_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->semantic_interfaces_length);
      if(semantic_interfaces_lengthT > semantic_interfaces_length)
        this->semantic_interfaces = (char**)realloc(this->semantic_interfaces, semantic_interfaces_lengthT * sizeof(char*));
      semantic_interfaces_length = semantic_interfaces_lengthT;
      for( uint32_t i = 0; i < semantic_interfaces_length; i++){
      uint32_t length_st_semantic_interfaces;
      arrToVar(length_st_semantic_interfaces, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_semantic_interfaces; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_semantic_interfaces-1]=0;
      this->st_semantic_interfaces = (char *)(inbuffer + offset-1);
      offset += length_st_semantic_interfaces;
        memcpy( &(this->semantic_interfaces[i]), &(this->st_semantic_interfaces), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return GETSEMANTICINTERFACES; };
    const char * getMD5(){ return "39999c138d8c9996d9ce71d837242710"; };

  };

  class GetSemanticInterfaces {
    public:
    typedef GetSemanticInterfacesRequest Request;
    typedef GetSemanticInterfacesResponse Response;
  };

}
#endif
