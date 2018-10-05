#ifndef _ROS_SERVICE_ServiceNode_h
#define _ROS_SERVICE_ServiceNode_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rosapi
{

static const char SERVICENODE[] = "rosapi/ServiceNode";

  class ServiceNodeRequest : public ros::Msg
  {
    public:
      typedef const char* _service_type;
      _service_type service;

    ServiceNodeRequest():
      service("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_service = strlen(this->service);
      varToArr(outbuffer + offset, length_service);
      offset += 4;
      memcpy(outbuffer + offset, this->service, length_service);
      offset += length_service;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_service;
      arrToVar(length_service, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_service; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_service-1]=0;
      this->service = (char *)(inbuffer + offset-1);
      offset += length_service;
     return offset;
    }

    const char * getType(){ return SERVICENODE; };
    const char * getMD5(){ return "1cbcfa13b08f6d36710b9af8741e6112"; };

  };

  class ServiceNodeResponse : public ros::Msg
  {
    public:
      typedef const char* _node_type;
      _node_type node;

    ServiceNodeResponse():
      node("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_node = strlen(this->node);
      varToArr(outbuffer + offset, length_node);
      offset += 4;
      memcpy(outbuffer + offset, this->node, length_node);
      offset += length_node;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_node;
      arrToVar(length_node, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_node; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_node-1]=0;
      this->node = (char *)(inbuffer + offset-1);
      offset += length_node;
     return offset;
    }

    const char * getType(){ return SERVICENODE; };
    const char * getMD5(){ return "a94c40e70a4b82863e6e52ec16732447"; };

  };

  class ServiceNode {
    public:
    typedef ServiceNodeRequest Request;
    typedef ServiceNodeResponse Response;
  };

}
#endif
