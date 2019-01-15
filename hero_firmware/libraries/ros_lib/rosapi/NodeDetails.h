#ifndef _ROS_SERVICE_NodeDetails_h
#define _ROS_SERVICE_NodeDetails_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rosapi
{

static const char NODEDETAILS[] = "rosapi/NodeDetails";

  class NodeDetailsRequest : public ros::Msg
  {
    public:
      typedef const char* _node_type;
      _node_type node;

    NodeDetailsRequest():
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

    const char * getType(){ return NODEDETAILS; };
    const char * getMD5(){ return "a94c40e70a4b82863e6e52ec16732447"; };

  };

  class NodeDetailsResponse : public ros::Msg
  {
    public:
      uint32_t subscribing_length;
      typedef char* _subscribing_type;
      _subscribing_type st_subscribing;
      _subscribing_type * subscribing;
      uint32_t publishing_length;
      typedef char* _publishing_type;
      _publishing_type st_publishing;
      _publishing_type * publishing;
      uint32_t services_length;
      typedef char* _services_type;
      _services_type st_services;
      _services_type * services;

    NodeDetailsResponse():
      subscribing_length(0), subscribing(NULL),
      publishing_length(0), publishing(NULL),
      services_length(0), services(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->subscribing_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->subscribing_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->subscribing_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->subscribing_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->subscribing_length);
      for( uint32_t i = 0; i < subscribing_length; i++){
      uint32_t length_subscribingi = strlen(this->subscribing[i]);
      varToArr(outbuffer + offset, length_subscribingi);
      offset += 4;
      memcpy(outbuffer + offset, this->subscribing[i], length_subscribingi);
      offset += length_subscribingi;
      }
      *(outbuffer + offset + 0) = (this->publishing_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->publishing_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->publishing_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->publishing_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->publishing_length);
      for( uint32_t i = 0; i < publishing_length; i++){
      uint32_t length_publishingi = strlen(this->publishing[i]);
      varToArr(outbuffer + offset, length_publishingi);
      offset += 4;
      memcpy(outbuffer + offset, this->publishing[i], length_publishingi);
      offset += length_publishingi;
      }
      *(outbuffer + offset + 0) = (this->services_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->services_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->services_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->services_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->services_length);
      for( uint32_t i = 0; i < services_length; i++){
      uint32_t length_servicesi = strlen(this->services[i]);
      varToArr(outbuffer + offset, length_servicesi);
      offset += 4;
      memcpy(outbuffer + offset, this->services[i], length_servicesi);
      offset += length_servicesi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t subscribing_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      subscribing_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      subscribing_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      subscribing_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->subscribing_length);
      if(subscribing_lengthT > subscribing_length)
        this->subscribing = (char**)realloc(this->subscribing, subscribing_lengthT * sizeof(char*));
      subscribing_length = subscribing_lengthT;
      for( uint32_t i = 0; i < subscribing_length; i++){
      uint32_t length_st_subscribing;
      arrToVar(length_st_subscribing, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_subscribing; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_subscribing-1]=0;
      this->st_subscribing = (char *)(inbuffer + offset-1);
      offset += length_st_subscribing;
        memcpy( &(this->subscribing[i]), &(this->st_subscribing), sizeof(char*));
      }
      uint32_t publishing_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      publishing_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      publishing_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      publishing_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->publishing_length);
      if(publishing_lengthT > publishing_length)
        this->publishing = (char**)realloc(this->publishing, publishing_lengthT * sizeof(char*));
      publishing_length = publishing_lengthT;
      for( uint32_t i = 0; i < publishing_length; i++){
      uint32_t length_st_publishing;
      arrToVar(length_st_publishing, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_publishing; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_publishing-1]=0;
      this->st_publishing = (char *)(inbuffer + offset-1);
      offset += length_st_publishing;
        memcpy( &(this->publishing[i]), &(this->st_publishing), sizeof(char*));
      }
      uint32_t services_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      services_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      services_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      services_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->services_length);
      if(services_lengthT > services_length)
        this->services = (char**)realloc(this->services, services_lengthT * sizeof(char*));
      services_length = services_lengthT;
      for( uint32_t i = 0; i < services_length; i++){
      uint32_t length_st_services;
      arrToVar(length_st_services, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_services; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_services-1]=0;
      this->st_services = (char *)(inbuffer + offset-1);
      offset += length_st_services;
        memcpy( &(this->services[i]), &(this->st_services), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return NODEDETAILS; };
    const char * getMD5(){ return "3da1cb16c6ec5885ad291735b6244a48"; };

  };

  class NodeDetails {
    public:
    typedef NodeDetailsRequest Request;
    typedef NodeDetailsResponse Response;
  };

}
#endif
