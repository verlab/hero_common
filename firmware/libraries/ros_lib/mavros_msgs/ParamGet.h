#ifndef _ROS_SERVICE_ParamGet_h
#define _ROS_SERVICE_ParamGet_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "mavros_msgs/ParamValue.h"

namespace mavros_msgs
{

static const char PARAMGET[] = "mavros_msgs/ParamGet";

  class ParamGetRequest : public ros::Msg
  {
    public:
      const char* param_id;

    ParamGetRequest():
      param_id("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_param_id = strlen(this->param_id);
      memcpy(outbuffer + offset, &length_param_id, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->param_id, length_param_id);
      offset += length_param_id;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_param_id;
      memcpy(&length_param_id, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_param_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_param_id-1]=0;
      this->param_id = (char *)(inbuffer + offset-1);
      offset += length_param_id;
     return offset;
    }

    const char * getType(){ return PARAMGET; };
    const char * getMD5(){ return "a0c8304d59f465712790120c3fc4b7d0"; };

  };

  class ParamGetResponse : public ros::Msg
  {
    public:
      bool success;
      mavros_msgs::ParamValue value;

    ParamGetResponse():
      success(0),
      value()
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
      offset += this->value.serialize(outbuffer + offset);
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
      offset += this->value.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return PARAMGET; };
    const char * getMD5(){ return "790d22b22b9dbf32a8e8d55578e25477"; };

  };

  class ParamGet {
    public:
    typedef ParamGetRequest Request;
    typedef ParamGetResponse Response;
  };

}
#endif
