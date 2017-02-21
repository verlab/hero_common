#ifndef _ROS_SERVICE_MakeNavPlan_h
#define _ROS_SERVICE_MakeNavPlan_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/PoseStamped.h"

namespace navfn
{

static const char MAKENAVPLAN[] = "navfn/MakeNavPlan";

  class MakeNavPlanRequest : public ros::Msg
  {
    public:
      geometry_msgs::PoseStamped start;
      geometry_msgs::PoseStamped goal;

    MakeNavPlanRequest():
      start(),
      goal()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->start.serialize(outbuffer + offset);
      offset += this->goal.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->start.deserialize(inbuffer + offset);
      offset += this->goal.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return MAKENAVPLAN; };
    const char * getMD5(){ return "2fe3126bd5b2d56edd5005220333d4fd"; };

  };

  class MakeNavPlanResponse : public ros::Msg
  {
    public:
      uint8_t plan_found;
      const char* error_message;
      uint8_t path_length;
      geometry_msgs::PoseStamped st_path;
      geometry_msgs::PoseStamped * path;

    MakeNavPlanResponse():
      plan_found(0),
      error_message(""),
      path_length(0), path(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->plan_found >> (8 * 0)) & 0xFF;
      offset += sizeof(this->plan_found);
      uint32_t length_error_message = strlen(this->error_message);
      memcpy(outbuffer + offset, &length_error_message, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->error_message, length_error_message);
      offset += length_error_message;
      *(outbuffer + offset++) = path_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < path_length; i++){
      offset += this->path[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->plan_found =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->plan_found);
      uint32_t length_error_message;
      memcpy(&length_error_message, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_error_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_error_message-1]=0;
      this->error_message = (char *)(inbuffer + offset-1);
      offset += length_error_message;
      uint8_t path_lengthT = *(inbuffer + offset++);
      if(path_lengthT > path_length)
        this->path = (geometry_msgs::PoseStamped*)realloc(this->path, path_lengthT * sizeof(geometry_msgs::PoseStamped));
      offset += 3;
      path_length = path_lengthT;
      for( uint8_t i = 0; i < path_length; i++){
      offset += this->st_path.deserialize(inbuffer + offset);
        memcpy( &(this->path[i]), &(this->st_path), sizeof(geometry_msgs::PoseStamped));
      }
     return offset;
    }

    const char * getType(){ return MAKENAVPLAN; };
    const char * getMD5(){ return "8b8ed7edf1b237dc9ddda8c8ffed5d3a"; };

  };

  class MakeNavPlan {
    public:
    typedef MakeNavPlanRequest Request;
    typedef MakeNavPlanResponse Response;
  };

}
#endif
