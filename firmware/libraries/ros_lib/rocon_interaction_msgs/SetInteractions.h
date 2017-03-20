#ifndef _ROS_SERVICE_SetInteractions_h
#define _ROS_SERVICE_SetInteractions_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rocon_interaction_msgs/Interaction.h"
#include "rocon_interaction_msgs/Pairing.h"

namespace rocon_interaction_msgs
{

static const char SETINTERACTIONS[] = "rocon_interaction_msgs/SetInteractions";

  class SetInteractionsRequest : public ros::Msg
  {
    public:
      uint32_t pairings_length;
      typedef rocon_interaction_msgs::Pairing _pairings_type;
      _pairings_type st_pairings;
      _pairings_type * pairings;
      uint32_t interactions_length;
      typedef rocon_interaction_msgs::Interaction _interactions_type;
      _interactions_type st_interactions;
      _interactions_type * interactions;
      typedef bool _load_type;
      _load_type load;

    SetInteractionsRequest():
      pairings_length(0), pairings(NULL),
      interactions_length(0), interactions(NULL),
      load(0)
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
      *(outbuffer + offset + 0) = (this->interactions_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->interactions_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->interactions_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->interactions_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->interactions_length);
      for( uint32_t i = 0; i < interactions_length; i++){
      offset += this->interactions[i].serialize(outbuffer + offset);
      }
      union {
        bool real;
        uint8_t base;
      } u_load;
      u_load.real = this->load;
      *(outbuffer + offset + 0) = (u_load.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->load);
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
      uint32_t interactions_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      interactions_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      interactions_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      interactions_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->interactions_length);
      if(interactions_lengthT > interactions_length)
        this->interactions = (rocon_interaction_msgs::Interaction*)realloc(this->interactions, interactions_lengthT * sizeof(rocon_interaction_msgs::Interaction));
      interactions_length = interactions_lengthT;
      for( uint32_t i = 0; i < interactions_length; i++){
      offset += this->st_interactions.deserialize(inbuffer + offset);
        memcpy( &(this->interactions[i]), &(this->st_interactions), sizeof(rocon_interaction_msgs::Interaction));
      }
      union {
        bool real;
        uint8_t base;
      } u_load;
      u_load.base = 0;
      u_load.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->load = u_load.real;
      offset += sizeof(this->load);
     return offset;
    }

    const char * getType(){ return SETINTERACTIONS; };
    const char * getMD5(){ return "ddb087ba9118c7e739c0e6ffb1147e4a"; };

  };

  class SetInteractionsResponse : public ros::Msg
  {
    public:
      typedef bool _result_type;
      _result_type result;

    SetInteractionsResponse():
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

    const char * getType(){ return SETINTERACTIONS; };
    const char * getMD5(){ return "eb13ac1f1354ccecb7941ee8fa2192e8"; };

  };

  class SetInteractions {
    public:
    typedef SetInteractionsRequest Request;
    typedef SetInteractionsResponse Response;
  };

}
#endif
