#ifndef _ROS_rocon_interaction_msgs_ErrorCodes_h
#define _ROS_rocon_interaction_msgs_ErrorCodes_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rocon_interaction_msgs
{

  class ErrorCodes : public ros::Msg
  {
    public:
      enum { SUCCESS =  0 };
      enum { INTERACTION_UNAVAILABLE =  20     };
      enum { INTERACTION_QUOTA_REACHED =  21   };
      enum { PAIRING_UNAVAILABLE =  30 };
      enum { START_PAIRING_FAILED =  31 };
      enum { ALREADY_PAIRING =  32 };
      enum { REQUIRED_RAPP_IS_NOT_RUNNING =  33 };
      enum { DIFFERENT_RAPP_IS_RUNNING =  34 };
      enum { NOT_PAIRING =  35 };
      enum { STOP_PAIRING_FAILED =  36 };
      enum { MSG_INTERACTION_UNAVAILABLE =  "This interaction is not available for use." };
      enum { MSG_PAIRING_UNAVAILABLE =  "The specified pairing does not exist." };
      enum { MSG_INTERACTION_QUOTA_REACHED =  "More connections of this type not permitted." };
      enum { MSG_REQUIRED_RAPP_IS_NOT_RUNNING =  "No rapp is running and this pairing interaction requires one to be." };
      enum { MSG_DIFFERENT_RAPP_IS_RUNNING =  "A different rapp to that required is already running." };
      enum { MSG_START_PAIRING_FAILED =  "Failed to start the pairing (rapp)." };
      enum { MSG_STOP_PAIRING_FAILED =  "Failed to stop a pairing (rapp)" };
      enum { MSG_ALREADY_PAIRING =  "Already pairing, cannot start another pairing." };
      enum { MSG_NOT_PAIRING =  "This interaction manager is not managing paired interactions." };

    ErrorCodes()
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

    const char * getType(){ return "rocon_interaction_msgs/ErrorCodes"; };
    const char * getMD5(){ return "07ff328fec8e7125b6dba36ae1479350"; };

  };

}
#endif