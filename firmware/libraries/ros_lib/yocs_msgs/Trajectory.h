#ifndef _ROS_yocs_msgs_Trajectory_h
#define _ROS_yocs_msgs_Trajectory_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "yocs_msgs/Waypoint.h"

namespace yocs_msgs
{

  class Trajectory : public ros::Msg
  {
    public:
      std_msgs::Header header;
      const char* name;
      uint8_t waypoints_length;
      yocs_msgs::Waypoint st_waypoints;
      yocs_msgs::Waypoint * waypoints;

    Trajectory():
      header(),
      name(""),
      waypoints_length(0), waypoints(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      uint32_t length_name = strlen(this->name);
      memcpy(outbuffer + offset, &length_name, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
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
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t length_name;
      memcpy(&length_name, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
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

    const char * getType(){ return "yocs_msgs/Trajectory"; };
    const char * getMD5(){ return "ff318cb77adf15ade6b9b9b13aff3a64"; };

  };

}
#endif