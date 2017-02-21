#ifndef _ROS_yocs_msgs_ColumnList_h
#define _ROS_yocs_msgs_ColumnList_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "yocs_msgs/Column.h"

namespace yocs_msgs
{

  class ColumnList : public ros::Msg
  {
    public:
      uint8_t obstacles_length;
      yocs_msgs::Column st_obstacles;
      yocs_msgs::Column * obstacles;

    ColumnList():
      obstacles_length(0), obstacles(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = obstacles_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < obstacles_length; i++){
      offset += this->obstacles[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t obstacles_lengthT = *(inbuffer + offset++);
      if(obstacles_lengthT > obstacles_length)
        this->obstacles = (yocs_msgs::Column*)realloc(this->obstacles, obstacles_lengthT * sizeof(yocs_msgs::Column));
      offset += 3;
      obstacles_length = obstacles_lengthT;
      for( uint8_t i = 0; i < obstacles_length; i++){
      offset += this->st_obstacles.deserialize(inbuffer + offset);
        memcpy( &(this->obstacles[i]), &(this->st_obstacles), sizeof(yocs_msgs::Column));
      }
     return offset;
    }

    const char * getType(){ return "yocs_msgs/ColumnList"; };
    const char * getMD5(){ return "fdf98d2a8a0cfe17000cdb66889826b6"; };

  };

}
#endif