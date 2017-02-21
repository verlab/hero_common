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
      const char* spec;

    GetRemappingsRequest():
      spec("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_spec = strlen(this->spec);
      memcpy(outbuffer + offset, &length_spec, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->spec, length_spec);
      offset += length_spec;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_spec;
      memcpy(&length_spec, (inbuffer + offset), sizeof(uint32_t));
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
      uint8_t topics_length;
      capabilities::Remapping st_topics;
      capabilities::Remapping * topics;
      uint8_t services_length;
      capabilities::Remapping st_services;
      capabilities::Remapping * services;
      uint8_t actions_length;
      capabilities::Remapping st_actions;
      capabilities::Remapping * actions;
      uint8_t parameters_length;
      capabilities::Remapping st_parameters;
      capabilities::Remapping * parameters;

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
      *(outbuffer + offset++) = topics_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < topics_length; i++){
      offset += this->topics[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = services_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < services_length; i++){
      offset += this->services[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = actions_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < actions_length; i++){
      offset += this->actions[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = parameters_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < parameters_length; i++){
      offset += this->parameters[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t topics_lengthT = *(inbuffer + offset++);
      if(topics_lengthT > topics_length)
        this->topics = (capabilities::Remapping*)realloc(this->topics, topics_lengthT * sizeof(capabilities::Remapping));
      offset += 3;
      topics_length = topics_lengthT;
      for( uint8_t i = 0; i < topics_length; i++){
      offset += this->st_topics.deserialize(inbuffer + offset);
        memcpy( &(this->topics[i]), &(this->st_topics), sizeof(capabilities::Remapping));
      }
      uint8_t services_lengthT = *(inbuffer + offset++);
      if(services_lengthT > services_length)
        this->services = (capabilities::Remapping*)realloc(this->services, services_lengthT * sizeof(capabilities::Remapping));
      offset += 3;
      services_length = services_lengthT;
      for( uint8_t i = 0; i < services_length; i++){
      offset += this->st_services.deserialize(inbuffer + offset);
        memcpy( &(this->services[i]), &(this->st_services), sizeof(capabilities::Remapping));
      }
      uint8_t actions_lengthT = *(inbuffer + offset++);
      if(actions_lengthT > actions_length)
        this->actions = (capabilities::Remapping*)realloc(this->actions, actions_lengthT * sizeof(capabilities::Remapping));
      offset += 3;
      actions_length = actions_lengthT;
      for( uint8_t i = 0; i < actions_length; i++){
      offset += this->st_actions.deserialize(inbuffer + offset);
        memcpy( &(this->actions[i]), &(this->st_actions), sizeof(capabilities::Remapping));
      }
      uint8_t parameters_lengthT = *(inbuffer + offset++);
      if(parameters_lengthT > parameters_length)
        this->parameters = (capabilities::Remapping*)realloc(this->parameters, parameters_lengthT * sizeof(capabilities::Remapping));
      offset += 3;
      parameters_length = parameters_lengthT;
      for( uint8_t i = 0; i < parameters_length; i++){
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
