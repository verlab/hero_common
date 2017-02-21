#ifndef _ROS_yocs_msgs_WaypointList_h
#define _ROS_yocs_msgs_WaypointList_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "yocs_msgs/Waypoint.h"

namespace yocs_msgs
{

  class WaypointList : public ros::Msg
  {
    public:
      uint8_t waypoints_length;
      yocs_msgs::Waypoint st_waypoints;
      yocs_msgs::Waypoint * waypoints;

    WaypointList():
      waypoints_length(0), waypoints(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = waypoints_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < waypoints_length; i++){
      offset += this->waypoints[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t waypoints_lengthT = *(inbuffer + offset++);
      if(waypoints_lengthT > waypoints_length)
        this->waypoints = (yocs_msgs::Waypoint*)realloc(this->waypoints, waypoints_lengthT * sizeof(yocs_msgs::Waypoint));
      offset += 3;
      waypoints_length = waypoints_lengthT;
      for( uint8_t i = 0; i < waypoints_length; i++){
      offset += this->st_waypoints.deserialize(inbuffer + offset);
        memcpy( &(this->waypoints[i]), &(this->st_waypoints), sizeof(yocs_msgs::Waypoint));
      }
     return offset;
    }

    const char * getType(){ return "yocs_msgs/WaypointList"; };
    const char * getMD5(){ return "66731005e3cf60fadb987aba363410ed"; };

  };

}
#endif