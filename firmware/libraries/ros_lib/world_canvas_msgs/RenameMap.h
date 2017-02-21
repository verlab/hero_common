#ifndef _ROS_SERVICE_RenameMap_h
#define _ROS_SERVICE_RenameMap_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace world_canvas_msgs
{

static const char RENAMEMAP[] = "world_canvas_msgs/RenameMap";

  class RenameMapRequest : public ros::Msg
  {
    public:
      const char* map_id;
      const char* new_name;

    RenameMapRequest():
      map_id(""),
      new_name("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_map_id = strlen(this->map_id);
      memcpy(outbuffer + offset, &length_map_id, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->map_id, length_map_id);
      offset += length_map_id;
      uint32_t length_new_name = strlen(this->new_name);
      memcpy(outbuffer + offset, &length_new_name, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->new_name, length_new_name);
      offset += length_new_name;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_map_id;
      memcpy(&length_map_id, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_map_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_map_id-1]=0;
      this->map_id = (char *)(inbuffer + offset-1);
      offset += length_map_id;
      uint32_t length_new_name;
      memcpy(&length_new_name, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_new_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_new_name-1]=0;
      this->new_name = (char *)(inbuffer + offset-1);
      offset += length_new_name;
     return offset;
    }

    const char * getType(){ return RENAMEMAP; };
    const char * getMD5(){ return "94f4d84fa2d3173899807933af417784"; };

  };

  class RenameMapResponse : public ros::Msg
  {
    public:

    RenameMapResponse()
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

    const char * getType(){ return RENAMEMAP; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class RenameMap {
    public:
    typedef RenameMapRequest Request;
    typedef RenameMapResponse Response;
  };

}
#endif
