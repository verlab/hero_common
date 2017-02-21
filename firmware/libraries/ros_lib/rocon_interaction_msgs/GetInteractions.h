#ifndef _ROS_SERVICE_GetInteractions_h
#define _ROS_SERVICE_GetInteractions_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rocon_interaction_msgs/Interaction.h"

namespace rocon_interaction_msgs
{

static const char GETINTERACTIONS[] = "rocon_interaction_msgs/GetInteractions";

  class GetInteractionsRequest : public ros::Msg
  {
    public:
      uint8_t groups_length;
      char* st_groups;
      char* * groups;
      const char* uri;
      bool runtime_pairing_requirements;

    GetInteractionsRequest():
      groups_length(0), groups(NULL),
      uri(""),
      runtime_pairing_requirements(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = groups_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < groups_length; i++){
      uint32_t length_groupsi = strlen(this->groups[i]);
      memcpy(outbuffer + offset, &length_groupsi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->groups[i], length_groupsi);
      offset += length_groupsi;
      }
      uint32_t length_uri = strlen(this->uri);
      memcpy(outbuffer + offset, &length_uri, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->uri, length_uri);
      offset += length_uri;
      union {
        bool real;
        uint8_t base;
      } u_runtime_pairing_requirements;
      u_runtime_pairing_requirements.real = this->runtime_pairing_requirements;
      *(outbuffer + offset + 0) = (u_runtime_pairing_requirements.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->runtime_pairing_requirements);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t groups_lengthT = *(inbuffer + offset++);
      if(groups_lengthT > groups_length)
        this->groups = (char**)realloc(this->groups, groups_lengthT * sizeof(char*));
      offset += 3;
      groups_length = groups_lengthT;
      for( uint8_t i = 0; i < groups_length; i++){
      uint32_t length_st_groups;
      memcpy(&length_st_groups, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_groups; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_groups-1]=0;
      this->st_groups = (char *)(inbuffer + offset-1);
      offset += length_st_groups;
        memcpy( &(this->groups[i]), &(this->st_groups), sizeof(char*));
      }
      uint32_t length_uri;
      memcpy(&length_uri, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_uri; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_uri-1]=0;
      this->uri = (char *)(inbuffer + offset-1);
      offset += length_uri;
      union {
        bool real;
        uint8_t base;
      } u_runtime_pairing_requirements;
      u_runtime_pairing_requirements.base = 0;
      u_runtime_pairing_requirements.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->runtime_pairing_requirements = u_runtime_pairing_requirements.real;
      offset += sizeof(this->runtime_pairing_requirements);
     return offset;
    }

    const char * getType(){ return GETINTERACTIONS; };
    const char * getMD5(){ return "c6009efeb3aefbb011e98b70f91471a0"; };

  };

  class GetInteractionsResponse : public ros::Msg
  {
    public:
      uint8_t interactions_length;
      rocon_interaction_msgs::Interaction st_interactions;
      rocon_interaction_msgs::Interaction * interactions;

    GetInteractionsResponse():
      interactions_length(0), interactions(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = interactions_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < interactions_length; i++){
      offset += this->interactions[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t interactions_lengthT = *(inbuffer + offset++);
      if(interactions_lengthT > interactions_length)
        this->interactions = (rocon_interaction_msgs::Interaction*)realloc(this->interactions, interactions_lengthT * sizeof(rocon_interaction_msgs::Interaction));
      offset += 3;
      interactions_length = interactions_lengthT;
      for( uint8_t i = 0; i < interactions_length; i++){
      offset += this->st_interactions.deserialize(inbuffer + offset);
        memcpy( &(this->interactions[i]), &(this->st_interactions), sizeof(rocon_interaction_msgs::Interaction));
      }
     return offset;
    }

    const char * getType(){ return GETINTERACTIONS; };
    const char * getMD5(){ return "e03e40b65375af79b812435c6a579126"; };

  };

  class GetInteractions {
    public:
    typedef GetInteractionsRequest Request;
    typedef GetInteractionsResponse Response;
  };

}
#endif
