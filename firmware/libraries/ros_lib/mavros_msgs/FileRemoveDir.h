#ifndef _ROS_SERVICE_FileRemoveDir_h
#define _ROS_SERVICE_FileRemoveDir_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mavros_msgs
{

static const char FILEREMOVEDIR[] = "mavros_msgs/FileRemoveDir";

  class FileRemoveDirRequest : public ros::Msg
  {
    public:
      const char* dir_path;

    FileRemoveDirRequest():
      dir_path("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_dir_path = strlen(this->dir_path);
      memcpy(outbuffer + offset, &length_dir_path, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->dir_path, length_dir_path);
      offset += length_dir_path;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_dir_path;
      memcpy(&length_dir_path, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_dir_path; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_dir_path-1]=0;
      this->dir_path = (char *)(inbuffer + offset-1);
      offset += length_dir_path;
     return offset;
    }

    const char * getType(){ return FILEREMOVEDIR; };
    const char * getMD5(){ return "401d5cf5f836aaa9ebdc0897f75da874"; };

  };

  class FileRemoveDirResponse : public ros::Msg
  {
    public:
      bool success;
      int32_t r_errno;

    FileRemoveDirResponse():
      success(0),
      r_errno(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      union {
        int32_t real;
        uint32_t base;
      } u_r_errno;
      u_r_errno.real = this->r_errno;
      *(outbuffer + offset + 0) = (u_r_errno.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_r_errno.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_r_errno.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_r_errno.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->r_errno);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
      union {
        int32_t real;
        uint32_t base;
      } u_r_errno;
      u_r_errno.base = 0;
      u_r_errno.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_r_errno.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_r_errno.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_r_errno.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->r_errno = u_r_errno.real;
      offset += sizeof(this->r_errno);
     return offset;
    }

    const char * getType(){ return FILEREMOVEDIR; };
    const char * getMD5(){ return "85394f2e941a8937ac567a617f06157f"; };

  };

  class FileRemoveDir {
    public:
    typedef FileRemoveDirRequest Request;
    typedef FileRemoveDirResponse Response;
  };

}
#endif
