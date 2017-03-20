#ifndef _ROS_rocon_app_manager_msgs_Status_h
#define _ROS_rocon_app_manager_msgs_Status_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rocon_app_manager_msgs/Rapp.h"
#include "rocon_app_manager_msgs/PublishedInterface.h"
#include "rocon_std_msgs/KeyValue.h"

namespace rocon_app_manager_msgs
{

  class Status : public ros::Msg
  {
    public:
      typedef const char* _application_namespace_type;
      _application_namespace_type application_namespace;
      typedef const char* _remote_controller_type;
      _remote_controller_type remote_controller;
      typedef const char* _rapp_status_type;
      _rapp_status_type rapp_status;
      typedef rocon_app_manager_msgs::Rapp _rapp_type;
      _rapp_type rapp;
      uint32_t published_interfaces_length;
      typedef rocon_app_manager_msgs::PublishedInterface _published_interfaces_type;
      _published_interfaces_type st_published_interfaces;
      _published_interfaces_type * published_interfaces;
      uint32_t published_parameters_length;
      typedef rocon_std_msgs::KeyValue _published_parameters_type;
      _published_parameters_type st_published_parameters;
      _published_parameters_type * published_parameters;
      enum { RAPP_STOPPED = stopped };
      enum { RAPP_RUNNING = running };

    Status():
      application_namespace(""),
      remote_controller(""),
      rapp_status(""),
      rapp(),
      published_interfaces_length(0), published_interfaces(NULL),
      published_parameters_length(0), published_parameters(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_application_namespace = strlen(this->application_namespace);
      varToArr(outbuffer + offset, length_application_namespace);
      offset += 4;
      memcpy(outbuffer + offset, this->application_namespace, length_application_namespace);
      offset += length_application_namespace;
      uint32_t length_remote_controller = strlen(this->remote_controller);
      varToArr(outbuffer + offset, length_remote_controller);
      offset += 4;
      memcpy(outbuffer + offset, this->remote_controller, length_remote_controller);
      offset += length_remote_controller;
      uint32_t length_rapp_status = strlen(this->rapp_status);
      varToArr(outbuffer + offset, length_rapp_status);
      offset += 4;
      memcpy(outbuffer + offset, this->rapp_status, length_rapp_status);
      offset += length_rapp_status;
      offset += this->rapp.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->published_interfaces_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->published_interfaces_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->published_interfaces_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->published_interfaces_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->published_interfaces_length);
      for( uint32_t i = 0; i < published_interfaces_length; i++){
      offset += this->published_interfaces[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->published_parameters_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->published_parameters_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->published_parameters_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->published_parameters_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->published_parameters_length);
      for( uint32_t i = 0; i < published_parameters_length; i++){
      offset += this->published_parameters[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_application_namespace;
      arrToVar(length_application_namespace, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_application_namespace; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_application_namespace-1]=0;
      this->application_namespace = (char *)(inbuffer + offset-1);
      offset += length_application_namespace;
      uint32_t length_remote_controller;
      arrToVar(length_remote_controller, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_remote_controller; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_remote_controller-1]=0;
      this->remote_controller = (char *)(inbuffer + offset-1);
      offset += length_remote_controller;
      uint32_t length_rapp_status;
      arrToVar(length_rapp_status, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_rapp_status; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_rapp_status-1]=0;
      this->rapp_status = (char *)(inbuffer + offset-1);
      offset += length_rapp_status;
      offset += this->rapp.deserialize(inbuffer + offset);
      uint32_t published_interfaces_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      published_interfaces_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      published_interfaces_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      published_interfaces_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->published_interfaces_length);
      if(published_interfaces_lengthT > published_interfaces_length)
        this->published_interfaces = (rocon_app_manager_msgs::PublishedInterface*)realloc(this->published_interfaces, published_interfaces_lengthT * sizeof(rocon_app_manager_msgs::PublishedInterface));
      published_interfaces_length = published_interfaces_lengthT;
      for( uint32_t i = 0; i < published_interfaces_length; i++){
      offset += this->st_published_interfaces.deserialize(inbuffer + offset);
        memcpy( &(this->published_interfaces[i]), &(this->st_published_interfaces), sizeof(rocon_app_manager_msgs::PublishedInterface));
      }
      uint32_t published_parameters_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      published_parameters_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      published_parameters_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      published_parameters_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->published_parameters_length);
      if(published_parameters_lengthT > published_parameters_length)
        this->published_parameters = (rocon_std_msgs::KeyValue*)realloc(this->published_parameters, published_parameters_lengthT * sizeof(rocon_std_msgs::KeyValue));
      published_parameters_length = published_parameters_lengthT;
      for( uint32_t i = 0; i < published_parameters_length; i++){
      offset += this->st_published_parameters.deserialize(inbuffer + offset);
        memcpy( &(this->published_parameters[i]), &(this->st_published_parameters), sizeof(rocon_std_msgs::KeyValue));
      }
     return offset;
    }

    const char * getType(){ return "rocon_app_manager_msgs/Status"; };
    const char * getMD5(){ return "845a2087bbeabf6770c4fda9fcc80442"; };

  };

}
#endif