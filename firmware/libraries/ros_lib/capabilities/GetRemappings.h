#ifndef _ROS_SERVICE_GetRemappings_h
#define _ROS_SERVICE_GetRemappings_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "capabilities/Remapping.h"

namespace capabilities
{

static const char GETREMAPPINGS[] = "capabilities/GetRemappings";

  class GetRemappingsRequest : public ros::Msg
  {
    public:
      typedef const char* _spec_type;
      _spec_type spec;

    GetRemappingsRequest():
      spec("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_spec = strlen(this->spec);
      varToArr(outbuffer + offset, length_spec);
      offset += 4;
      memcpy(outbuffer + offset, this->spec, length_spec);
      offset += length_spec;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_spec;
      arrToVar(length_spec, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_spec; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_spec-1]=0;
      this->spec = (char *)(inbuffer + offset-1);
      offset += length_spec;
     return offset;
    }

    const char * getType(){ return GETREMAPPINGS; };
    const char * getMD5(){ return "bf89a64acee91503026f8c35448cf63c"; };

  };

  class GetRemappingsResponse : public ros::Msg
  {
    public:
      uint32_t topics_length;
      typedef capabilities::Remapping _topics_type;
      _topics_type st_topics;
      _topics_type * topics;
      uint32_t services_length;
      typedef capabilities::Remapping _services_type;
      _services_type st_services;
      _services_type * services;
      uint32_t actions_length;
      typedef capabilities::Remapping _actions_type;
      _actions_type st_actions;
      _actions_type * actions;
      uint32_t parameters_length;
      typedef capabilities::Remapping _parameters_type;
      _parameters_type st_parameters;
      _parameters_type * parameters;

    GetRemappingsResponse():
      topics_length(0), topics(NULL),
      services_length(0), services(NULL),
      actions_length(0), actions(NULL),
      parameters_length(0), parameters(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->topics_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->topics_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->topics_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->topics_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->topics_length);
      for( uint32_t i = 0; i < topics_length; i++){
      offset += this->topics[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->services_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->services_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->services_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->services_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->services_length);
      for( uint32_t i = 0; i < services_length; i++){
      offset += this->services[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->actions_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->actions_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->actions_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->actions_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->actions_length);
      for( uint32_t i = 0; i < actions_length; i++){
      offset += this->actions[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->parameters_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->parameters_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->parameters_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->parameters_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->parameters_length);
      for( uint32_t i = 0; i < parameters_length; i++){
      offset += this->parameters[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t topics_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      topics_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      topics_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      topics_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->topics_length);
      if(topics_lengthT > topics_length)
        this->topics = (capabilities::Remapping*)realloc(this->topics, topics_lengthT * sizeof(capabilities::Remapping));
      topics_length = topics_lengthT;
      for( uint32_t i = 0; i < topics_length; i++){
      offset += this->st_topics.deserialize(inbuffer + offset);
        memcpy( &(this->topics[i]), &(this->st_topics), sizeof(capabilities::Remapping));
      }
      uint32_t services_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      services_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      services_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      services_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->services_length);
      if(services_lengthT > services_length)
        this->services = (capabilities::Remapping*)realloc(this->services, services_lengthT * sizeof(capabilities::Remapping));
      services_length = services_lengthT;
      for( uint32_t i = 0; i < services_length; i++){
      offset += this->st_services.deserialize(inbuffer + offset);
        memcpy( &(this->services[i]), &(this->st_services), sizeof(capabilities::Remapping));
      }
      uint32_t actions_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      actions_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      actions_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      actions_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->actions_length);
      if(actions_lengthT > actions_length)
        this->actions = (capabilities::Remapping*)realloc(this->actions, actions_lengthT * sizeof(capabilities::Remapping));
      actions_length = actions_lengthT;
      for( uint32_t i = 0; i < actions_length; i++){
      offset += this->st_actions.deserialize(inbuffer + offset);
        memcpy( &(this->actions[i]), &(this->st_actions), sizeof(capabilities::Remapping));
      }
      uint32_t parameters_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      parameters_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      parameters_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      parameters_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->parameters_length);
      if(parameters_lengthT > parameters_length)
        this->parameters = (capabilities::Remapping*)realloc(this->parameters, parameters_lengthT * sizeof(capabilities::Remapping));
      parameters_length = parameters_lengthT;
      for( uint32_t i = 0; i < parameters_length; i++){
      offset += this->st_parameters.deserialize(inbuffer + offset);
        memcpy( &(this->parameters[i]), &(this->st_parameters), sizeof(capabilities::Remapping));
      }
     return offset;
    }

    const char * getType(){ return GETREMAPPINGS; };
    const char * getMD5(){ return "415cd1db0ffcce80349919d43c587ff2"; };

  };

  class GetRemappings {
    public:
    typedef GetRemappingsRequest Request;
    typedef GetRemappingsResponse Response;
  };

}
#endif
