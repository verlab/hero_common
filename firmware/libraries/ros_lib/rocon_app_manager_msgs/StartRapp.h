#ifndef _ROS_SERVICE_StartRapp_h
#define _ROS_SERVICE_StartRapp_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rocon_std_msgs/Remapping.h"
#include "rocon_std_msgs/KeyValue.h"

namespace rocon_app_manager_msgs
{

static const char STARTRAPP[] = "rocon_app_manager_msgs/StartRapp";

  class StartRappRequest : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;
      uint32_t remappings_length;
      typedef rocon_std_msgs::Remapping _remappings_type;
      _remappings_type st_remappings;
      _remappings_type * remappings;
      uint32_t parameters_length;
      typedef rocon_std_msgs::KeyValue _parameters_type;
      _parameters_type st_parameters;
      _parameters_type * parameters;

    StartRappRequest():
      name(""),
      remappings_length(0), remappings(NULL),
      parameters_length(0), parameters(NULL)
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
      *(outbuffer + offset + 0) = (this->remappings_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->remappings_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->remappings_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->remappings_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->remappings_length);
      for( uint32_t i = 0; i < remappings_length; i++){
      offset += this->remappings[i].serialize(outbuffer + offset);
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
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
      uint32_t remappings_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      remappings_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      remappings_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      remappings_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->remappings_length);
      if(remappings_lengthT > remappings_length)
        this->remappings = (rocon_std_msgs::Remapping*)realloc(this->remappings, remappings_lengthT * sizeof(rocon_std_msgs::Remapping));
      remappings_length = remappings_lengthT;
      for( uint32_t i = 0; i < remappings_length; i++){
      offset += this->st_remappings.deserialize(inbuffer + offset);
        memcpy( &(this->remappings[i]), &(this->st_remappings), sizeof(rocon_std_msgs::Remapping));
      }
      uint32_t parameters_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      parameters_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      parameters_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      parameters_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->parameters_length);
      if(parameters_lengthT > parameters_length)
        this->parameters = (rocon_std_msgs::KeyValue*)realloc(this->parameters, parameters_lengthT * sizeof(rocon_std_msgs::KeyValue));
      parameters_length = parameters_lengthT;
      for( uint32_t i = 0; i < parameters_length; i++){
      offset += this->st_parameters.deserialize(inbuffer + offset);
        memcpy( &(this->parameters[i]), &(this->st_parameters), sizeof(rocon_std_msgs::KeyValue));
      }
     return offset;
    }

    const char * getType(){ return STARTRAPP; };
    const char * getMD5(){ return "cb167056946b89b371dab6e226563482"; };

  };

  class StartRappResponse : public ros::Msg
  {
    public:
      typedef bool _started_type;
      _started_type started;
      typedef int32_t _error_code_type;
      _error_code_type error_code;
      typedef const char* _message_type;
      _message_type message;
      typedef const char* _application_namespace_type;
      _application_namespace_type application_namespace;

    StartRappResponse():
      started(0),
      error_code(0),
      message(""),
      application_namespace("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_started;
      u_started.real = this->started;
      *(outbuffer + offset + 0) = (u_started.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->started);
      union {
        int32_t real;
        uint32_t base;
      } u_error_code;
      u_error_code.real = this->error_code;
      *(outbuffer + offset + 0) = (u_error_code.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_error_code.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_error_code.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_error_code.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->error_code);
      uint32_t length_message = strlen(this->message);
      varToArr(outbuffer + offset, length_message);
      offset += 4;
      memcpy(outbuffer + offset, this->message, length_message);
      offset += length_message;
      uint32_t length_application_namespace = strlen(this->application_namespace);
      varToArr(outbuffer + offset, length_application_namespace);
      offset += 4;
      memcpy(outbuffer + offset, this->application_namespace, length_application_namespace);
      offset += length_application_namespace;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_started;
      u_started.base = 0;
      u_started.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->started = u_started.real;
      offset += sizeof(this->started);
      union {
        int32_t real;
        uint32_t base;
      } u_error_code;
      u_error_code.base = 0;
      u_error_code.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_error_code.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_error_code.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_error_code.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->error_code = u_error_code.real;
      offset += sizeof(this->error_code);
      uint32_t length_message;
      arrToVar(length_message, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_message-1]=0;
      this->message = (char *)(inbuffer + offset-1);
      offset += length_message;
      uint32_t length_application_namespace;
      arrToVar(length_application_namespace, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_application_namespace; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_application_namespace-1]=0;
      this->application_namespace = (char *)(inbuffer + offset-1);
      offset += length_application_namespace;
     return offset;
    }

    const char * getType(){ return STARTRAPP; };
    const char * getMD5(){ return "4e0ddce154da40da8b63b887f1d049e8"; };

  };

  class StartRapp {
    public:
    typedef StartRappRequest Request;
    typedef StartRappResponse Response;
  };

}
#endif
