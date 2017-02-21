#ifndef _ROS_stdr_msgs_ThermalSource_h
#define _ROS_stdr_msgs_ThermalSource_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose2D.h"

namespace stdr_msgs
{

  class ThermalSource : public ros::Msg
  {
    public:
      const char* id;
      float degrees;
      geometry_msgs::Pose2D pose;

    ThermalSource():
      id(""),
      degrees(0),
      pose()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_id = strlen(this->id);
      memcpy(outbuffer + offset, &length_id, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->id, length_id);
      offset += length_id;
      union {
        float real;
        uint32_t base;
      } u_degrees;
      u_degrees.real = this->degrees;
      *(outbuffer + offset + 0) = (u_degrees.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_degrees.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_degrees.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_degrees.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->degrees);
      offset += this->pose.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_id;
      memcpy(&length_id, (inbuffer + offset), sizeof(uint32_t));
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
      } u_degrees;
      u_degrees.base = 0;
      u_degrees.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_degrees.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_degrees.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_degrees.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->degrees = u_degrees.real;
      offset += sizeof(this->degrees);
      offset += this->pose.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "stdr_msgs/ThermalSource"; };
    const char * getMD5(){ return "b732f325d4ba0a2977192d50dca59310"; };

  };

}
#endif