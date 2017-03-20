#ifndef _ROS_rocon_interaction_msgs_InteractiveClients_h
#define _ROS_rocon_interaction_msgs_InteractiveClients_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rocon_interaction_msgs/InteractiveClient.h"

namespace rocon_interaction_msgs
{

  class InteractiveClients : public ros::Msg
  {
    public:
      uint32_t idle_clients_length;
      typedef rocon_interaction_msgs::InteractiveClient _idle_clients_type;
      _idle_clients_type st_idle_clients;
      _idle_clients_type * idle_clients;
      uint32_t running_clients_length;
      typedef rocon_interaction_msgs::InteractiveClient _running_clients_type;
      _running_clients_type st_running_clients;
      _running_clients_type * running_clients;

    InteractiveClients():
      idle_clients_length(0), idle_clients(NULL),
      running_clients_length(0), running_clients(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->idle_clients_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->idle_clients_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->idle_clients_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->idle_clients_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->idle_clients_length);
      for( uint32_t i = 0; i < idle_clients_length; i++){
      offset += this->idle_clients[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->running_clients_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->running_clients_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->running_clients_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->running_clients_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->running_clients_length);
      for( uint32_t i = 0; i < running_clients_length; i++){
      offset += this->running_clients[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t idle_clients_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      idle_clients_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      idle_clients_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      idle_clients_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->idle_clients_length);
      if(idle_clients_lengthT > idle_clients_length)
        this->idle_clients = (rocon_interaction_msgs::InteractiveClient*)realloc(this->idle_clients, idle_clients_lengthT * sizeof(rocon_interaction_msgs::InteractiveClient));
      idle_clients_length = idle_clients_lengthT;
      for( uint32_t i = 0; i < idle_clients_length; i++){
      offset += this->st_idle_clients.deserialize(inbuffer + offset);
        memcpy( &(this->idle_clients[i]), &(this->st_idle_clients), sizeof(rocon_interaction_msgs::InteractiveClient));
      }
      uint32_t running_clients_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      running_clients_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      running_clients_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      running_clients_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->running_clients_length);
      if(running_clients_lengthT > running_clients_length)
        this->running_clients = (rocon_interaction_msgs::InteractiveClient*)realloc(this->running_clients, running_clients_lengthT * sizeof(rocon_interaction_msgs::InteractiveClient));
      running_clients_length = running_clients_lengthT;
      for( uint32_t i = 0; i < running_clients_length; i++){
      offset += this->st_running_clients.deserialize(inbuffer + offset);
        memcpy( &(this->running_clients[i]), &(this->st_running_clients), sizeof(rocon_interaction_msgs::InteractiveClient));
      }
     return offset;
    }

    const char * getType(){ return "rocon_interaction_msgs/InteractiveClients"; };
    const char * getMD5(){ return "5a5f85c169f63b30c61759b0bcca81c4"; };

  };

}
#endif