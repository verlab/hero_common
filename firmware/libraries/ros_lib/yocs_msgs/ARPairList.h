#ifndef _ROS_yocs_msgs_ARPairList_h
#define _ROS_yocs_msgs_ARPairList_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "yocs_msgs/ARPair.h"

namespace yocs_msgs
{

  class ARPairList : public ros::Msg
  {
    public:
      uint8_t pairs_length;
      yocs_msgs::ARPair st_pairs;
      yocs_msgs::ARPair * pairs;

    ARPairList():
      pairs_length(0), pairs(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = pairs_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < pairs_length; i++){
      offset += this->pairs[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t pairs_lengthT = *(inbuffer + offset++);
      if(pairs_lengthT > pairs_length)
        this->pairs = (yocs_msgs::ARPair*)realloc(this->pairs, pairs_lengthT * sizeof(yocs_msgs::ARPair));
      offset += 3;
      pairs_length = pairs_lengthT;
      for( uint8_t i = 0; i < pairs_length; i++){
      offset += this->st_pairs.deserialize(inbuffer + offset);
        memcpy( &(this->pairs[i]), &(this->st_pairs), sizeof(yocs_msgs::ARPair));
      }
     return offset;
    }

    const char * getType(){ return "yocs_msgs/ARPairList"; };
    const char * getMD5(){ return "0d0cfdee6418b6b3edd41c0abc93d76f"; };

  };

}
#endif