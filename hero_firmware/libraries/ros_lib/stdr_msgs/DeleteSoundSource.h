#ifndef _ROS_SERVICE_DeleteSoundSource_h
#define _ROS_SERVICE_DeleteSoundSource_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace stdr_msgs
{

static const char DELETESOUNDSOURCE[] = "stdr_msgs/DeleteSoundSource";

  class DeleteSoundSourceRequest : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;

    DeleteSoundSourceRequest():
      name("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
     return offset;
    }

    const char * getType(){ return DELETESOUNDSOURCE; };
    const char * getMD5(){ return "c1f3d28f1b044c871e6eff2e9fc3c667"; };

  };

  class DeleteSoundSourceResponse : public ros::Msg
  {
    public:

    DeleteSoundSourceResponse()
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

    const char * getType(){ return DELETESOUNDSOURCE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class DeleteSoundSource {
    public:
    typedef DeleteSoundSourceRequest Request;
    typedef DeleteSoundSourceResponse Response;
  };

}
#endif
