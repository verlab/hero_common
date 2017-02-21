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
      const char* application_namespace;
      const char* remote_controller;
      const char* rapp_status;
      rocon_app_manager_msgs::Rapp rapp;
      uint8_t published_interfaces_length;
      rocon_app_manager_msgs::PublishedInterface st_published_interfaces;
      rocon_app_manager_msgs::PublishedInterface * published_interfaces;
      uint8_t published_parameters_length;
      rocon_std_msgs::KeyValue st_published_parameters;
      rocon_std_msgs::KeyValue * published_parameters;
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
      memcpy(outbuffer + offset, &length_application_namespace, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->application_namespace, length_application_namespace);
      offset += length_application_namespace;
      uint32_t length_remote_controller = strlen(this->remote_controller);
      memcpy(outbuffer + offset, &length_remote_controller, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->remote_controller, length_remote_controller);
      offset += length_remote_controller;
      uint32_t length_rapp_status = strlen(this->rapp_status);
      memcpy(outbuffer + offset, &length_rapp_status, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->rapp_status, length_rapp_status);
      offset += length_rapp_status;
      offset += this->rapp.serialize(outbuffer + offset);
      *(outbuffer + offset++) = published_interfaces_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < published_interfaces_length; i++){
      offset += this->published_interfaces[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = published_parameters_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < published_parameters_length; i++){
      offset += this->published_parameters[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_application_namespace;
      memcpy(&length_application_namespace, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_application_namespace; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_application_namespace-1]=0;
      this->application_namespace = (char *)(inbuffer + offset-1);
      offset += length_application_namespace;
      uint32_t length_remote_controller;
      memcpy(&length_remote_controller, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_remote_controller; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_remote_controller-1]=0;
      this->remote_controller = (char *)(inbuffer + offset-1);
      offset += length_remote_controller;
      uint32_t length_rapp_status;
      memcpy(&length_rapp_status, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_rapp_status; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_rapp_status-1]=0;
      this->rapp_status = (char *)(inbuffer + offset-1);
      offset += length_rapp_status;
      offset += this->rapp.deserialize(inbuffer + offset);
      uint8_t published_interfaces_lengthT = *(inbuffer + offset++);
      if(published_interfaces_lengthT > published_interfaces_length)
        this->published_interfaces = (rocon_app_manager_msgs::PublishedInterface*)realloc(this->published_interfaces, published_interfaces_lengthT * sizeof(rocon_app_manager_msgs::PublishedInterface));
      offset += 3;
      published_interfaces_length = published_interfaces_lengthT;
      for( uint8_t i = 0; i < published_interfaces_length; i++){
      offset += this->st_published_interfaces.deserialize(inbuffer + offset);
        memcpy( &(this->published_interfaces[i]), &(this->st_published_interfaces), sizeof(rocon_app_manager_msgs::PublishedInterface));
      }
      uint8_t published_parameters_lengthT = *(inbuffer + offset++);
      if(published_parameters_lengthT > published_parameters_length)
        this->published_parameters = (rocon_std_msgs::KeyValue*)realloc(this->published_parameters, published_parameters_lengthT * sizeof(rocon_std_msgs::KeyValue));
      offset += 3;
      published_parameters_length = published_parameters_lengthT;
      for( uint8_t i = 0; i < published_parameters_length; i++){
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