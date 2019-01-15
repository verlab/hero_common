#ifndef _ROS_variant_msgs_VariantType_h
#define _ROS_variant_msgs_VariantType_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace variant_msgs
{

  class VariantType : public ros::Msg
  {
    public:
      typedef const char* _md5_sum_type;
      _md5_sum_type md5_sum;
      typedef const char* _data_type_type;
      _data_type_type data_type;
      typedef const char* _definition_type;
      _definition_type definition;

    VariantType():
      md5_sum(""),
      data_type(""),
      definition("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_md5_sum = strlen(this->md5_sum);
      varToArr(outbuffer + offset, length_md5_sum);
      offset += 4;
      memcpy(outbuffer + offset, this->md5_sum, length_md5_sum);
      offset += length_md5_sum;
      uint32_t length_data_type = strlen(this->data_type);
      varToArr(outbuffer + offset, length_data_type);
      offset += 4;
      memcpy(outbuffer + offset, this->data_type, length_data_type);
      offset += length_data_type;
      uint32_t length_definition = strlen(this->definition);
      varToArr(outbuffer + offset, length_definition);
      offset += 4;
      memcpy(outbuffer + offset, this->definition, length_definition);
      offset += length_definition;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_md5_sum;
      arrToVar(length_md5_sum, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_md5_sum; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_md5_sum-1]=0;
      this->md5_sum = (char *)(inbuffer + offset-1);
      offset += length_md5_sum;
      uint32_t length_data_type;
      arrToVar(length_data_type, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_data_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_data_type-1]=0;
      this->data_type = (char *)(inbuffer + offset-1);
      offset += length_data_type;
      uint32_t length_definition;
      arrToVar(length_definition, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_definition; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_definition-1]=0;
      this->definition = (char *)(inbuffer + offset-1);
      offset += length_definition;
     return offset;
    }

    const char * getType(){ return "variant_msgs/VariantType"; };
    const char * getMD5(){ return "ea49579a10d85560b62a77e2f2f84caf"; };

  };

}
#endif