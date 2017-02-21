#ifndef _ROS_rocon_std_msgs_ConnectionsList_h
#define _ROS_rocon_std_msgs_ConnectionsList_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rocon_std_msgs/Connection.h"

namespace rocon_std_msgs
{

  class ConnectionsList : public ros::Msg
  {
    public:
      uint8_t connections_length;
      rocon_std_msgs::Connection st_connections;
      rocon_std_msgs::Connection * connections;

    ConnectionsList():
      connections_length(0), connections(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = connections_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < connections_length; i++){
      offset += this->connections[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t connections_lengthT = *(inbuffer + offset++);
      if(connections_lengthT > connections_length)
        this->connections = (rocon_std_msgs::Connection*)realloc(this->connections, connections_lengthT * sizeof(rocon_std_msgs::Connection));
      offset += 3;
      connections_length = connections_lengthT;
      for( uint8_t i = 0; i < connections_length; i++){
      offset += this->st_connections.deserialize(inbuffer + offset);
        memcpy( &(this->connections[i]), &(this->st_connections), sizeof(rocon_std_msgs::Connection));
      }
     return offset;
    }

    const char * getType(){ return "rocon_std_msgs/ConnectionsList"; };
    const char * getMD5(){ return "672d6ad69b684884f8fb6f4acedbd39f"; };

  };

}
#endif