#ifndef _ROS_SERVICE_SearchParam_h
#define _ROS_SERVICE_SearchParam_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rosapi
{

static const char SEARCHPARAM[] = "rosapi/SearchParam";

  class SearchParamRequest : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;

    SearchParamRequest():
      name("")
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
     return offset;
    }

    const char * getType(){ return SEARCHPARAM; };
    const char * getMD5(){ return "c1f3d28f1b044c871e6eff2e9fc3c667"; };

  };

  class SearchParamResponse : public ros::Msg
  {
    public:
      typedef const char* _global_name_type;
      _global_name_type global_name;

    SearchParamResponse():
      global_name("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_global_name = strlen(this->global_name);
      varToArr(outbuffer + offset, length_global_name);
      offset += 4;
      memcpy(outbuffer + offset, this->global_name, length_global_name);
      offset += length_global_name;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_global_name;
      arrToVar(length_global_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_global_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_global_name-1]=0;
      this->global_name = (char *)(inbuffer + offset-1);
      offset += length_global_name;
     return offset;
    }

    const char * getType(){ return SEARCHPARAM; };
    const char * getMD5(){ return "87c264f142c2aeca13349d90aeec0386"; };

  };

  class SearchParam {
    public:
    typedef SearchParamRequest Request;
    typedef SearchParamResponse Response;
  };

}
#endif
