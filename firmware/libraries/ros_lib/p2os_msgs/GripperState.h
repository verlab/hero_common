#ifndef _ROS_p2os_msgs_GripperState_h
#define _ROS_p2os_msgs_GripperState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "p2os_msgs/GripState.h"
#include "p2os_msgs/LiftState.h"

namespace p2os_msgs
{

  class GripperState : public ros::Msg
  {
    public:
      p2os_msgs::GripState grip;
      p2os_msgs::LiftState lift;

    GripperState():
      grip(),
      lift()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->grip.serialize(outbuffer + offset);
      offset += this->lift.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->grip.deserialize(inbuffer + offset);
      offset += this->lift.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "p2os_msgs/GripperState"; };
    const char * getMD5(){ return "300b38b2a4173deb725df02fa70fc70b"; };

  };

}
#endif