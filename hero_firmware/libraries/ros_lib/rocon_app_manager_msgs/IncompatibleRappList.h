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
      uint32_t blacklisted_rapps_length;
      typedef char* _blacklisted_rapps_type;
      _blacklisted_rapps_type st_blacklisted_rapps;
      _blacklisted_rapps_type * blacklisted_rapps;
      uint32_t non_whitelisted_rapps_length;
      typedef char* _non_whitelisted_rapps_type;
      _non_whitelisted_rapps_type st_non_whitelisted_rapps;
      _non_whitelisted_rapps_type * non_whitelisted_rapps;
      uint32_t platform_incompatible_rapps_length;
      typedef char* _platform_incompatible_rapps_type;
      _platform_incompatible_rapps_type st_platform_incompatible_rapps;
      _platform_incompatible_rapps_type * platform_incompatible_rapps;
      uint32_t capabilities_incompatible_rapps_length;
      typedef char* _capabilities_incompatible_rapps_type;
      _capabilities_incompatible_rapps_type st_capabilities_incompatible_rapps;
      _capabilities_incompatible_rapps_type * capabilities_incompatible_rapps;

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
      *(outbuffer + offset + 0) = (this->blacklisted_rapps_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->blacklisted_rapps_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->blacklisted_rapps_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->blacklisted_rapps_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->blacklisted_rapps_length);
      for( uint32_t i = 0; i < blacklisted_rapps_length; i++){
      uint32_t length_blacklisted_rappsi = strlen(this->blacklisted_rapps[i]);
      varToArr(outbuffer + offset, length_blacklisted_rappsi);
      offset += 4;
      memcpy(outbuffer + offset, this->blacklisted_rapps[i], length_blacklisted_rappsi);
      offset += length_blacklisted_rappsi;
      }
      *(outbuffer + offset + 0) = (this->non_whitelisted_rapps_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->non_whitelisted_rapps_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->non_whitelisted_rapps_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->non_whitelisted_rapps_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->non_whitelisted_rapps_length);
      for( uint32_t i = 0; i < non_whitelisted_rapps_length; i++){
      uint32_t length_non_whitelisted_rappsi = strlen(this->non_whitelisted_rapps[i]);
      varToArr(outbuffer + offset, length_non_whitelisted_rappsi);
      offset += 4;
      memcpy(outbuffer + offset, this->non_whitelisted_rapps[i], length_non_whitelisted_rappsi);
      offset += length_non_whitelisted_rappsi;
      }
      *(outbuffer + offset + 0) = (this->platform_incompatible_rapps_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->platform_incompatible_rapps_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->platform_incompatible_rapps_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->platform_incompatible_rapps_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->platform_incompatible_rapps_length);
      for( uint32_t i = 0; i < platform_incompatible_rapps_length; i++){
      uint32_t length_platform_incompatible_rappsi = strlen(this->platform_incompatible_rapps[i]);
      varToArr(outbuffer + offset, length_platform_incompatible_rappsi);
      offset += 4;
      memcpy(outbuffer + offset, this->platform_incompatible_rapps[i], length_platform_incompatible_rappsi);
      offset += length_platform_incompatible_rappsi;
      }
      *(outbuffer + offset + 0) = (this->capabilities_incompatible_rapps_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->capabilities_incompatible_rapps_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->capabilities_incompatible_rapps_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->capabilities_incompatible_rapps_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->capabilities_incompatible_rapps_length);
      for( uint32_t i = 0; i < capabilities_incompatible_rapps_length; i++){
      uint32_t length_capabilities_incompatible_rappsi = strlen(this->capabilities_incompatible_rapps[i]);
      varToArr(outbuffer + offset, length_capabilities_incompatible_rappsi);
      offset += 4;
      memcpy(outbuffer + offset, this->capabilities_incompatible_rapps[i], length_capabilities_incompatible_rappsi);
      offset += length_capabilities_incompatible_rappsi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t blacklisted_rapps_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      blacklisted_rapps_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      blacklisted_rapps_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      blacklisted_rapps_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->blacklisted_rapps_length);
      if(blacklisted_rapps_lengthT > blacklisted_rapps_length)
        this->blacklisted_rapps = (char**)realloc(this->blacklisted_rapps, blacklisted_rapps_lengthT * sizeof(char*));
      blacklisted_rapps_length = blacklisted_rapps_lengthT;
      for( uint32_t i = 0; i < blacklisted_rapps_length; i++){
      uint32_t length_st_blacklisted_rapps;
      arrToVar(length_st_blacklisted_rapps, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_blacklisted_rapps; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_blacklisted_rapps-1]=0;
      this->st_blacklisted_rapps = (char *)(inbuffer + offset-1);
      offset += length_st_blacklisted_rapps;
        memcpy( &(this->blacklisted_rapps[i]), &(this->st_blacklisted_rapps), sizeof(char*));
      }
      uint32_t non_whitelisted_rapps_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      non_whitelisted_rapps_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      non_whitelisted_rapps_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      non_whitelisted_rapps_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->non_whitelisted_rapps_length);
      if(non_whitelisted_rapps_lengthT > non_whitelisted_rapps_length)
        this->non_whitelisted_rapps = (char**)realloc(this->non_whitelisted_rapps, non_whitelisted_rapps_lengthT * sizeof(char*));
      non_whitelisted_rapps_length = non_whitelisted_rapps_lengthT;
      for( uint32_t i = 0; i < non_whitelisted_rapps_length; i++){
      uint32_t length_st_non_whitelisted_rapps;
      arrToVar(length_st_non_whitelisted_rapps, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_non_whitelisted_rapps; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_non_whitelisted_rapps-1]=0;
      this->st_non_whitelisted_rapps = (char *)(inbuffer + offset-1);
      offset += length_st_non_whitelisted_rapps;
        memcpy( &(this->non_whitelisted_rapps[i]), &(this->st_non_whitelisted_rapps), sizeof(char*));
      }
      uint32_t platform_incompatible_rapps_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      platform_incompatible_rapps_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      platform_incompatible_rapps_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      platform_incompatible_rapps_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->platform_incompatible_rapps_length);
      if(platform_incompatible_rapps_lengthT > platform_incompatible_rapps_length)
        this->platform_incompatible_rapps = (char**)realloc(this->platform_incompatible_rapps, platform_incompatible_rapps_lengthT * sizeof(char*));
      platform_incompatible_rapps_length = platform_incompatible_rapps_lengthT;
      for( uint32_t i = 0; i < platform_incompatible_rapps_length; i++){
      uint32_t length_st_platform_incompatible_rapps;
      arrToVar(length_st_platform_incompatible_rapps, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_platform_incompatible_rapps; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_platform_incompatible_rapps-1]=0;
      this->st_platform_incompatible_rapps = (char *)(inbuffer + offset-1);
      offset += length_st_platform_incompatible_rapps;
        memcpy( &(this->platform_incompatible_rapps[i]), &(this->st_platform_incompatible_rapps), sizeof(char*));
      }
      uint32_t capabilities_incompatible_rapps_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      capabilities_incompatible_rapps_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      capabilities_incompatible_rapps_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      capabilities_incompatible_rapps_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->capabilities_incompatible_rapps_length);
      if(capabilities_incompatible_rapps_lengthT > capabilities_incompatible_rapps_length)
        this->capabilities_incompatible_rapps = (char**)realloc(this->capabilities_incompatible_rapps, capabilities_incompatible_rapps_lengthT * sizeof(char*));
      capabilities_incompatible_rapps_length = capabilities_incompatible_rapps_lengthT;
      for( uint32_t i = 0; i < capabilities_incompatible_rapps_length; i++){
      uint32_t length_st_capabilities_incompatible_rapps;
      arrToVar(length_st_capabilities_incompatible_rapps, (inbuffer + offset));
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