#ifndef _ROS_controller_manager_msgs_HardwareInterfaceResources_h
#define _ROS_controller_manager_msgs_HardwareInterfaceResources_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace controller_manager_msgs
{

  class HardwareInterfaceResources : public ros::Msg
  {
    public:
      const char* hardware_interface;
      uint8_t resources_length;
      char* st_resources;
      char* * resources;

    HardwareInterfaceResources():
      hardware_interface(""),
      resources_length(0), resources(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_hardware_interface = strlen(this->hardware_interface);
      memcpy(outbuffer + offset, &length_hardware_interface, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->hardware_interface, length_hardware_interface);
      offset += length_hardware_interface;
      *(outbuffer + offset++) = resources_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < resources_length; i++){
      uint32_t length_resourcesi = strlen(this->resources[i]);
      memcpy(outbuffer + offset, &length_resourcesi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->resources[i], length_resourcesi);
      offset += length_resourcesi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_hardware_interface;
      memcpy(&length_hardware_interface, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_hardware_interface; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_hardware_interface-1]=0;
      this->hardware_interface = (char *)(inbuffer + offset-1);
      offset += length_hardware_interface;
      uint8_t resources_lengthT = *(inbuffer + offset++);
      if(resources_lengthT > resources_length)
        this->resources = (char**)realloc(this->resources, resources_lengthT * sizeof(char*));
      offset += 3;
      resources_length = resources_lengthT;
      for( uint8_t i = 0; i < resources_length; i++){
      uint32_t length_st_resources;
      memcpy(&length_st_resources, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_resources; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_resources-1]=0;
      this->st_resources = (char *)(inbuffer + offset-1);
      offset += length_st_resources;
        memcpy( &(this->resources[i]), &(this->st_resources), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return "controller_manager_msgs/HardwareInterfaceResources"; };
    const char * getMD5(){ return "f25b55cbf1d1f76e82e5ec9e83f76258"; };

  };

}
#endif