#ifndef _ROS_controller_manager_msgs_ControllerState_h
#define _ROS_controller_manager_msgs_ControllerState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "controller_manager_msgs/HardwareInterfaceResources.h"

namespace controller_manager_msgs
{

  class ControllerState : public ros::Msg
  {
    public:
      const char* name;
      const char* state;
      const char* type;
      uint8_t claimed_resources_length;
      controller_manager_msgs::HardwareInterfaceResources st_claimed_resources;
      controller_manager_msgs::HardwareInterfaceResources * claimed_resources;

    ControllerState():
      name(""),
      state(""),
      type(""),
      claimed_resources_length(0), claimed_resources(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_name = strlen(this->name);
      memcpy(outbuffer + offset, &length_name, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      uint32_t length_state = strlen(this->state);
      memcpy(outbuffer + offset, &length_state, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->state, length_state);
      offset += length_state;
      uint32_t length_type = strlen(this->type);
      memcpy(outbuffer + offset, &length_type, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->type, length_type);
      offset += length_type;
      *(outbuffer + offset++) = claimed_resources_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < claimed_resources_length; i++){
      offset += this->claimed_resources[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_name;
      memcpy(&length_name, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
      uint32_t length_state;
      memcpy(&length_state, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_state; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_state-1]=0;
      this->state = (char *)(inbuffer + offset-1);
      offset += length_state;
      uint32_t length_type;
      memcpy(&length_type, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_type-1]=0;
      this->type = (char *)(inbuffer + offset-1);
      offset += length_type;
      uint8_t claimed_resources_lengthT = *(inbuffer + offset++);
      if(claimed_resources_lengthT > claimed_resources_length)
        this->claimed_resources = (controller_manager_msgs::HardwareInterfaceResources*)realloc(this->claimed_resources, claimed_resources_lengthT * sizeof(controller_manager_msgs::HardwareInterfaceResources));
      offset += 3;
      claimed_resources_length = claimed_resources_lengthT;
      for( uint8_t i = 0; i < claimed_resources_length; i++){
      offset += this->st_claimed_resources.deserialize(inbuffer + offset);
        memcpy( &(this->claimed_resources[i]), &(this->st_claimed_resources), sizeof(controller_manager_msgs::HardwareInterfaceResources));
      }
     return offset;
    }

    const char * getType(){ return "controller_manager_msgs/ControllerState"; };
    const char * getMD5(){ return "aeb6b261d97793ab74099a3740245272"; };

  };

}
#endif