#ifndef _ROS_ros_tamiya_Gps_msg_h
#define _ROS_ros_tamiya_Gps_msg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace ros_tamiya
{

  class Gps_msg : public ros::Msg
  {
    public:
      std_msgs::Header header;
      const char* fix_quality;
      const char* fix3d;
      const char* status;
      int32_t sat_num;
      float latitude;
      float longitude;
      int32_t utmzone;
      float X;
      float Y;
      float speed;
      float orientation;

    Gps_msg():
      header(),
      fix_quality(""),
      fix3d(""),
      status(""),
      sat_num(0),
      latitude(0),
      longitude(0),
      utmzone(0),
      X(0),
      Y(0),
      speed(0),
      orientation(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      uint32_t length_fix_quality = strlen(this->fix_quality);
      memcpy(outbuffer + offset, &length_fix_quality, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->fix_quality, length_fix_quality);
      offset += length_fix_quality;
      uint32_t length_fix3d = strlen(this->fix3d);
      memcpy(outbuffer + offset, &length_fix3d, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->fix3d, length_fix3d);
      offset += length_fix3d;
      uint32_t length_status = strlen(this->status);
      memcpy(outbuffer + offset, &length_status, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->status, length_status);
      offset += length_status;
      union {
        int32_t real;
        uint32_t base;
      } u_sat_num;
      u_sat_num.real = this->sat_num;
      *(outbuffer + offset + 0) = (u_sat_num.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_sat_num.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_sat_num.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_sat_num.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->sat_num);
      union {
        float real;
        uint32_t base;
      } u_latitude;
      u_latitude.real = this->latitude;
      *(outbuffer + offset + 0) = (u_latitude.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_latitude.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_latitude.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_latitude.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->latitude);
      union {
        float real;
        uint32_t base;
      } u_longitude;
      u_longitude.real = this->longitude;
      *(outbuffer + offset + 0) = (u_longitude.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_longitude.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_longitude.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_longitude.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->longitude);
      union {
        int32_t real;
        uint32_t base;
      } u_utmzone;
      u_utmzone.real = this->utmzone;
      *(outbuffer + offset + 0) = (u_utmzone.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_utmzone.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_utmzone.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_utmzone.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->utmzone);
      union {
        float real;
        uint32_t base;
      } u_X;
      u_X.real = this->X;
      *(outbuffer + offset + 0) = (u_X.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_X.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_X.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_X.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->X);
      union {
        float real;
        uint32_t base;
      } u_Y;
      u_Y.real = this->Y;
      *(outbuffer + offset + 0) = (u_Y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Y);
      union {
        float real;
        uint32_t base;
      } u_speed;
      u_speed.real = this->speed;
      *(outbuffer + offset + 0) = (u_speed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_speed.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_speed.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_speed.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->speed);
      union {
        float real;
        uint32_t base;
      } u_orientation;
      u_orientation.real = this->orientation;
      *(outbuffer + offset + 0) = (u_orientation.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_orientation.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_orientation.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_orientation.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->orientation);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t length_fix_quality;
      memcpy(&length_fix_quality, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_fix_quality; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_fix_quality-1]=0;
      this->fix_quality = (char *)(inbuffer + offset-1);
      offset += length_fix_quality;
      uint32_t length_fix3d;
      memcpy(&length_fix3d, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_fix3d; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_fix3d-1]=0;
      this->fix3d = (char *)(inbuffer + offset-1);
      offset += length_fix3d;
      uint32_t length_status;
      memcpy(&length_status, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_status; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_status-1]=0;
      this->status = (char *)(inbuffer + offset-1);
      offset += length_status;
      union {
        int32_t real;
        uint32_t base;
      } u_sat_num;
      u_sat_num.base = 0;
      u_sat_num.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_sat_num.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_sat_num.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_sat_num.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->sat_num = u_sat_num.real;
      offset += sizeof(this->sat_num);
      union {
        float real;
        uint32_t base;
      } u_latitude;
      u_latitude.base = 0;
      u_latitude.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_latitude.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_latitude.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_latitude.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->latitude = u_latitude.real;
      offset += sizeof(this->latitude);
      union {
        float real;
        uint32_t base;
      } u_longitude;
      u_longitude.base = 0;
      u_longitude.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_longitude.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_longitude.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_longitude.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->longitude = u_longitude.real;
      offset += sizeof(this->longitude);
      union {
        int32_t real;
        uint32_t base;
      } u_utmzone;
      u_utmzone.base = 0;
      u_utmzone.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_utmzone.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_utmzone.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_utmzone.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->utmzone = u_utmzone.real;
      offset += sizeof(this->utmzone);
      union {
        float real;
        uint32_t base;
      } u_X;
      u_X.base = 0;
      u_X.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_X.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_X.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_X.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->X = u_X.real;
      offset += sizeof(this->X);
      union {
        float real;
        uint32_t base;
      } u_Y;
      u_Y.base = 0;
      u_Y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Y = u_Y.real;
      offset += sizeof(this->Y);
      union {
        float real;
        uint32_t base;
      } u_speed;
      u_speed.base = 0;
      u_speed.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_speed.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_speed.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_speed.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->speed = u_speed.real;
      offset += sizeof(this->speed);
      union {
        float real;
        uint32_t base;
      } u_orientation;
      u_orientation.base = 0;
      u_orientation.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_orientation.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_orientation.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_orientation.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->orientation = u_orientation.real;
      offset += sizeof(this->orientation);
     return offset;
    }

    const char * getType(){ return "ros_tamiya/Gps_msg"; };
    const char * getMD5(){ return "a0be83b67cf7273fb97820c6e5000136"; };

  };

}
#endif