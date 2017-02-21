#ifndef _ROS_yocs_msgs_TrajectoryList_h
#define _ROS_yocs_msgs_TrajectoryList_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "yocs_msgs/Trajectory.h"

namespace yocs_msgs
{

  class TrajectoryList : public ros::Msg
  {
    public:
      uint8_t trajectories_length;
      yocs_msgs::Trajectory st_trajectories;
      yocs_msgs::Trajectory * trajectories;

    TrajectoryList():
      trajectories_length(0), trajectories(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = trajectories_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < trajectories_length; i++){
      offset += this->trajectories[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t trajectories_lengthT = *(inbuffer + offset++);
      if(trajectories_lengthT > trajectories_length)
        this->trajectories = (yocs_msgs::Trajectory*)realloc(this->trajectories, trajectories_lengthT * sizeof(yocs_msgs::Trajectory));
      offset += 3;
      trajectories_length = trajectories_lengthT;
      for( uint8_t i = 0; i < trajectories_length; i++){
      offset += this->st_trajectories.deserialize(inbuffer + offset);
        memcpy( &(this->trajectories[i]), &(this->st_trajectories), sizeof(yocs_msgs::Trajectory));
      }
     return offset;
    }

    const char * getType(){ return "yocs_msgs/TrajectoryList"; };
    const char * getMD5(){ return "f0901d378c8ac2d2d3d8feafaa343a58"; };

  };

}
#endif