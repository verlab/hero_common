#ifndef _ROS_rocon_app_manager_msgs_PublicInterface_h
#define _ROS_rocon_app_manager_msgs_PublicInterface_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rocon_app_manager_msgs
{

  class PublicInterface : public ros::Msg
  {
    public:
      const char* connection_type;
      const char* data_type;
      const char* name;

    PublicInterface():
      connection_type(""),
      data_type(""),
      name("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_connection_type = strlen(this->connection_type);
      memcpy(outbuffer + offset, &length_connection_type, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->connection_type, length_connection_type);
      offset += length_connection_type;
      uint32_t length_data_type = strlen(this->data_type);
      memcpy(outbuffer + offset, &length_data_type, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->data_type, length_data_type);
      offset += length_data_type;
      uint32_t length_name = strlen(this->name);
      memcpy(outbuffer + offset, &length_name, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_connection_type;
      memcpy(&length_connection_type, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_connection_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_connection_type-1]=0;
      this->connection_type = (char *)(inbuffer + offset-1);
      offset += length_connection_type;
      uint32_t length_data_type;
      memcpy(&length_data_type, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_data_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_data_type-1]=0;
      this->data_type = (char *)(inbuffer + offset-1);
      offset += length_data_type;
      uint32_t length_name;
      memcpy(&length_name, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
     return offset;
    }

    const char * getType(){ return "rocon_app_manager_msgs/PublicInterface"; };
    const char * getMD5(){ return "894455d729ec4bb7068b1f83aa87a23c"; };

  };

}
#endif