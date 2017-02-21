#ifndef _ROS_SERVICE_SetRelationship_h
#define _ROS_SERVICE_SetRelationship_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "uuid_msgs/UniqueID.h"

namespace world_canvas_msgs
{

static const char SETRELATIONSHIP[] = "world_canvas_msgs/SetRelationship";

  class SetRelationshipRequest : public ros::Msg
  {
    public:
      uuid_msgs::UniqueID id;
      uuid_msgs::UniqueID relationship;
      uint8_t action;
      enum { ADD =  1 };
      enum { DEL =  2 };

    SetRelationshipRequest():
      id(),
      relationship(),
      action(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->id.serialize(outbuffer + offset);
      offset += this->relationship.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->action >> (8 * 0)) & 0xFF;
      offset += sizeof(this->action);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->id.deserialize(inbuffer + offset);
      offset += this->relationship.deserialize(inbuffer + offset);
      this->action =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->action);
     return offset;
    }

    const char * getType(){ return SETRELATIONSHIP; };
    const char * getMD5(){ return "959a407bfae0a7caca19dd67a720b2b8"; };

  };

  class SetRelationshipResponse : public ros::Msg
  {
    public:
      bool result;
      const char* message;

    SetRelationshipResponse():
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
      memcpy(outbuffer + offset, &length_message, sizeof(uint32_t));
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
      memcpy(&length_message, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_message-1]=0;
      this->message = (char *)(inbuffer + offset-1);
      offset += length_message;
     return offset;
    }

    const char * getType(){ return SETRELATIONSHIP; };
    const char * getMD5(){ return "b543fbd3518c791be28589b850702201"; };

  };

  class SetRelationship {
    public:
    typedef SetRelationshipRequest Request;
    typedef SetRelationshipResponse Response;
  };

}
#endif
