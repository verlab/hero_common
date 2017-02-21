#ifndef _ROS_rocon_app_manager_msgs_RappList_h
#define _ROS_rocon_app_manager_msgs_RappList_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rocon_app_manager_msgs/Rapp.h"

namespace rocon_app_manager_msgs
{

  class RappList : public ros::Msg
  {
    public:
      uint8_t available_rapps_length;
      rocon_app_manager_msgs::Rapp st_available_rapps;
      rocon_app_manager_msgs::Rapp * available_rapps;

    RappList():
      available_rapps_length(0), available_rapps(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = available_rapps_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < available_rapps_length; i++){
      offset += this->available_rapps[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t available_rapps_lengthT = *(inbuffer + offset++);
      if(available_rapps_lengthT > available_rapps_length)
        this->available_rapps = (rocon_app_manager_msgs::Rapp*)realloc(this->available_rapps, available_rapps_lengthT * sizeof(rocon_app_manager_msgs::Rapp));
      offset += 3;
      available_rapps_length = available_rapps_lengthT;
      for( uint8_t i = 0; i < available_rapps_length; i++){
      offset += this->st_available_rapps.deserialize(inbuffer + offset);
        memcpy( &(this->available_rapps[i]), &(this->st_available_rapps), sizeof(rocon_app_manager_msgs::Rapp));
      }
     return offset;
    }

    const char * getType(){ return "rocon_app_manager_msgs/RappList"; };
    const char * getMD5(){ return "796706b807515187050df80223ad161e"; };

  };

}
#endif