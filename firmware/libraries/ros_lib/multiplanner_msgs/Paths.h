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
      std_msgs::Header header;
      uint8_t paths_length;
      nav_msgs::Path st_paths;
      nav_msgs::Path * paths;

    Paths():
      header(),
      paths_length(0), paths(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = paths_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < paths_length; i++){
      offset += this->paths[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t paths_lengthT = *(inbuffer + offset++);
      if(paths_lengthT > paths_length)
        this->paths = (nav_msgs::Path*)realloc(this->paths, paths_lengthT * sizeof(nav_msgs::Path));
      offset += 3;
      paths_length = paths_lengthT;
      for( uint8_t i = 0; i < paths_length; i++){
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