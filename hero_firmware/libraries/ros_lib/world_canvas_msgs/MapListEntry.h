#ifndef _ROS_world_canvas_msgs_MapListEntry_h
#define _ROS_world_canvas_msgs_MapListEntry_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace world_canvas_msgs
{

  class MapListEntry : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;
      typedef const char* _session_id_type;
      _session_id_type session_id;
      typedef int64_t _date_type;
      _date_type date;
      typedef const char* _map_id_type;
      _map_id_type map_id;

    MapListEntry():
      name(""),
      session_id(""),
      date(0),
      map_id("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      uint32_t length_session_id = strlen(this->session_id);
      varToArr(outbuffer + offset, length_session_id);
      offset += 4;
      memcpy(outbuffer + offset, this->session_id, length_session_id);
      offset += length_session_id;
      union {
        int64_t real;
        uint64_t base;
      } u_date;
      u_date.real = this->date;
      *(outbuffer + offset + 0) = (u_date.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_date.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_date.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_date.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_date.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_date.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_date.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_date.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->date);
      uint32_t length_map_id = strlen(this->map_id);
      varToArr(outbuffer + offset, length_map_id);
      offset += 4;
      memcpy(outbuffer + offset, this->map_id, length_map_id);
      offset += length_map_id;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
      uint32_t length_session_id;
      arrToVar(length_session_id, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_session_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_session_id-1]=0;
      this->session_id = (char *)(inbuffer + offset-1);
      offset += length_session_id;
      union {
        int64_t real;
        uint64_t base;
      } u_date;
      u_date.base = 0;
      u_date.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_date.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_date.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_date.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_date.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_date.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_date.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_date.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->date = u_date.real;
      offset += sizeof(this->date);
      uint32_t length_map_id;
      arrToVar(length_map_id, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_map_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_map_id-1]=0;
      this->map_id = (char *)(inbuffer + offset-1);
      offset += length_map_id;
     return offset;
    }

    const char * getType(){ return "world_canvas_msgs/MapListEntry"; };
    const char * getMD5(){ return "092f024758d394d17196cd37d999fdb0"; };

  };

}
#endif