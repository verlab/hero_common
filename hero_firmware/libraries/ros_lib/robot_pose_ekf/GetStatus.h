#ifndef _ROS_SERVICE_GetStatus_h
#define _ROS_SERVICE_GetStatus_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace robot_pose_ekf
{

static const char GETSTATUS[] = "robot_pose_ekf/GetStatus";

  class GetStatusRequest : public ros::Msg
  {
    public:

    GetStatusRequest()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return GETSTATUS; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetStatusResponse : public ros::Msg
  {
    public:
      typedef const char* _status_type;
      _status_type status;

    GetStatusResponse():
      status("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_status = strlen(this->status);
      varToArr(outbuffer + offset, length_status);
      offset += 4;
      memcpy(outbuffer + offset, this->status, length_status);
      offset += length_status;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_status;
      arrToVar(length_status, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_status; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_status-1]=0;
      this->status = (char *)(inbuffer + offset-1);
      offset += length_status;
     return offset;
    }

    const char * getType(){ return GETSTATUS; };
    const char * getMD5(){ return "4fe5af303955c287688e7347e9b00278"; };

  };

  class GetStatus {
    public:
    typedef GetStatusRequest Request;
    typedef GetStatusResponse Response;
  };

}
#endif
