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
      uint32_t groups_length;
      typedef char* _groups_type;
      _groups_type st_groups;
      _groups_type * groups;
      typedef const char* _uri_type;
      _uri_type uri;
      typedef bool _runtime_pairing_requirements_type;
      _runtime_pairing_requirements_type runtime_pairing_requirements;

    GetInteractionsRequest():
      groups_length(0), groups(NULL),
      uri(""),
      runtime_pairing_requirements(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->groups_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->groups_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->groups_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->groups_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->groups_length);
      for( uint32_t i = 0; i < groups_length; i++){
      uint32_t length_groupsi = strlen(this->groups[i]);
      varToArr(outbuffer + offset, length_groupsi);
      offset += 4;
      memcpy(outbuffer + offset, this->groups[i], length_groupsi);
      offset += length_groupsi;
      }
      uint32_t length_uri = strlen(this->uri);
      varToArr(outbuffer + offset, length_uri);
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
      uint32_t groups_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      groups_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      groups_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      groups_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->groups_length);
      if(groups_lengthT > groups_length)
        this->groups = (char**)realloc(this->groups, groups_lengthT * sizeof(char*));
      groups_length = groups_lengthT;
      for( uint32_t i = 0; i < groups_length; i++){
      uint32_t length_st_groups;
      arrToVar(length_st_groups, (inbuffer + offset));
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
      arrToVar(length_uri, (inbuffer + offset));
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
      uint32_t interactions_length;
      typedef rocon_interaction_msgs::Interaction _interactions_type;
      _interactions_type st_interactions;
      _interactions_type * interactions;

    GetInteractionsResponse():
      interactions_length(0), interactions(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->interactions_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->interactions_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->interactions_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->interactions_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->interactions_length);
      for( uint32_t i = 0; i < interactions_length; i++){
      offset += this->interactions[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t interactions_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      interactions_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      interactions_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      interactions_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->interactions_length);
      if(interactions_lengthT > interactions_length)
        this->interactions = (rocon_interaction_msgs::Interaction*)realloc(this->interactions, interactions_lengthT * sizeof(rocon_interaction_msgs::Interaction));
      interactions_length = interactions_lengthT;
      for( uint32_t i = 0; i < interactions_length; i++){
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
