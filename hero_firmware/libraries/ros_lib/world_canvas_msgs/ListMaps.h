#ifndef _ROS_SERVICE_ListMaps_h
#define _ROS_SERVICE_ListMaps_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "world_canvas_msgs/MapListEntry.h"

namespace world_canvas_msgs
{

static const char LISTMAPS[] = "world_canvas_msgs/ListMaps";

  class ListMapsRequest : public ros::Msg
  {
    public:

    ListMapsRequest()
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

    const char * getType(){ return LISTMAPS; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class ListMapsResponse : public ros::Msg
  {
    public:
      uint32_t map_list_length;
      typedef world_canvas_msgs::MapListEntry _map_list_type;
      _map_list_type st_map_list;
      _map_list_type * map_list;

    ListMapsResponse():
      map_list_length(0), map_list(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->map_list_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->map_list_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->map_list_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->map_list_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->map_list_length);
      for( uint32_t i = 0; i < map_list_length; i++){
      offset += this->map_list[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t map_list_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      map_list_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      map_list_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      map_list_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->map_list_length);
      if(map_list_lengthT > map_list_length)
        this->map_list = (world_canvas_msgs::MapListEntry*)realloc(this->map_list, map_list_lengthT * sizeof(world_canvas_msgs::MapListEntry));
      map_list_length = map_list_lengthT;
      for( uint32_t i = 0; i < map_list_length; i++){
      offset += this->st_map_list.deserialize(inbuffer + offset);
        memcpy( &(this->map_list[i]), &(this->st_map_list), sizeof(world_canvas_msgs::MapListEntry));
      }
     return offset;
    }

    const char * getType(){ return LISTMAPS; };
    const char * getMD5(){ return "ca5a33dd106a2c24cfd54c927d214957"; };

  };

  class ListMaps {
    public:
    typedef ListMapsRequest Request;
    typedef ListMapsResponse Response;
  };

}
#endif
