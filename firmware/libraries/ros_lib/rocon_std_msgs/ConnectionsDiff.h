#ifndef _ROS_rocon_std_msgs_ConnectionsDiff_h
#define _ROS_rocon_std_msgs_ConnectionsDiff_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rocon_std_msgs/Connection.h"

namespace rocon_std_msgs
{

  class ConnectionsDiff : public ros::Msg
  {
    public:
      uint8_t added_length;
      rocon_std_msgs::Connection st_added;
      rocon_std_msgs::Connection * added;
      uint8_t lost_length;
      rocon_std_msgs::Connection st_lost;
      rocon_std_msgs::Connection * lost;

    ConnectionsDiff():
      added_length(0), added(NULL),
      lost_length(0), lost(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = added_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < added_length; i++){
      offset += this->added[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = lost_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < lost_length; i++){
      offset += this->lost[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t added_lengthT = *(inbuffer + offset++);
      if(added_lengthT > added_length)
        this->added = (rocon_std_msgs::Connection*)realloc(this->added, added_lengthT * sizeof(rocon_std_msgs::Connection));
      offset += 3;
      added_length = added_lengthT;
      for( uint8_t i = 0; i < added_length; i++){
      offset += this->st_added.deserialize(inbuffer + offset);
        memcpy( &(this->added[i]), &(this->st_added), sizeof(rocon_std_msgs::Connection));
      }
      uint8_t lost_lengthT = *(inbuffer + offset++);
      if(lost_lengthT > lost_length)
        this->lost = (rocon_std_msgs::Connection*)realloc(this->lost, lost_lengthT * sizeof(rocon_std_msgs::Connection));
      offset += 3;
      lost_length = lost_lengthT;
      for( uint8_t i = 0; i < lost_length; i++){
      offset += this->st_lost.deserialize(inbuffer + offset);
        memcpy( &(this->lost[i]), &(this->st_lost), sizeof(rocon_std_msgs::Connection));
      }
     return offset;
    }

    const char * getType(){ return "rocon_std_msgs/ConnectionsDiff"; };
    const char * getMD5(){ return "19f9e3bef1153b4bc619ec3d21b94718"; };

  };

}
#endif