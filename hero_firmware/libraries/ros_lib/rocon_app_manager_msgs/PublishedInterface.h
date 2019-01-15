#ifndef _ROS_rocon_app_manager_msgs_PublishedInterface_h
#define _ROS_rocon_app_manager_msgs_PublishedInterface_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rocon_app_manager_msgs/PublicInterface.h"

namespace rocon_app_manager_msgs
{

  class PublishedInterface : public ros::Msg
  {
    public:
      typedef rocon_app_manager_msgs::PublicInterface _interface_type;
      _interface_type interface;
      typedef const char* _name_type;
      _name_type name;

    PublishedInterface():
      interface(),
      name("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->interface.serialize(outbuffer + offset);
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
      offset += this->interface.deserialize(inbuffer + offset);
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

    const char * getType(){ return "rocon_app_manager_msgs/PublishedInterface"; };
    const char * getMD5(){ return "0441e6f3dfb91bbff9a213da41a7a0d6"; };

  };

}
#endif