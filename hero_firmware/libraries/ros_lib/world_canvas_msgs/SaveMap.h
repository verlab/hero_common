#ifndef _ROS_SERVICE_SaveMap_h
#define _ROS_SERVICE_SaveMap_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace world_canvas_msgs
{

static const char SAVEMAP[] = "world_canvas_msgs/SaveMap";

  class SaveMapRequest : public ros::Msg
  {
    public:
      typedef const char* _map_name_type;
      _map_name_type map_name;

    SaveMapRequest():
      map_name("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_map_name = strlen(this->map_name);
      varToArr(outbuffer + offset, length_map_name);
      offset += 4;
      memcpy(outbuffer + offset, this->map_name, length_map_name);
      offset += length_map_name;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_map_name;
      arrToVar(length_map_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_map_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_map_name-1]=0;
      this->map_name = (char *)(inbuffer + offset-1);
      offset += length_map_name;
     return offset;
    }

    const char * getType(){ return SAVEMAP; };
    const char * getMD5(){ return "25e928a2d4ff388c294895b7af935978"; };

  };

  class SaveMapResponse : public ros::Msg
  {
    public:

    SaveMapResponse()
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

    const char * getType(){ return SAVEMAP; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class SaveMap {
    public:
    typedef SaveMapRequest Request;
    typedef SaveMapResponse Response;
  };

}
#endif
