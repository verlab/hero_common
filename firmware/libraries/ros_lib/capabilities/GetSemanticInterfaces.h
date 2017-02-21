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
      const char* interface;

    GetSemanticInterfacesRequest():
      interface("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_interface = strlen(this->interface);
      memcpy(outbuffer + offset, &length_interface, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->interface, length_interface);
      offset += length_interface;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_interface;
      memcpy(&length_interface, (inbuffer + offset), sizeof(uint32_t));
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
      uint8_t semantic_interfaces_length;
      char* st_semantic_interfaces;
      char* * semantic_interfaces;

    GetSemanticInterfacesResponse():
      semantic_interfaces_length(0), semantic_interfaces(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = semantic_interfaces_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < semantic_interfaces_length; i++){
      uint32_t length_semantic_interfacesi = strlen(this->semantic_interfaces[i]);
      memcpy(outbuffer + offset, &length_semantic_interfacesi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->semantic_interfaces[i], length_semantic_interfacesi);
      offset += length_semantic_interfacesi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t semantic_interfaces_lengthT = *(inbuffer + offset++);
      if(semantic_interfaces_lengthT > semantic_interfaces_length)
        this->semantic_interfaces = (char**)realloc(this->semantic_interfaces, semantic_interfaces_lengthT * sizeof(char*));
      offset += 3;
      semantic_interfaces_length = semantic_interfaces_lengthT;
      for( uint8_t i = 0; i < semantic_interfaces_length; i++){
      uint32_t length_st_semantic_interfaces;
      memcpy(&length_st_semantic_interfaces, (inbuffer + offset), sizeof(uint32_t));
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
