#ifndef _ROS_SERVICE_LoadMap_h
#define _ROS_SERVICE_LoadMap_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace stdr_msgs
{

static const char LOADMAP[] = "stdr_msgs/LoadMap";

  class LoadMapRequest : public ros::Msg
  {
    public:
      typedef const char* _mapFile_type;
      _mapFile_type mapFile;

    LoadMapRequest():
      mapFile("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_mapFile = strlen(this->mapFile);
      varToArr(outbuffer + offset, length_mapFile);
      offset += 4;
      memcpy(outbuffer + offset, this->mapFile, length_mapFile);
      offset += length_mapFile;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_mapFile;
      arrToVar(length_mapFile, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_mapFile; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_mapFile-1]=0;
      this->mapFile = (char *)(inbuffer + offset-1);
      offset += length_mapFile;
     return offset;
    }

    const char * getType(){ return LOADMAP; };
    const char * getMD5(){ return "656f50b5e78328d62ac1c4a5c19fefd5"; };

  };

  class LoadMapResponse : public ros::Msg
  {
    public:

    LoadMapResponse()
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

    const char * getType(){ return LOADMAP; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class LoadMap {
    public:
    typedef LoadMapRequest Request;
    typedef LoadMapResponse Response;
  };

}
#endif
