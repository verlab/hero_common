#ifndef _ROS_multiplanner_msgs_Paths_h
#define _ROS_multiplanner_msgs_Paths_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "nav_msgs/Path.h"

namespace multiplanner_msgs
{

  class Paths : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t paths_length;
      typedef nav_msgs::Path _paths_type;
      _paths_type st_paths;
      _paths_type * paths;

    Paths():
      header(),
      paths_length(0), paths(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->paths_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->paths_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->paths_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->paths_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->paths_length);
      for( uint32_t i = 0; i < paths_length; i++){
      offset += this->paths[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t paths_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      paths_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      paths_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      paths_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->paths_length);
      if(paths_lengthT > paths_length)
        this->paths = (nav_msgs::Path*)realloc(this->paths, paths_lengthT * sizeof(nav_msgs::Path));
      paths_length = paths_lengthT;
      for( uint32_t i = 0; i < paths_length; i++){
      offset += this->st_paths.deserialize(inbuffer + offset);
        memcpy( &(this->paths[i]), &(this->st_paths), sizeof(nav_msgs::Path));
      }
     return offset;
    }

    const char * getType(){ return "multiplanner_msgs/Paths"; };
    const char * getMD5(){ return "15f5d16b8f01a09a8f8f7b8eec36aa1c"; };

  };

}
#endif