#ifndef _ROS_SERVICE_GetInteraction_h
#define _ROS_SERVICE_GetInteraction_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rocon_interaction_msgs/Interaction.h"

namespace rocon_interaction_msgs
{

static const char GETINTERACTION[] = "rocon_interaction_msgs/GetInteraction";

  class GetInteractionRequest : public ros::Msg
  {
    public:
      typedef int32_t _hash_type;
      _hash_type hash;

    GetInteractionRequest():
      hash(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_hash;
      u_hash.real = this->hash;
      *(outbuffer + offset + 0) = (u_hash.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_hash.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_hash.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_hash.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->hash);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_hash;
      u_hash.base = 0;
      u_hash.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_hash.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_hash.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_hash.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->hash = u_hash.real;
      offset += sizeof(this->hash);
     return offset;
    }

    const char * getType(){ return GETINTERACTION; };
    const char * getMD5(){ return "bff57ffe69467a2a244fb9a7d371e074"; };

  };

  class GetInteractionResponse : public ros::Msg
  {
    public:
      typedef bool _result_type;
      _result_type result;
      typedef rocon_interaction_msgs::Interaction _interaction_type;
      _interaction_type interaction;

    GetInteractionResponse():
      result(0),
      interaction()
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
      offset += this->interaction.serialize(outbuffer + offset);
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
      offset += this->interaction.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return GETINTERACTION; };
    const char * getMD5(){ return "791b2d4e984d3bc84277d856a387a4ac"; };

  };

  class GetInteraction {
    public:
    typedef GetInteractionRequest Request;
    typedef GetInteractionResponse Response;
  };

}
#endif
