#ifndef _ROS_SERVICE_SetKeyword_h
#define _ROS_SERVICE_SetKeyword_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "uuid_msgs/UniqueID.h"

namespace world_canvas_msgs
{

static const char SETKEYWORD[] = "world_canvas_msgs/SetKeyword";

  class SetKeywordRequest : public ros::Msg
  {
    public:
      typedef uuid_msgs::UniqueID _id_type;
      _id_type id;
      typedef const char* _keyword_type;
      _keyword_type keyword;
      typedef uint8_t _action_type;
      _action_type action;
      enum { ADD =  1 };
      enum { DEL =  2 };

    SetKeywordRequest():
      id(),
      keyword(""),
      action(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->id.serialize(outbuffer + offset);
      uint32_t length_keyword = strlen(this->keyword);
      varToArr(outbuffer + offset, length_keyword);
      offset += 4;
      memcpy(outbuffer + offset, this->keyword, length_keyword);
      offset += length_keyword;
      *(outbuffer + offset + 0) = (this->action >> (8 * 0)) & 0xFF;
      offset += sizeof(this->action);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->id.deserialize(inbuffer + offset);
      uint32_t length_keyword;
      arrToVar(length_keyword, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_keyword; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_keyword-1]=0;
      this->keyword = (char *)(inbuffer + offset-1);
      offset += length_keyword;
      this->action =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->action);
     return offset;
    }

    const char * getType(){ return SETKEYWORD; };
    const char * getMD5(){ return "9ed2d01a15fce27c3182cc6ddffe0591"; };

  };

  class SetKeywordResponse : public ros::Msg
  {
    public:
      typedef bool _result_type;
      _result_type result;
      typedef const char* _message_type;
      _message_type message;

    SetKeywordResponse():
      result(0),
      message("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_result;
      u_result.real = this->result;
      *(outbuffer + offset + 0) = (u_result.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->result);
      uint32_t length_message = strlen(this->message);
      varToArr(outbuffer + offset, length_message);
      offset += 4;
      memcpy(outbuffer + offset, this->message, length_message);
      offset += length_message;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_result;
      u_result.base = 0;
      u_result.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->result = u_result.real;
      offset += sizeof(this->result);
      uint32_t length_message;
      arrToVar(length_message, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_message-1]=0;
      this->message = (char *)(inbuffer + offset-1);
      offset += length_message;
     return offset;
    }

    const char * getType(){ return SETKEYWORD; };
    const char * getMD5(){ return "b543fbd3518c791be28589b850702201"; };

  };

  class SetKeyword {
    public:
    typedef SetKeywordRequest Request;
    typedef SetKeywordResponse Response;
  };

}
#endif
