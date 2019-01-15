#ifndef _ROS_SERVICE_LoadExternalMap_h
#define _ROS_SERVICE_LoadExternalMap_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "nav_msgs/OccupancyGrid.h"

namespace stdr_msgs
{

static const char LOADEXTERNALMAP[] = "stdr_msgs/LoadExternalMap";

  class LoadExternalMapRequest : public ros::Msg
  {
    public:
      typedef nav_msgs::OccupancyGrid _map_type;
      _map_type map;

    LoadExternalMapRequest():
      map()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->map.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->map.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return LOADEXTERNALMAP; };
    const char * getMD5(){ return "6cdd0a18e0aff5b0a3ca2326a89b54ff"; };

  };

  class LoadExternalMapResponse : public ros::Msg
  {
    public:

    LoadExternalMapResponse()
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

    const char * getType(){ return LOADEXTERNALMAP; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class LoadExternalMap {
    public:
    typedef LoadExternalMapRequest Request;
    typedef LoadExternalMapResponse Response;
  };

}
#endif
