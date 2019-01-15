#ifndef _ROS_SERVICE_Invite_h
#define _ROS_SERVICE_Invite_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rocon_app_manager_msgs
{

static const char INVITE[] = "rocon_app_manager_msgs/Invite";

  class InviteRequest : public ros::Msg
  {
    public:
      typedef const char* _remote_target_name_type;
      _remote_target_name_type remote_target_name;
      typedef const char* _application_namespace_type;
      _application_namespace_type application_namespace;
      typedef bool _cancel_type;
      _cancel_type cancel;

    InviteRequest():
      remote_target_name(""),
      application_namespace(""),
      cancel(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_remote_target_name = strlen(this->remote_target_name);
      varToArr(outbuffer + offset, length_remote_target_name);
      offset += 4;
      memcpy(outbuffer + offset, this->remote_target_name, length_remote_target_name);
      offset += length_remote_target_name;
      uint32_t length_application_namespace = strlen(this->application_namespace);
      varToArr(outbuffer + offset, length_application_namespace);
      offset += 4;
      memcpy(outbuffer + offset, this->application_namespace, length_application_namespace);
      offset += length_application_namespace;
      union {
        bool real;
        uint8_t base;
      } u_cancel;
      u_cancel.real = this->cancel;
      *(outbuffer + offset + 0) = (u_cancel.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->cancel);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_remote_target_name;
      arrToVar(length_remote_target_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_remote_target_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_remote_target_name-1]=0;
      this->remote_target_name = (char *)(inbuffer + offset-1);
      offset += length_remote_target_name;
      uint32_t length_application_namespace;
      arrToVar(length_application_namespace, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_application_namespace; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_application_namespace-1]=0;
      this->application_namespace = (char *)(inbuffer + offset-1);
      offset += length_application_namespace;
      union {
        bool real;
        uint8_t base;
      } u_cancel;
      u_cancel.base = 0;
      u_cancel.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->cancel = u_cancel.real;
      offset += sizeof(this->cancel);
     return offset;
    }

    const char * getType(){ return INVITE; };
    const char * getMD5(){ return "4bed4f247c648d28c7c34a7504917911"; };

  };

  class InviteResponse : public ros::Msg
  {
    public:
      typedef bool _result_type;
      _result_type result;
      typedef int32_t _error_code_type;
      _error_code_type error_code;
      typedef const char* _message_type;
      _message_type message;

    InviteResponse():
      result(0),
      error_code(0),
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
      union {
        int32_t real;
        uint32_t base;
      } u_error_code;
      u_error_code.real = this->error_code;
      *(outbuffer + offset + 0) = (u_error_code.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_error_code.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_error_code.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_error_code.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->error_code);
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
      union {
        int32_t real;
        uint32_t base;
      } u_error_code;
      u_error_code.base = 0;
      u_error_code.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_error_code.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_error_code.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_error_code.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->error_code = u_error_code.real;
      offset += sizeof(this->error_code);
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

    const char * getType(){ return INVITE; };
    const char * getMD5(){ return "384ff408f471a07d9163c63207128ec5"; };

  };

  class Invite {
    public:
    typedef InviteRequest Request;
    typedef InviteResponse Response;
  };

}
#endif
