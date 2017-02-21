#ifndef _ROS_stdr_msgs_RfidTagVector_h
#define _ROS_stdr_msgs_RfidTagVector_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "stdr_msgs/RfidTag.h"

namespace stdr_msgs
{

  class RfidTagVector : public ros::Msg
  {
    public:
      uint8_t rfid_tags_length;
      stdr_msgs::RfidTag st_rfid_tags;
      stdr_msgs::RfidTag * rfid_tags;

    RfidTagVector():
      rfid_tags_length(0), rfid_tags(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = rfid_tags_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < rfid_tags_length; i++){
      offset += this->rfid_tags[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t rfid_tags_lengthT = *(inbuffer + offset++);
      if(rfid_tags_lengthT > rfid_tags_length)
        this->rfid_tags = (stdr_msgs::RfidTag*)realloc(this->rfid_tags, rfid_tags_lengthT * sizeof(stdr_msgs::RfidTag));
      offset += 3;
      rfid_tags_length = rfid_tags_lengthT;
      for( uint8_t i = 0; i < rfid_tags_length; i++){
      offset += this->st_rfid_tags.deserialize(inbuffer + offset);
        memcpy( &(this->rfid_tags[i]), &(this->st_rfid_tags), sizeof(stdr_msgs::RfidTag));
      }
     return offset;
    }

    const char * getType(){ return "stdr_msgs/RfidTagVector"; };
    const char * getMD5(){ return "d1ccd79235f17c9d8c9665681cfa66f7"; };

  };

}
#endif