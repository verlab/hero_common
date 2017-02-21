#ifndef _ROS_SERVICE_SetFollowState_h
#define _ROS_SERVICE_SetFollowState_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace turtlebot_msgs
{

static const char SETFOLLOWSTATE[] = "turtlebot_msgs/SetFollowState";

  class SetFollowStateRequest : public ros::Msg
  {
    public:
      uint8_t state;
      enum { STOPPED =  0 };
      enum { FOLLOW =  1 };

    SetFollowStateRequest():
      state(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->state >> (8 * 0)) & 0xFF;
      offset += sizeof(this->state);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->state =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->state);
     return offset;
    }

    const char * getType(){ return SETFOLLOWSTATE; };
    const char * getMD5(){ return "92b912c48c68248015bb32deb0bf7713"; };

  };

  class SetFollowStateResponse : public ros::Msg
  {
    public:
      uint8_t result;
      enum { OK =  0 };
      enum { ERROR =  1 };

    SetFollowStateResponse():
      result(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->result >> (8 * 0)) & 0xFF;
      offset += sizeof(this->result);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->result =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->result);
     return offset;
    }

    const char * getType(){ return SETFOLLOWSTATE; };
    const char * getMD5(){ return "37065417175a2f4a49100bc798e5ee49"; };

  };

  class SetFollowState {
    public:
    typedef SetFollowStateRequest Request;
    typedef SetFollowStateResponse Response;
  };

}
#endif
