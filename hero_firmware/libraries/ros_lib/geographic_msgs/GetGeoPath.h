#ifndef _ROS_SERVICE_GetGeoPath_h
#define _ROS_SERVICE_GetGeoPath_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geographic_msgs/GeoPoint.h"
#include "geographic_msgs/GeoPath.h"

namespace geographic_msgs
{

static const char GETGEOPATH[] = "geographic_msgs/GetGeoPath";

  class GetGeoPathRequest : public ros::Msg
  {
    public:
      typedef geographic_msgs::GeoPoint _start_type;
      _start_type start;
      typedef geographic_msgs::GeoPoint _goal_type;
      _goal_type goal;

    GetGeoPathRequest():
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

    const char * getType(){ return GETGEOPATH; };
    const char * getMD5(){ return "cad6de11e4ae4ca568785186e1f99f89"; };

  };

  class GetGeoPathResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;
      typedef const char* _status_type;
      _status_type status;
      typedef geographic_msgs::GeoPath _plan_type;
      _plan_type plan;

    GetGeoPathResponse():
      success(0),
      status(""),
      plan()
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
      uint32_t length_status = strlen(this->status);
      varToArr(outbuffer + offset, length_status);
      offset += 4;
      memcpy(outbuffer + offset, this->status, length_status);
      offset += length_status;
      offset += this->plan.serialize(outbuffer + offset);
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
      uint32_t length_status;
      arrToVar(length_status, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_status; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_status-1]=0;
      this->status = (char *)(inbuffer + offset-1);
      offset += length_status;
      offset += this->plan.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return GETGEOPATH; };
    const char * getMD5(){ return "a76cd333bccd6c700c1b1b87dd5a3394"; };

  };

  class GetGeoPath {
    public:
    typedef GetGeoPathRequest Request;
    typedef GetGeoPathResponse Response;
  };

}
#endif
