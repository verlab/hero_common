#ifndef _ROS_mav_msgs_Status_h
#define _ROS_mav_msgs_Status_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace mav_msgs
{

  class Status : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef uint8_t _flight_state_type;
      _flight_state_type flight_state;

    Status():
      header(),
      flight_state(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->flight_state >> (8 * 0)) & 0xFF;
      offset += sizeof(this->flight_state);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->flight_state =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->flight_state);
     return offset;
    }

    const char * getType(){ return "mav_msgs/Status"; };
    const char * getMD5(){ return "a057741fd00ea7c39c0e7269b0defec7"; };

  };

}
#endif