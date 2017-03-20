#ifndef _ROS_kobuki_msgs_AutoDockingActionFeedback_h
#define _ROS_kobuki_msgs_AutoDockingActionFeedback_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalStatus.h"
#include "kobuki_msgs/AutoDockingFeedback.h"

namespace kobuki_msgs
{

  class AutoDockingActionFeedback : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef actionlib_msgs::GoalStatus _status_type;
      _status_type status;
      typedef kobuki_msgs::AutoDockingFeedback _feedback_type;
      _feedback_type feedback;

    AutoDockingActionFeedback():
      header(),
      status(),
      feedback()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->status.serialize(outbuffer + offset);
      offset += this->feedback.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->status.deserialize(inbuffer + offset);
      offset += this->feedback.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "kobuki_msgs/AutoDockingActionFeedback"; };
    const char * getMD5(){ return "6f7132467beab5153587d9ebb8d8262d"; };

  };

}
#endif