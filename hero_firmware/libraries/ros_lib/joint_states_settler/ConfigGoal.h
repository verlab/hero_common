#ifndef _ROS_joint_states_settler_ConfigGoal_h
#define _ROS_joint_states_settler_ConfigGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ros/duration.h"

namespace joint_states_settler
{

  class ConfigGoal : public ros::Msg
  {
    public:
      uint32_t joint_names_length;
      typedef char* _joint_names_type;
      _joint_names_type st_joint_names;
      _joint_names_type * joint_names;
      uint32_t tolerances_length;
      typedef float _tolerances_type;
      _tolerances_type st_tolerances;
      _tolerances_type * tolerances;
      typedef ros::Duration _max_step_type;
      _max_step_type max_step;
      typedef uint32_t _cache_size_type;
      _cache_size_type cache_size;

    ConfigGoal():
      joint_names_length(0), st_joint_names(), joint_names(nullptr),
      tolerances_length(0), st_tolerances(), tolerances(nullptr),
      max_step(),
      cache_size(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->joint_names_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->joint_names_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->joint_names_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->joint_names_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->joint_names_length);
      for( uint32_t i = 0; i < joint_names_length; i++){
      uint32_t length_joint_namesi = strlen(this->joint_names[i]);
      varToArr(outbuffer + offset, length_joint_namesi);
      offset += 4;
      memcpy(outbuffer + offset, this->joint_names[i], length_joint_namesi);
      offset += length_joint_namesi;
      }
      *(outbuffer + offset + 0) = (this->tolerances_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->tolerances_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->tolerances_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->tolerances_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->tolerances_length);
      for( uint32_t i = 0; i < tolerances_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->tolerances[i]);
      }
      *(outbuffer + offset + 0) = (this->max_step.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->max_step.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->max_step.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->max_step.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->max_step.sec);
      *(outbuffer + offset + 0) = (this->max_step.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->max_step.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->max_step.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->max_step.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->max_step.nsec);
      *(outbuffer + offset + 0) = (this->cache_size >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->cache_size >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->cache_size >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->cache_size >> (8 * 3)) & 0xFF;
      offset += sizeof(this->cache_size);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t joint_names_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      joint_names_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      joint_names_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      joint_names_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->joint_names_length);
      if(joint_names_lengthT > joint_names_length)
        this->joint_names = (char**)realloc(this->joint_names, joint_names_lengthT * sizeof(char*));
      joint_names_length = joint_names_lengthT;
      for( uint32_t i = 0; i < joint_names_length; i++){
      uint32_t length_st_joint_names;
      arrToVar(length_st_joint_names, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_joint_names; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_joint_names-1]=0;
      this->st_joint_names = (char *)(inbuffer + offset-1);
      offset += length_st_joint_names;
        memcpy( &(this->joint_names[i]), &(this->st_joint_names), sizeof(char*));
      }
      uint32_t tolerances_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      tolerances_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      tolerances_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      tolerances_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->tolerances_length);
      if(tolerances_lengthT > tolerances_length)
        this->tolerances = (float*)realloc(this->tolerances, tolerances_lengthT * sizeof(float));
      tolerances_length = tolerances_lengthT;
      for( uint32_t i = 0; i < tolerances_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_tolerances));
        memcpy( &(this->tolerances[i]), &(this->st_tolerances), sizeof(float));
      }
      this->max_step.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->max_step.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->max_step.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->max_step.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->max_step.sec);
      this->max_step.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->max_step.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->max_step.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->max_step.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->max_step.nsec);
      this->cache_size =  ((uint32_t) (*(inbuffer + offset)));
      this->cache_size |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->cache_size |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->cache_size |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->cache_size);
     return offset;
    }

    virtual const char * getType() override { return "joint_states_settler/ConfigGoal"; };
    virtual const char * getMD5() override { return "863b25359077f9aa231257b3d1612b63"; };

  };

}
#endif
