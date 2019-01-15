#ifndef _ROS_stdr_msgs_CO2Source_h
#define _ROS_stdr_msgs_CO2Source_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose2D.h"

namespace stdr_msgs
{

  class CO2Source : public ros::Msg
  {
    public:
      typedef const char* _id_type;
      _id_type id;
      typedef float _ppm_type;
      _ppm_type ppm;
      typedef geometry_msgs::Pose2D _pose_type;
      _pose_type pose;

    CO2Source():
      id(""),
      ppm(0),
      pose()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_id = strlen(this->id);
      varToArr(outbuffer + offset, length_id);
      offset += 4;
      memcpy(outbuffer + offset, this->id, length_id);
      offset += length_id;
      union {
        float real;
        uint32_t base;
      } u_ppm;
      u_ppm.real = this->ppm;
      *(outbuffer + offset + 0) = (u_ppm.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ppm.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ppm.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ppm.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ppm);
      offset += this->pose.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_id;
      arrToVar(length_id, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_id-1]=0;
      this->id = (char *)(inbuffer + offset-1);
      offset += length_id;
      union {
        float real;
        uint32_t base;
      } u_ppm;
      u_ppm.base = 0;
      u_ppm.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ppm.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ppm.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ppm.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ppm = u_ppm.real;
      offset += sizeof(this->ppm);
      offset += this->pose.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "stdr_msgs/CO2Source"; };
    const char * getMD5(){ return "5d5cdddff090254ed6052018cd9b2686"; };

  };

}
#endif