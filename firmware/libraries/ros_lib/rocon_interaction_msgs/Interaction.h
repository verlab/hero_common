#ifndef _ROS_rocon_interaction_msgs_Interaction_h
#define _ROS_rocon_interaction_msgs_Interaction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rocon_std_msgs/Icon.h"
#include "rocon_std_msgs/Remapping.h"

namespace rocon_interaction_msgs
{

  class Interaction : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;
      typedef const char* _command_type;
      _command_type command;
      typedef const char* _compatibility_type;
      _compatibility_type compatibility;
      typedef const char* _group_type;
      _group_type group;
      typedef const char* _description_type;
      _description_type description;
      typedef rocon_std_msgs::Icon _icon_type;
      _icon_type icon;
      typedef const char* _namespace_type;
      _namespace_type namespace;
      uint32_t remappings_length;
      typedef rocon_std_msgs::Remapping _remappings_type;
      _remappings_type st_remappings;
      _remappings_type * remappings;
      typedef const char* _parameters_type;
      _parameters_type parameters;
      typedef int32_t _max_type;
      _max_type max;
      typedef bool _bringup_pairing_type;
      _bringup_pairing_type bringup_pairing;
      typedef bool _teardown_pairing_type;
      _teardown_pairing_type teardown_pairing;
      uint32_t required_pairings_length;
      typedef char* _required_pairings_type;
      _required_pairings_type st_required_pairings;
      _required_pairings_type * required_pairings;
      typedef int32_t _hash_type;
      _hash_type hash;
      enum { UNLIMITED_INTERACTIONS =  -1 };

    Interaction():
      name(""),
      command(""),
      compatibility(""),
      group(""),
      description(""),
      icon(),
      namespace(""),
      remappings_length(0), remappings(NULL),
      parameters(""),
      max(0),
      bringup_pairing(0),
      teardown_pairing(0),
      required_pairings_length(0), required_pairings(NULL),
      hash(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      uint32_t length_command = strlen(this->command);
      varToArr(outbuffer + offset, length_command);
      offset += 4;
      memcpy(outbuffer + offset, this->command, length_command);
      offset += length_command;
      uint32_t length_compatibility = strlen(this->compatibility);
      varToArr(outbuffer + offset, length_compatibility);
      offset += 4;
      memcpy(outbuffer + offset, this->compatibility, length_compatibility);
      offset += length_compatibility;
      uint32_t length_group = strlen(this->group);
      varToArr(outbuffer + offset, length_group);
      offset += 4;
      memcpy(outbuffer + offset, this->group, length_group);
      offset += length_group;
      uint32_t length_description = strlen(this->description);
      varToArr(outbuffer + offset, length_description);
      offset += 4;
      memcpy(outbuffer + offset, this->description, length_description);
      offset += length_description;
      offset += this->icon.serialize(outbuffer + offset);
      uint32_t length_namespace = strlen(this->namespace);
      varToArr(outbuffer + offset, length_namespace);
      offset += 4;
      memcpy(outbuffer + offset, this->namespace, length_namespace);
      offset += length_namespace;
      *(outbuffer + offset + 0) = (this->remappings_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->remappings_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->remappings_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->remappings_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->remappings_length);
      for( uint32_t i = 0; i < remappings_length; i++){
      offset += this->remappings[i].serialize(outbuffer + offset);
      }
      uint32_t length_parameters = strlen(this->parameters);
      varToArr(outbuffer + offset, length_parameters);
      offset += 4;
      memcpy(outbuffer + offset, this->parameters, length_parameters);
      offset += length_parameters;
      union {
        int32_t real;
        uint32_t base;
      } u_max;
      u_max.real = this->max;
      *(outbuffer + offset + 0) = (u_max.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_max.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_max.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_max.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->max);
      union {
        bool real;
        uint8_t base;
      } u_bringup_pairing;
      u_bringup_pairing.real = this->bringup_pairing;
      *(outbuffer + offset + 0) = (u_bringup_pairing.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->bringup_pairing);
      union {
        bool real;
        uint8_t base;
      } u_teardown_pairing;
      u_teardown_pairing.real = this->teardown_pairing;
      *(outbuffer + offset + 0) = (u_teardown_pairing.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->teardown_pairing);
      *(outbuffer + offset + 0) = (this->required_pairings_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->required_pairings_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->required_pairings_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->required_pairings_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->required_pairings_length);
      for( uint32_t i = 0; i < required_pairings_length; i++){
      uint32_t length_required_pairingsi = strlen(this->required_pairings[i]);
      varToArr(outbuffer + offset, length_required_pairingsi);
      offset += 4;
      memcpy(outbuffer + offset, this->required_pairings[i], length_required_pairingsi);
      offset += length_required_pairingsi;
      }
      union {
        int32_t real;
        uint32_t base;
      } u_hash;
      u_hash.real = this->hash;
      *(outbuffer + offset + 0) = (u_hash.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_hash.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_hash.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_hash.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->hash);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
      uint32_t length_command;
      arrToVar(length_command, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_command; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_command-1]=0;
      this->command = (char *)(inbuffer + offset-1);
      offset += length_command;
      uint32_t length_compatibility;
      arrToVar(length_compatibility, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_compatibility; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_compatibility-1]=0;
      this->compatibility = (char *)(inbuffer + offset-1);
      offset += length_compatibility;
      uint32_t length_group;
      arrToVar(length_group, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_group; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_group-1]=0;
      this->group = (char *)(inbuffer + offset-1);
      offset += length_group;
      uint32_t length_description;
      arrToVar(length_description, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_description; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_description-1]=0;
      this->description = (char *)(inbuffer + offset-1);
      offset += length_description;
      offset += this->icon.deserialize(inbuffer + offset);
      uint32_t length_namespace;
      arrToVar(length_namespace, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_namespace; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_namespace-1]=0;
      this->namespace = (char *)(inbuffer + offset-1);
      offset += length_namespace;
      uint32_t remappings_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      remappings_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      remappings_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      remappings_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->remappings_length);
      if(remappings_lengthT > remappings_length)
        this->remappings = (rocon_std_msgs::Remapping*)realloc(this->remappings, remappings_lengthT * sizeof(rocon_std_msgs::Remapping));
      remappings_length = remappings_lengthT;
      for( uint32_t i = 0; i < remappings_length; i++){
      offset += this->st_remappings.deserialize(inbuffer + offset);
        memcpy( &(this->remappings[i]), &(this->st_remappings), sizeof(rocon_std_msgs::Remapping));
      }
      uint32_t length_parameters;
      arrToVar(length_parameters, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_parameters; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_parameters-1]=0;
      this->parameters = (char *)(inbuffer + offset-1);
      offset += length_parameters;
      union {
        int32_t real;
        uint32_t base;
      } u_max;
      u_max.base = 0;
      u_max.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_max.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_max.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_max.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->max = u_max.real;
      offset += sizeof(this->max);
      union {
        bool real;
        uint8_t base;
      } u_bringup_pairing;
      u_bringup_pairing.base = 0;
      u_bringup_pairing.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->bringup_pairing = u_bringup_pairing.real;
      offset += sizeof(this->bringup_pairing);
      union {
        bool real;
        uint8_t base;
      } u_teardown_pairing;
      u_teardown_pairing.base = 0;
      u_teardown_pairing.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->teardown_pairing = u_teardown_pairing.real;
      offset += sizeof(this->teardown_pairing);
      uint32_t required_pairings_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      required_pairings_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      required_pairings_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      required_pairings_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->required_pairings_length);
      if(required_pairings_lengthT > required_pairings_length)
        this->required_pairings = (char**)realloc(this->required_pairings, required_pairings_lengthT * sizeof(char*));
      required_pairings_length = required_pairings_lengthT;
      for( uint32_t i = 0; i < required_pairings_length; i++){
      uint32_t length_st_required_pairings;
      arrToVar(length_st_required_pairings, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_required_pairings; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_required_pairings-1]=0;
      this->st_required_pairings = (char *)(inbuffer + offset-1);
      offset += length_st_required_pairings;
        memcpy( &(this->required_pairings[i]), &(this->st_required_pairings), sizeof(char*));
      }
      union {
        int32_t real;
        uint32_t base;
      } u_hash;
      u_hash.base = 0;
      u_hash.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_hash.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_hash.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_hash.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->hash = u_hash.real;
      offset += sizeof(this->hash);
     return offset;
    }

    const char * getType(){ return "rocon_interaction_msgs/Interaction"; };
    const char * getMD5(){ return "a118201d77d4921a4dbca2d7a413a812"; };

  };

}
#endif