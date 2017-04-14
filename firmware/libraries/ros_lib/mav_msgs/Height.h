#ifndef _ROS_mav_msgs_Height_h
#define _ROS_mav_msgs_Height_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace mav_msgs
{

  class Height : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef float _height_type;
      _height_type height;
      typedef float _height_variance_type;
      _height_variance_type height_variance;
      typedef float _climb_type;
      _climb_type climb;
      typedef float _climb_variance_type;
      _climb_variance_type climb_variance;

    Height():
      header(),
      height(0),
      height_variance(0),
      climb(0),
      climb_variance(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->height);
      offset += serializeAvrFloat64(outbuffer + offset, this->height_variance);
      offset += serializeAvrFloat64(outbuffer + offset, this->climb);
      offset += serializeAvrFloat64(outbuffer + offset, this->climb_variance);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->height));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->height_variance));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->climb));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->climb_variance));
     return offset;
    }

    const char * getType(){ return "mav_msgs/Height"; };
    const char * getMD5(){ return "a78e1294ab4281402b080d0478dd360c"; };

  };

}
#endif