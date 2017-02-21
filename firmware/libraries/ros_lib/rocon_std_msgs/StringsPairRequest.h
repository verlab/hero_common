#ifndef _ROS_rocon_std_msgs_StringsPairRequest_h
#define _ROS_rocon_std_msgs_StringsPairRequest_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "uuid_msgs/UniqueID.h"
#include "rocon_std_msgs/StringsRequest.h"

namespace rocon_std_msgs
{

  class StringsPairRequest : public ros::Msg
  {
    public:
      uuid_msgs::UniqueID id;
      rocon_std_msgs::StringsRequest request;

    StringsPairRequest():
      id(),
      request()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->id.serialize(outbuffer + offset);
      offset += this->request.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->id.deserialize(inbuffer + offset);
      offset += this->request.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "rocon_std_msgs/StringsPairRequest"; };
    const char * getMD5(){ return "71ec95e384ce52aa32491f3b69a62027"; };

  };

}
#endif