#ifndef _ROS_kobuki_msgs_DockInfraRed_h
#define _ROS_kobuki_msgs_DockInfraRed_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace kobuki_msgs
{

  class DockInfraRed : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t data_length;
      uint8_t st_data;
      uint8_t * data;
      enum { NEAR_LEFT =   1 };
      enum { NEAR_CENTER =   2 };
      enum { NEAR_RIGHT =   4 };
      enum { FAR_LEFT =  16 };
      enum { FAR_CENTER =   8 };
      enum { FAR_RIGHT =  32 };

    DockInfraRed():
      header(),
      data_length(0), data(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = data_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < data_length; i++){
      *(outbuffer + offset + 0) = (this->data[i] >> (8 * 0)) & 0xFF;
      offset += sizeof(this->data[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t data_lengthT = *(inbuffer + offset++);
      if(data_lengthT > data_length)
        this->data = (uint8_t*)realloc(this->data, data_lengthT * sizeof(uint8_t));
      offset += 3;
      data_length = data_lengthT;
      for( uint8_t i = 0; i < data_length; i++){
      this->st_data =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->st_data);
        memcpy( &(this->data[i]), &(this->st_data), sizeof(uint8_t));
      }
     return offset;
    }

    const char * getType(){ return "kobuki_msgs/DockInfraRed"; };
    const char * getMD5(){ return "a3d77f7d15e50579473dcc24e9b97b34"; };

  };

}
#endif