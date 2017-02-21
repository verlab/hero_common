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
      uint8_t pairings_length;
      rocon_interaction_msgs::Pairing st_pairings;
      rocon_interaction_msgs::Pairing * pairings;

    GetPairingsResponse():
      pairings_length(0), pairings(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = pairings_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < pairings_length; i++){
      offset += this->pairings[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t pairings_lengthT = *(inbuffer + offset++);
      if(pairings_lengthT > pairings_length)
        this->pairings = (rocon_interaction_msgs::Pairing*)realloc(this->pairings, pairings_lengthT * sizeof(rocon_interaction_msgs::Pairing));
      offset += 3;
      pairings_length = pairings_lengthT;
      for( uint8_t i = 0; i < pairings_length; i++){
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
