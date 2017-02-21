#ifndef _ROS_SERVICE_WaypointPush_h
#define _ROS_SERVICE_WaypointPush_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "mavros_msgs/Waypoint.h"

namespace mavros_msgs
{

static const char WAYPOINTPUSH[] = "mavros_msgs/WaypointPush";

  class WaypointPushRequest : public ros::Msg
  {
    public:
      uint8_t waypoints_length;
      mavros_msgs::Waypoint st_waypoints;
      mavros_msgs::Waypoint * waypoints;

    WaypointPushRequest():
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
        this->waypoints = (mavros_msgs::Waypoint*)realloc(this->waypoints, waypoints_lengthT * sizeof(mavros_msgs::Waypoint));
      offset += 3;
      waypoints_length = waypoints_lengthT;
      for( uint8_t i = 0; i < waypoints_length; i++){
      offset += this->st_waypoints.deserialize(inbuffer + offset);
        memcpy( &(this->waypoints[i]), &(this->st_waypoints), sizeof(mavros_msgs::Waypoint));
      }
     return offset;
    }

    const char * getType(){ return WAYPOINTPUSH; };
    const char * getMD5(){ return "a2a7f3a6be7e0cbb0a52883d59e82ee9"; };

  };

  class WaypointPushResponse : public ros::Msg
  {
    public:
      bool success;
      uint32_t wp_transfered;

    WaypointPushResponse():
      success(0),
      wp_transfered(0)
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
      *(outbuffer + offset + 0) = (this->wp_transfered >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->wp_transfered >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->wp_transfered >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->wp_transfered >> (8 * 3)) & 0xFF;
      offset += sizeof(this->wp_transfered);
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
      this->wp_transfered =  ((uint32_t) (*(inbuffer + offset)));
      this->wp_transfered |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->wp_transfered |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->wp_transfered |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->wp_transfered);
     return offset;
    }

    const char * getType(){ return WAYPOINTPUSH; };
    const char * getMD5(){ return "90e0074a42480231d34eed864d14365e"; };

  };

  class WaypointPush {
    public:
    typedef WaypointPushRequest Request;
    typedef WaypointPushResponse Response;
  };

}
#endif
