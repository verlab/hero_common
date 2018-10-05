#ifndef _ROS_rocon_interaction_msgs_PairingStatus_h
#define _ROS_rocon_interaction_msgs_PairingStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rocon_interaction_msgs
{

  class PairingStatus : public ros::Msg
  {
    public:
      typedef const char* _active_pairing_type;
      _active_pairing_type active_pairing;

    PairingStatus():
      active_pairing("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_active_pairing = strlen(this->active_pairing);
      varToArr(outbuffer + offset, length_active_pairing);
      offset += 4;
      memcpy(outbuffer + offset, this->active_pairing, length_active_pairing);
      offset += length_active_pairing;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_active_pairing;
      arrToVar(length_active_pairing, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_active_pairing; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_active_pairing-1]=0;
      this->active_pairing = (char *)(inbuffer + offset-1);
      offset += length_active_pairing;
     return offset;
    }

    const char * getType(){ return "rocon_interaction_msgs/PairingStatus"; };
    const char * getMD5(){ return "b404b2284f2d7e4f38394ad5a36be453"; };

  };

}
#endif