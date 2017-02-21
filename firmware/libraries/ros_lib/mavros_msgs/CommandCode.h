#ifndef _ROS_mavros_msgs_CommandCode_h
#define _ROS_mavros_msgs_CommandCode_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mavros_msgs
{

  class CommandCode : public ros::Msg
  {
    public:
      enum { CMD_DO_SET_MODE =  176 };
      enum { CMD_DO_JUMP =  177 };
      enum { CMD_DO_CHANGE_SPEED =  178 };
      enum { CMD_DO_SET_HOME =  179 };
      enum { CMD_DO_SET_RELAY =  181 };
      enum { CMD_DO_REPEAT_RELAY =  182 };
      enum { CMD_DO_SET_SERVO =  183 };
      enum { CMD_DO_REPEAT_SERVO =  184 };
      enum { CMD_DO_CONTROL_VIDEO =  200 };
      enum { CMD_DO_SET_ROI =  201 };
      enum { CMD_DO_MOUNT_CONTROL =  205 };
      enum { CMD_DO_SET_CAM_TRIGG_DIST =  206 };
      enum { CMD_DO_FENCE_ENABLE =  207 };
      enum { CMD_DO_PARACHUTE =  208 };
      enum { CMD_DO_INVERTED_FLIGHT =  210 };
      enum { CMD_DO_MOUNT_CONTROL_QUAT =  220 };
      enum { CMD_PREFLIGHT_CALIBRATION =  241 };
      enum { CMD_MISSION_START =  300 };
      enum { CMD_COMPONENT_ARM_DISARM =  400 };
      enum { CMD_START_RX_PAIR =  500 };
      enum { CMD_REQUEST_AUTOPILOT_CAPABILITIES =  520 };
      enum { CMD_DO_TRIGGER_CONTROL =  2003 };
      enum { NAV_WAYPOINT =  16 };
      enum { NAV_LOITER_UNLIM =  17 };
      enum { NAV_LOITER_TURNS =  18 };
      enum { NAV_LOITER_TIME =  19 };
      enum { NAV_RETURN_TO_LAUNCH =  20 };
      enum { NAV_LAND =  21 };
      enum { NAV_TAKEOFF =  22 };

    CommandCode()
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

    const char * getType(){ return "mavros_msgs/CommandCode"; };
    const char * getMD5(){ return "f7e54ea3892a961cc44c9350fdb0855e"; };

  };

}
#endif