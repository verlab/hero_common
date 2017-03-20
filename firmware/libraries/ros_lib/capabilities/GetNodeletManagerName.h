#ifndef _ROS_SERVICE_GetNodeletManagerName_h
#define _ROS_SERVICE_GetNodeletManagerName_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace capabilities
{

static const char GETNODELETMANAGERNAME[] = "capabilities/GetNodeletManagerName";

  class GetNodeletManagerNameRequest : public ros::Msg
  {
    public:

    GetNodeletManagerNameRequest()
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

    const char * getType(){ return GETNODELETMANAGERNAME; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetNodeletManagerNameResponse : public ros::Msg
  {
    public:
      typedef const char* _nodelet_manager_name_type;
      _nodelet_manager_name_type nodelet_manager_name;

    GetNodeletManagerNameResponse():
      nodelet_manager_name("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_nodelet_manager_name = strlen(this->nodelet_manager_name);
      varToArr(outbuffer + offset, length_nodelet_manager_name);
      offset += 4;
      memcpy(outbuffer + offset, this->nodelet_manager_name, length_nodelet_manager_name);
      offset += length_nodelet_manager_name;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_nodelet_manager_name;
      arrToVar(length_nodelet_manager_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_nodelet_manager_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_nodelet_manager_name-1]=0;
      this->nodelet_manager_name = (char *)(inbuffer + offset-1);
      offset += length_nodelet_manager_name;
     return offset;
    }

    const char * getType(){ return GETNODELETMANAGERNAME; };
    const char * getMD5(){ return "014bb50d87c6c69df1cbae3d5439041f"; };

  };

  class GetNodeletManagerName {
    public:
    typedef GetNodeletManagerNameRequest Request;
    typedef GetNodeletManagerNameResponse Response;
  };

}
#endif
