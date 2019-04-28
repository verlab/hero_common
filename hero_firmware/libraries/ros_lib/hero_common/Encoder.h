#ifndef _ROS_hero_common_Encoder_h
#define _ROS_hero_common_Encoder_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace hero_common
{

  class Encoder : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef float _left_ticks_type;
      _left_ticks_type left_ticks;
      typedef float _right_ticks_type;
      _right_ticks_type right_ticks;
      typedef float _left_diff_type;
      _left_diff_type left_diff;
      typedef float _right_diff_type;
      _right_diff_type right_diff;
      typedef float _left_dist_type;
      _left_dist_type left_dist;
      typedef float _right_dist_type;
      _right_dist_type right_dist;
      typedef float _timestep_type;
      _timestep_type timestep;
      typedef float _left_speed_type;
      _left_speed_type left_speed;
      typedef float _right_speed_type;
      _right_speed_type right_speed;
      typedef float _left_speed_filtered_type;
      _left_speed_filtered_type left_speed_filtered;
      typedef float _right_speed_filtered_type;
      _right_speed_filtered_type right_speed_filtered;

    Encoder():
      header(),
      left_ticks(0),
      right_ticks(0),
      left_diff(0),
      right_diff(0),
      left_dist(0),
      right_dist(0),
      timestep(0),
      left_speed(0),
      right_speed(0),
      left_speed_filtered(0),
      right_speed_filtered(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->left_ticks);
      offset += serializeAvrFloat64(outbuffer + offset, this->right_ticks);
      offset += serializeAvrFloat64(outbuffer + offset, this->left_diff);
      offset += serializeAvrFloat64(outbuffer + offset, this->right_diff);
      offset += serializeAvrFloat64(outbuffer + offset, this->left_dist);
      offset += serializeAvrFloat64(outbuffer + offset, this->right_dist);
      offset += serializeAvrFloat64(outbuffer + offset, this->timestep);
      offset += serializeAvrFloat64(outbuffer + offset, this->left_speed);
      offset += serializeAvrFloat64(outbuffer + offset, this->right_speed);
      offset += serializeAvrFloat64(outbuffer + offset, this->left_speed_filtered);
      offset += serializeAvrFloat64(outbuffer + offset, this->right_speed_filtered);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->left_ticks));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->right_ticks));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->left_diff));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->right_diff));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->left_dist));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->right_dist));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->timestep));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->left_speed));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->right_speed));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->left_speed_filtered));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->right_speed_filtered));
     return offset;
    }

    const char * getType(){ return "hero_common/Encoder"; };
    const char * getMD5(){ return "b5586cdbae9b740afc6a1f403a2d7dde"; };

  };

}
#endif
