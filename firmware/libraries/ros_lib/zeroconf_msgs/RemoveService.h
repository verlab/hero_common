#ifndef _ROS_SERVICE_RemoveService_h
#define _ROS_SERVICE_RemoveService_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "zeroconf_msgs/PublishedService.h"

namespace zeroconf_msgs
{

static const char REMOVESERVICE[] = "zeroconf_msgs/RemoveService";

  class RemoveServiceRequest : public ros::Msg
  {
    public:
      typedef zeroconf_msgs::PublishedService _service_type;
      _service_type service;

    RemoveServiceRequest():
      service()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->service.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->service.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return REMOVESERVICE; };
    const char * getMD5(){ return "7028a4a43349f6cca86209ddd39f607a"; };

  };

  class RemoveServiceResponse : public ros::Msg
  {
    public:
      typedef bool _result_type;
      _result_type result;

    RemoveServiceResponse():
      result(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_result;
      u_result.real = this->result;
      *(outbuffer + offset + 0) = (u_result.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->result);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_result;
      u_result.base = 0;
      u_result.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->result = u_result.real;
      offset += sizeof(this->result);
     return offset;
    }

    const char * getType(){ return REMOVESERVICE; };
    const char * getMD5(){ return "eb13ac1f1354ccecb7941ee8fa2192e8"; };

  };

  class RemoveService {
    public:
    typedef RemoveServiceRequest Request;
    typedef RemoveServiceResponse Response;
  };

}
#endif
