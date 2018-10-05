#ifndef _ROS_SERVICE_GetActionServers_h
#define _ROS_SERVICE_GetActionServers_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rosapi
{

static const char GETACTIONSERVERS[] = "rosapi/GetActionServers";

  class GetActionServersRequest : public ros::Msg
  {
    public:

    GetActionServersRequest()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return GETACTIONSERVERS; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetActionServersResponse : public ros::Msg
  {
    public:
      uint32_t action_servers_length;
      typedef char* _action_servers_type;
      _action_servers_type st_action_servers;
      _action_servers_type * action_servers;

    GetActionServersResponse():
      action_servers_length(0), action_servers(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->action_servers_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->action_servers_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->action_servers_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->action_servers_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->action_servers_length);
      for( uint32_t i = 0; i < action_servers_length; i++){
      uint32_t length_action_serversi = strlen(this->action_servers[i]);
      varToArr(outbuffer + offset, length_action_serversi);
      offset += 4;
      memcpy(outbuffer + offset, this->action_servers[i], length_action_serversi);
      offset += length_action_serversi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t action_servers_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      action_servers_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      action_servers_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      action_servers_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->action_servers_length);
      if(action_servers_lengthT > action_servers_length)
        this->action_servers = (char**)realloc(this->action_servers, action_servers_lengthT * sizeof(char*));
      action_servers_length = action_servers_lengthT;
      for( uint32_t i = 0; i < action_servers_length; i++){
      uint32_t length_st_action_servers;
      arrToVar(length_st_action_servers, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_action_servers; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_action_servers-1]=0;
      this->st_action_servers = (char *)(inbuffer + offset-1);
      offset += length_st_action_servers;
        memcpy( &(this->action_servers[i]), &(this->st_action_servers), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return GETACTIONSERVERS; };
    const char * getMD5(){ return "46807ba271844ac5ba4730a47556b236"; };

  };

  class GetActionServers {
    public:
    typedef GetActionServersRequest Request;
    typedef GetActionServersResponse Response;
  };

}
#endif
