#ifndef _ROS_asctec_msgs_CurrentWay_h
#define _ROS_asctec_msgs_CurrentWay_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace asctec_msgs
{

  class CurrentWay : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t dummy1;
      uint8_t properties;
      uint16_t nr_of_wp;
      uint8_t current_wp;
      uint8_t current_wp_memlocation;
      uint8_t status;
      uint8_t dummy2;
      uint16_t navigation_status;
      uint16_t distance_to_wp;

    CurrentWay():
      header(),
      dummy1(0),
      properties(0),
      nr_of_wp(0),
      current_wp(0),
      current_wp_memlocation(0),
      status(0),
      dummy2(0),
      navigation_status(0),
      distance_to_wp(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->dummy1 >> (8 * 0)) & 0xFF;
      offset += sizeof(this->dummy1);
      *(outbuffer + offset + 0) = (this->properties >> (8 * 0)) & 0xFF;
      offset += sizeof(this->properties);
      *(outbuffer + offset + 0) = (this->nr_of_wp >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->nr_of_wp >> (8 * 1)) & 0xFF;
      offset += sizeof(this->nr_of_wp);
      *(outbuffer + offset + 0) = (this->current_wp >> (8 * 0)) & 0xFF;
      offset += sizeof(this->current_wp);
      *(outbuffer + offset + 0) = (this->current_wp_memlocation >> (8 * 0)) & 0xFF;
      offset += sizeof(this->current_wp_memlocation);
      *(outbuffer + offset + 0) = (this->status >> (8 * 0)) & 0xFF;
      offset += sizeof(this->status);
      *(outbuffer + offset + 0) = (this->dummy2 >> (8 * 0)) & 0xFF;
      offset += sizeof(this->dummy2);
      *(outbuffer + offset + 0) = (this->navigation_status >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->navigation_status >> (8 * 1)) & 0xFF;
      offset += sizeof(this->navigation_status);
      *(outbuffer + offset + 0) = (this->distance_to_wp >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->distance_to_wp >> (8 * 1)) & 0xFF;
      offset += sizeof(this->distance_to_wp);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->dummy1 =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->dummy1);
      this->properties =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->properties);
      this->nr_of_wp =  ((uint16_t) (*(inbuffer + offset)));
      this->nr_of_wp |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->nr_of_wp);
      this->current_wp =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->current_wp);
      this->current_wp_memlocation =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->current_wp_memlocation);
      this->status =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->status);
      this->dummy2 =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->dummy2);
      this->navigation_status =  ((uint16_t) (*(inbuffer + offset)));
      this->navigation_status |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->navigation_status);
      this->distance_to_wp =  ((uint16_t) (*(inbuffer + offset)));
      this->distance_to_wp |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->distance_to_wp);
     return offset;
    }

    const char * getType(){ return "asctec_msgs/CurrentWay"; };
    const char * getMD5(){ return "6d25aae02ea1a55cb5a3abd0dd055622"; };

  };

}
#endif