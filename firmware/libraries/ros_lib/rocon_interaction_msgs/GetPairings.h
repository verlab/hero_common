#ifndef _ROS_SERVICE_GetPairings_h
#define _ROS_SERVICE_GetPairings_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rocon_interaction_msgs/Pairing.h"

namespace rocon_interaction_msgs
{

static const char GETPAIRINGS[] = "rocon_interaction_msgs/GetPairings";

  class GetPairingsRequest : public ros::Msg
  {
    public:

    GetPairingsRequest()
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

    const char * getType(){ return GETPAIRINGS; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetPairingsResponse : public ros::Msg
  {
    public:
      uint32_t pairings_length;
      typedef rocon_interaction_msgs::Pairing _pairings_type;
      _pairings_type st_pairings;
      _pairings_type * pairings;

    GetPairingsResponse():
      pairings_length(0), pairings(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->pairings_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->pairings_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->pairings_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->pairings_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pairings_length);
      for( uint32_t i = 0; i < pairings_length; i++){
      offset += this->pairings[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t pairings_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      pairings_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      pairings_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      pairings_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->pairings_length);
      if(pairings_lengthT > pairings_length)
        this->pairings = (rocon_interaction_msgs::Pairing*)realloc(this->pairings, pairings_lengthT * sizeof(rocon_interaction_msgs::Pairing));
      pairings_length = pairings_lengthT;
      for( uint32_t i = 0; i < pairings_length; i++){
      offset += this->st_pairings.deserialize(inbuffer + offset);
        memcpy( &(this->pairings[i]), &(this->st_pairings), sizeof(rocon_interaction_msgs::Pairing));
      }
     return offset;
    }

    const char * getType(){ return GETPAIRINGS; };
    const char * getMD5(){ return "e0e0dfdbbb548c1c4a3f673bbe3961a7"; };

  };

  class GetPairings {
    public:
    typedef GetPairingsRequest Request;
    typedef GetPairingsResponse Response;
  };

}
#endif
