#ifndef _ROS_SERVICE_WaypointListService_h
#define _ROS_SERVICE_WaypointListService_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "yocs_msgs/WaypointList.h"

namespace yocs_msgs
{

static const char WAYPOINTLISTSERVICE[] = "yocs_msgs/WaypointListService";

  class WaypointListServiceRequest : public ros::Msg
  {
    public:

    WaypointListServiceRequest()
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

    const char * getType(){ return WAYPOINTLISTSERVICE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class WaypointListServiceResponse : public ros::Msg
  {
    public:
      bool success;
      yocs_msgs::WaypointList waypoints;

    WaypointListServiceResponse():
      success(0),
      waypoints()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      offset += this->waypoints.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
      offset += this->waypoints.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return WAYPOINTLISTSERVICE; };
    const char * getMD5(){ return "3b776b847c407c971555820af7e3f3b1"; };

  };

  class WaypointListService {
    public:
    typedef WaypointListServiceRequest Request;
    typedef WaypointListServiceResponse Response;
  };

}
#endif
