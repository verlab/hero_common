#ifndef _ROS_mavros_msgs_Mavlink_h
#define _ROS_mavros_msgs_Mavlink_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace mavros_msgs
{

  class Mavlink : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t framing_status;
      uint8_t magic;
      uint8_t len;
      uint8_t incompat_flags;
      uint8_t compat_flags;
      uint8_t seq;
      uint8_t sysid;
      uint8_t compid;
      uint32_t msgid;
      uint16_t checksum;
      uint8_t payload64_length;
      uint64_t st_payload64;
      uint64_t * payload64;
      uint8_t signature_length;
      uint8_t st_signature;
      uint8_t * signature;
      enum { FRAMING_OK =  1 };
      enum { FRAMING_BAD_CRC =  2 };
      enum { FRAMING_BAD_SIGNATURE =  3 };
      enum { MAVLINK_V10 =  254 };
      enum { MAVLINK_V20 =  253 };

    Mavlink():
      header(),
      framing_status(0),
      magic(0),
      len(0),
      incompat_flags(0),
      compat_flags(0),
      seq(0),
      sysid(0),
      compid(0),
      msgid(0),
      checksum(0),
      payload64_length(0), payload64(NULL),
      signature_length(0), signature(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->framing_status >> (8 * 0)) & 0xFF;
      offset += sizeof(this->framing_status);
      *(outbuffer + offset + 0) = (this->magic >> (8 * 0)) & 0xFF;
      offset += sizeof(this->magic);
      *(outbuffer + offset + 0) = (this->len >> (8 * 0)) & 0xFF;
      offset += sizeof(this->len);
      *(outbuffer + offset + 0) = (this->incompat_flags >> (8 * 0)) & 0xFF;
      offset += sizeof(this->incompat_flags);
      *(outbuffer + offset + 0) = (this->compat_flags >> (8 * 0)) & 0xFF;
      offset += sizeof(this->compat_flags);
      *(outbuffer + offset + 0) = (this->seq >> (8 * 0)) & 0xFF;
      offset += sizeof(this->seq);
      *(outbuffer + offset + 0) = (this->sysid >> (8 * 0)) & 0xFF;
      offset += sizeof(this->sysid);
      *(outbuffer + offset + 0) = (this->compid >> (8 * 0)) & 0xFF;
      offset += sizeof(this->compid);
      *(outbuffer + offset + 0) = (this->msgid >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->msgid >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->msgid >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->msgid >> (8 * 3)) & 0xFF;
      offset += sizeof(this->msgid);
      *(outbuffer + offset + 0) = (this->checksum >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->checksum >> (8 * 1)) & 0xFF;
      offset += sizeof(this->checksum);
      *(outbuffer + offset++) = payload64_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < payload64_length; i++){
      union {
        uint64_t real;
        uint32_t base;
      } u_payload64i;
      u_payload64i.real = this->payload64[i];
      *(outbuffer + offset + 0) = (u_payload64i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_payload64i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_payload64i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_payload64i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->payload64[i]);
      }
      *(outbuffer + offset++) = signature_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < signature_length; i++){
      *(outbuffer + offset + 0) = (this->signature[i] >> (8 * 0)) & 0xFF;
      offset += sizeof(this->signature[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->framing_status =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->framing_status);
      this->magic =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->magic);
      this->len =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->len);
      this->incompat_flags =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->incompat_flags);
      this->compat_flags =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->compat_flags);
      this->seq =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->seq);
      this->sysid =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->sysid);
      this->compid =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->compid);
      this->msgid =  ((uint32_t) (*(inbuffer + offset)));
      this->msgid |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->msgid |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->msgid |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->msgid);
      this->checksum =  ((uint16_t) (*(inbuffer + offset)));
      this->checksum |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->checksum);
      uint8_t payload64_lengthT = *(inbuffer + offset++);
      if(payload64_lengthT > payload64_length)
        this->payload64 = (uint64_t*)realloc(this->payload64, payload64_lengthT * sizeof(uint64_t));
      offset += 3;
      payload64_length = payload64_lengthT;
      for( uint8_t i = 0; i < payload64_length; i++){
      union {
        uint64_t real;
        uint32_t base;
      } u_st_payload64;
      u_st_payload64.base = 0;
      u_st_payload64.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_payload64.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_payload64.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_payload64.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_payload64 = u_st_payload64.real;
      offset += sizeof(this->st_payload64);
        memcpy( &(this->payload64[i]), &(this->st_payload64), sizeof(uint64_t));
      }
      uint8_t signature_lengthT = *(inbuffer + offset++);
      if(signature_lengthT > signature_length)
        this->signature = (uint8_t*)realloc(this->signature, signature_lengthT * sizeof(uint8_t));
      offset += 3;
      signature_length = signature_lengthT;
      for( uint8_t i = 0; i < signature_length; i++){
      this->st_signature =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->st_signature);
        memcpy( &(this->signature[i]), &(this->st_signature), sizeof(uint8_t));
      }
     return offset;
    }

    const char * getType(){ return "mavros_msgs/Mavlink"; };
    const char * getMD5(){ return "41093e1fd0f3eea1da2aa33a177e5ba6"; };

  };

}
#endif