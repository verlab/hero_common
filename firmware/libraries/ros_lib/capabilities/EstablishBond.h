#ifndef _ROS_SERVICE_EstablishBond_h
#define _ROS_SERVICE_EstablishBond_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace capabilities
{

static const char ESTABLISHBOND[] = "capabilities/EstablishBond";

  class EstablishBondRequest : public ros::Msg
  {
    public:

    EstablishBondRequest()
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

    const char * getType(){ return ESTABLISHBOND; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class EstablishBondResponse : public ros::Msg
  {
    public:
      typedef const char* _bond_id_type;
      _bond_id_type bond_id;

    EstablishBondResponse():
      bond_id("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_bond_id = strlen(this->bond_id);
      varToArr(outbuffer + offset, length_bond_id);
      offset += 4;
      memcpy(outbuffer + offset, this->bond_id, length_bond_id);
      offset += length_bond_id;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_bond_id;
      arrToVar(length_bond_id, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_bond_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_bond_id-1]=0;
      this->bond_id = (char *)(inbuffer + offset-1);
      offset += length_bond_id;
     return offset;
    }

    const char * getType(){ return ESTABLISHBOND; };
    const char * getMD5(){ return "5dec67991af973eddfa86dc20c3faef0"; };

  };

  class EstablishBond {
    public:
    typedef EstablishBondRequest Request;
    typedef EstablishBondResponse Response;
  };

}
#endif
