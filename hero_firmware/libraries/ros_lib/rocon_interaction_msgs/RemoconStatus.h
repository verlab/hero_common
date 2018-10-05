#ifndef _ROS_rocon_interaction_msgs_RemoconStatus_h
#define _ROS_rocon_interaction_msgs_RemoconStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rocon_std_msgs/MasterInfo.h"

namespace rocon_interaction_msgs
{

  class RemoconStatus : public ros::Msg
  {
    public:
      typedef rocon_std_msgs::MasterInfo _platform_info_type;
      _platform_info_type platform_info;
      typedef const char* _uuid_type;
      _uuid_type uuid;
      uint32_t running_interactions_length;
      typedef int32_t _running_interactions_type;
      _running_interactions_type st_running_interactions;
      _running_interactions_type * running_interactions;
      typedef const char* _version_type;
      _version_type version;

    RemoconStatus():
      platform_info(),
      uuid(""),
      running_interactions_length(0), running_interactions(NULL),
      version("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->platform_info.serialize(outbuffer + offset);
      uint32_t length_uuid = strlen(this->uuid);
      varToArr(outbuffer + offset, length_uuid);
      offset += 4;
      memcpy(outbuffer + offset, this->uuid, length_uuid);
      offset += length_uuid;
      *(outbuffer + offset + 0) = (this->running_interactions_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->running_interactions_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->running_interactions_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->running_interactions_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->running_interactions_length);
      for( uint32_t i = 0; i < running_interactions_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_running_interactionsi;
      u_running_interactionsi.real = this->running_interactions[i];
      *(outbuffer + offset + 0) = (u_running_interactionsi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_running_interactionsi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_running_interactionsi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_running_interactionsi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->running_interactions[i]);
      }
      uint32_t length_version = strlen(this->version);
      varToArr(outbuffer + offset, length_version);
      offset += 4;
      memcpy(outbuffer + offset, this->version, length_version);
      offset += length_version;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->platform_info.deserialize(inbuffer + offset);
      uint32_t length_uuid;
      arrToVar(length_uuid, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_uuid; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_uuid-1]=0;
      this->uuid = (char *)(inbuffer + offset-1);
      offset += length_uuid;
      uint32_t running_interactions_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      running_interactions_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      running_interactions_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      running_interactions_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->running_interactions_length);
      if(running_interactions_lengthT > running_interactions_length)
        this->running_interactions = (int32_t*)realloc(this->running_interactions, running_interactions_lengthT * sizeof(int32_t));
      running_interactions_length = running_interactions_lengthT;
      for( uint32_t i = 0; i < running_interactions_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_running_interactions;
      u_st_running_interactions.base = 0;
      u_st_running_interactions.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_running_interactions.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_running_interactions.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_running_interactions.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_running_interactions = u_st_running_interactions.real;
      offset += sizeof(this->st_running_interactions);
        memcpy( &(this->running_interactions[i]), &(this->st_running_interactions), sizeof(int32_t));
      }
      uint32_t length_version;
      arrToVar(length_version, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_version; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_version-1]=0;
      this->version = (char *)(inbuffer + offset-1);
      offset += length_version;
     return offset;
    }

    const char * getType(){ return "rocon_interaction_msgs/RemoconStatus"; };
    const char * getMD5(){ return "a586408ad56a017fbadae95562c0c018"; };

  };

}
#endif