#ifndef _ROS_control_msgs_PidState_h
#define _ROS_control_msgs_PidState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "ros/duration.h"

namespace control_msgs
{

  class PidState : public ros::Msg
  {
    public:
      std_msgs::Header header;
      ros::Duration timestep;
      float error;
      float error_dot;
      float p_error;
      float i_error;
      float d_error;
      float p_term;
      float i_term;
      float d_term;
      float i_max;
      float i_min;
      float output;

    PidState():
      header(),
      timestep(),
      error(0),
      error_dot(0),
      p_error(0),
      i_error(0),
      d_error(0),
      p_term(0),
      i_term(0),
      d_term(0),
      i_max(0),
      i_min(0),
      output(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->timestep.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->timestep.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->timestep.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->timestep.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->timestep.sec);
      *(outbuffer + offset + 0) = (this->timestep.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->timestep.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->timestep.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->timestep.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->timestep.nsec);
      offset += serializeAvrFloat64(outbuffer + offset, this->error);
      offset += serializeAvrFloat64(outbuffer + offset, this->error_dot);
      offset += serializeAvrFloat64(outbuffer + offset, this->p_error);
      offset += serializeAvrFloat64(outbuffer + offset, this->i_error);
      offset += serializeAvrFloat64(outbuffer + offset, this->d_error);
      offset += serializeAvrFloat64(outbuffer + offset, this->p_term);
      offset += serializeAvrFloat64(outbuffer + offset, this->i_term);
      offset += serializeAvrFloat64(outbuffer + offset, this->d_term);
      offset += serializeAvrFloat64(outbuffer + offset, this->i_max);
      offset += serializeAvrFloat64(outbuffer + offset, this->i_min);
      offset += serializeAvrFloat64(outbuffer + offset, this->output);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->timestep.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->timestep.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->timestep.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->timestep.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->timestep.sec);
      this->timestep.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->timestep.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->timestep.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->timestep.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->timestep.nsec);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->error));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->error_dot));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->p_error));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->i_error));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->d_error));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->p_term));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->i_term));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->d_term));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->i_max));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->i_min));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->output));
     return offset;
    }

    const char * getType(){ return "control_msgs/PidState"; };
    const char * getMD5(){ return "b138ec00e886c10e73f27e8712252ea6"; };

  };

}
#endif