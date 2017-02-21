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
      uint8_t idle_clients_length;
      rocon_interaction_msgs::InteractiveClient st_idle_clients;
      rocon_interaction_msgs::InteractiveClient * idle_clients;
      uint8_t running_clients_length;
      rocon_interaction_msgs::InteractiveClient st_running_clients;
      rocon_interaction_msgs::InteractiveClient * running_clients;

    InteractiveClients():
      idle_clients_length(0), idle_clients(NULL),
      running_clients_length(0), running_clients(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = idle_clients_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < idle_clients_length; i++){
      offset += this->idle_clients[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = running_clients_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < running_clients_length; i++){
      offset += this->running_clients[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t idle_clients_lengthT = *(inbuffer + offset++);
      if(idle_clients_lengthT > idle_clients_length)
        this->idle_clients = (rocon_interaction_msgs::InteractiveClient*)realloc(this->idle_clients, idle_clients_lengthT * sizeof(rocon_interaction_msgs::InteractiveClient));
      offset += 3;
      idle_clients_length = idle_clients_lengthT;
      for( uint8_t i = 0; i < idle_clients_length; i++){
      offset += this->st_idle_clients.deserialize(inbuffer + offset);
        memcpy( &(this->idle_clients[i]), &(this->st_idle_clients), sizeof(rocon_interaction_msgs::InteractiveClient));
      }
      uint8_t running_clients_lengthT = *(inbuffer + offset++);
      if(running_clients_lengthT > running_clients_length)
        this->running_clients = (rocon_interaction_msgs::InteractiveClient*)realloc(this->running_clients, running_clients_lengthT * sizeof(rocon_interaction_msgs::InteractiveClient));
      offset += 3;
      running_clients_length = running_clients_lengthT;
      for( uint8_t i = 0; i < running_clients_length; i++){
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