#ifndef _ROS_rocon_std_msgs_StringArray_h
#define _ROS_rocon_std_msgs_StringArray_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rocon_std_msgs
{

  class StringArray : public ros::Msg
  {
    public:
      uint8_t strings_length;
      char* st_strings;
      char* * strings;

    StringArray():
      strings_length(0), strings(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = strings_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < strings_length; i++){
      uint32_t length_stringsi = strlen(this->strings[i]);
      memcpy(outbuffer + offset, &length_stringsi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->strings[i], length_stringsi);
      offset += length_stringsi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t strings_lengthT = *(inbuffer + offset++);
      if(strings_lengthT > strings_length)
        this->strings = (char**)realloc(this->strings, strings_lengthT * sizeof(char*));
      offset += 3;
      strings_length = strings_lengthT;
      for( uint8_t i = 0; i < strings_length; i++){
      uint32_t length_st_strings;
      memcpy(&length_st_strings, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_strings; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_strings-1]=0;
      this->st_strings = (char *)(inbuffer + offset-1);
      offset += length_st_strings;
        memcpy( &(this->strings[i]), &(this->st_strings), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return "rocon_std_msgs/StringArray"; };
    const char * getMD5(){ return "51789d20146e565223d0963361aecda1"; };

  };

}
#endif