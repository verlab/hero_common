#ifndef _ROS_SERVICE_SetMode_h
#define _ROS_SERVICE_SetMode_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mavros_msgs
{

static const char SETMODE[] = "mavros_msgs/SetMode";

  class SetModeRequest : public ros::Msg
  {
    public:
      uint8_t base_mode;
      const char* custom_mode;
      enum { MAV_MODE_PREFLIGHT =  0 };
      enum { MAV_MODE_STABILIZE_DISARMED =  80 };
      enum { MAV_MODE_STABILIZE_ARMED =  208 };
      enum { MAV_MODE_MANUAL_DISARMED =  64 };
      enum { MAV_MODE_MANUAL_ARMED =  192 };
      enum { MAV_MODE_GUIDED_DISARMED =  88 };
      enum { MAV_MODE_GUIDED_ARMED =  216 };
      enum { MAV_MODE_AUTO_DISARMED =  92 };
      enum { MAV_MODE_AUTO_ARMED =  220 };
      enum { MAV_MODE_TEST_DISARMED =  66 };
      enum { MAV_MODE_TEST_ARMED =  194 };

    SetModeRequest():
      base_mode(0),
      custom_mode("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->base_mode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->base_mode);
      uint32_t length_custom_mode = strlen(this->custom_mode);
      memcpy(outbuffer + offset, &length_custom_mode, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->custom_mode, length_custom_mode);
      offset += length_custom_mode;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->base_mode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->base_mode);
      uint32_t length_custom_mode;
      memcpy(&length_custom_mode, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_custom_mode; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_custom_mode-1]=0;
      this->custom_mode = (char *)(inbuffer + offset-1);
      offset += length_custom_mode;
     return offset;
    }

    const char * getType(){ return SETMODE; };
    const char * getMD5(){ return "d770431847cad3a8f50a81ec70ddf0e2"; };

  };

  class SetModeResponse : public ros::Msg
  {
    public:
      bool success;

    SetModeResponse():
      success(0)
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
     return offset;
    }

    const char * getType(){ return SETMODE; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class SetMode {
    public:
    typedef SetModeRequest Request;
    typedef SetModeResponse Response;
  };

}
#endif
