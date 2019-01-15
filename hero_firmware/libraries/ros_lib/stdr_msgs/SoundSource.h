#ifndef _ROS_stdr_msgs_SoundSource_h
#define _ROS_stdr_msgs_SoundSource_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose2D.h"

namespace stdr_msgs
{

  class SoundSource : public ros::Msg
  {
    public:
      typedef const char* _id_type;
      _id_type id;
      typedef float _dbs_type;
      _dbs_type dbs;
      typedef geometry_msgs::Pose2D _pose_type;
      _pose_type pose;

    SoundSource():
      id(""),
      dbs(0),
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
      } u_dbs;
      u_dbs.real = this->dbs;
      *(outbuffer + offset + 0) = (u_dbs.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_dbs.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_dbs.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_dbs.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->dbs);
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
      } u_dbs;
      u_dbs.base = 0;
      u_dbs.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_dbs.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_dbs.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_dbs.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->dbs = u_dbs.real;
      offset += sizeof(this->dbs);
      offset += this->pose.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "stdr_msgs/SoundSource"; };
    const char * getMD5(){ return "c45183ddcf94455b2f7bb47f2f3e9f87"; };

  };

}
#endif