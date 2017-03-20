#ifndef _ROS_kobuki_msgs_KeyboardInput_h
#define _ROS_kobuki_msgs_KeyboardInput_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace kobuki_msgs
{

  class KeyboardInput : public ros::Msg
  {
    public:
      typedef uint8_t _pressedKey_type;
      _pressedKey_type pressedKey;
      enum { KeyCode_Right =  67      };
      enum { KeyCode_Left =  68      };
      enum { KeyCode_Up =  65      };
      enum { KeyCode_Down =  66      };
      enum { KeyCode_Space =  32      };
      enum { KeyCode_Enable =  101     };
      enum { KeyCode_Disable =  100     };

    KeyboardInput():
      pressedKey(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->pressedKey >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pressedKey);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->pressedKey =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->pressedKey);
     return offset;
    }

    const char * getType(){ return "kobuki_msgs/KeyboardInput"; };
    const char * getMD5(){ return "9288b95cb32b48719d84d696be253401"; };

  };

}
#endif