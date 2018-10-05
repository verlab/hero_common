#ifndef _ROS_gateway_msgs_ConnectionType_h
#define _ROS_gateway_msgs_ConnectionType_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace gateway_msgs
{

  class ConnectionType : public ros::Msg
  {
    public:
      enum { PUBLISHER =  publisher };
      enum { SUBSCRIBER =  subscriber };
      enum { SERVICE =  service };
      enum { ACTION_CLIENT =  action_client };
      enum { ACTION_SERVER =  action_server };
      enum { INVALID =  invalid };

    ConnectionType()
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

    const char * getType(){ return "gateway_msgs/ConnectionType"; };
    const char * getMD5(){ return "65d75f1bb32566bfec48966db2073c81"; };

  };

}
#endif