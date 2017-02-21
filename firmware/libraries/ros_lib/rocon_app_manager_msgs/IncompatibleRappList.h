#ifndef _ROS_rocon_app_manager_msgs_IncompatibleRappList_h
#define _ROS_rocon_app_manager_msgs_IncompatibleRappList_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rocon_app_manager_msgs
{

  class IncompatibleRappList : public ros::Msg
  {
    public:
      uint8_t blacklisted_rapps_length;
      char* st_blacklisted_rapps;
      char* * blacklisted_rapps;
      uint8_t non_whitelisted_rapps_length;
      char* st_non_whitelisted_rapps;
      char* * non_whitelisted_rapps;
      uint8_t platform_incompatible_rapps_length;
      char* st_platform_incompatible_rapps;
      char* * platform_incompatible_rapps;
      uint8_t capabilities_incompatible_rapps_length;
      char* st_capabilities_incompatible_rapps;
      char* * capabilities_incompatible_rapps;

    IncompatibleRappList():
      blacklisted_rapps_length(0), blacklisted_rapps(NULL),
      non_whitelisted_rapps_length(0), non_whitelisted_rapps(NULL),
      platform_incompatible_rapps_length(0), platform_incompatible_rapps(NULL),
      capabilities_incompatible_rapps_length(0), capabilities_incompatible_rapps(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = blacklisted_rapps_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < blacklisted_rapps_length; i++){
      uint32_t length_blacklisted_rappsi = strlen(this->blacklisted_rapps[i]);
      memcpy(outbuffer + offset, &length_blacklisted_rappsi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->blacklisted_rapps[i], length_blacklisted_rappsi);
      offset += length_blacklisted_rappsi;
      }
      *(outbuffer + offset++) = non_whitelisted_rapps_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < non_whitelisted_rapps_length; i++){
      uint32_t length_non_whitelisted_rappsi = strlen(this->non_whitelisted_rapps[i]);
      memcpy(outbuffer + offset, &length_non_whitelisted_rappsi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->non_whitelisted_rapps[i], length_non_whitelisted_rappsi);
      offset += length_non_whitelisted_rappsi;
      }
      *(outbuffer + offset++) = platform_incompatible_rapps_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < platform_incompatible_rapps_length; i++){
      uint32_t length_platform_incompatible_rappsi = strlen(this->platform_incompatible_rapps[i]);
      memcpy(outbuffer + offset, &length_platform_incompatible_rappsi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->platform_incompatible_rapps[i], length_platform_incompatible_rappsi);
      offset += length_platform_incompatible_rappsi;
      }
      *(outbuffer + offset++) = capabilities_incompatible_rapps_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < capabilities_incompatible_rapps_length; i++){
      uint32_t length_capabilities_incompatible_rappsi = strlen(this->capabilities_incompatible_rapps[i]);
      memcpy(outbuffer + offset, &length_capabilities_incompatible_rappsi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->capabilities_incompatible_rapps[i], length_capabilities_incompatible_rappsi);
      offset += length_capabilities_incompatible_rappsi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t blacklisted_rapps_lengthT = *(inbuffer + offset++);
      if(blacklisted_rapps_lengthT > blacklisted_rapps_length)
        this->blacklisted_rapps = (char**)realloc(this->blacklisted_rapps, blacklisted_rapps_lengthT * sizeof(char*));
      offset += 3;
      blacklisted_rapps_length = blacklisted_rapps_lengthT;
      for( uint8_t i = 0; i < blacklisted_rapps_length; i++){
      uint32_t length_st_blacklisted_rapps;
      memcpy(&length_st_blacklisted_rapps, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_blacklisted_rapps; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_blacklisted_rapps-1]=0;
      this->st_blacklisted_rapps = (char *)(inbuffer + offset-1);
      offset += length_st_blacklisted_rapps;
        memcpy( &(this->blacklisted_rapps[i]), &(this->st_blacklisted_rapps), sizeof(char*));
      }
      uint8_t non_whitelisted_rapps_lengthT = *(inbuffer + offset++);
      if(non_whitelisted_rapps_lengthT > non_whitelisted_rapps_length)
        this->non_whitelisted_rapps = (char**)realloc(this->non_whitelisted_rapps, non_whitelisted_rapps_lengthT * sizeof(char*));
      offset += 3;
      non_whitelisted_rapps_length = non_whitelisted_rapps_lengthT;
      for( uint8_t i = 0; i < non_whitelisted_rapps_length; i++){
      uint32_t length_st_non_whitelisted_rapps;
      memcpy(&length_st_non_whitelisted_rapps, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_non_whitelisted_rapps; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_non_whitelisted_rapps-1]=0;
      this->st_non_whitelisted_rapps = (char *)(inbuffer + offset-1);
      offset += length_st_non_whitelisted_rapps;
        memcpy( &(this->non_whitelisted_rapps[i]), &(this->st_non_whitelisted_rapps), sizeof(char*));
      }
      uint8_t platform_incompatible_rapps_lengthT = *(inbuffer + offset++);
      if(platform_incompatible_rapps_lengthT > platform_incompatible_rapps_length)
        this->platform_incompatible_rapps = (char**)realloc(this->platform_incompatible_rapps, platform_incompatible_rapps_lengthT * sizeof(char*));
      offset += 3;
      platform_incompatible_rapps_length = platform_incompatible_rapps_lengthT;
      for( uint8_t i = 0; i < platform_incompatible_rapps_length; i++){
      uint32_t length_st_platform_incompatible_rapps;
      memcpy(&length_st_platform_incompatible_rapps, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_platform_incompatible_rapps; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_platform_incompatible_rapps-1]=0;
      this->st_platform_incompatible_rapps = (char *)(inbuffer + offset-1);
      offset += length_st_platform_incompatible_rapps;
        memcpy( &(this->platform_incompatible_rapps[i]), &(this->st_platform_incompatible_rapps), sizeof(char*));
      }
      uint8_t capabilities_incompatible_rapps_lengthT = *(inbuffer + offset++);
      if(capabilities_incompatible_rapps_lengthT > capabilities_incompatible_rapps_length)
        this->capabilities_incompatible_rapps = (char**)realloc(this->capabilities_incompatible_rapps, capabilities_incompatible_rapps_lengthT * sizeof(char*));
      offset += 3;
      capabilities_incompatible_rapps_length = capabilities_incompatible_rapps_lengthT;
      for( uint8_t i = 0; i < capabilities_incompatible_rapps_length; i++){
      uint32_t length_st_capabilities_incompatible_rapps;
      memcpy(&length_st_capabilities_incompatible_rapps, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_capabilities_incompatible_rapps; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_capabilities_incompatible_rapps-1]=0;
      this->st_capabilities_incompatible_rapps = (char *)(inbuffer + offset-1);
      offset += length_st_capabilities_incompatible_rapps;
        memcpy( &(this->capabilities_incompatible_rapps[i]), &(this->st_capabilities_incompatible_rapps), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return "rocon_app_manager_msgs/IncompatibleRappList"; };
    const char * getMD5(){ return "f8b60bc2510b0df387f6623f3db3a079"; };

  };

}
#endif