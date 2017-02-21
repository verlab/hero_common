#ifndef _ROS_stdr_msgs_RfidSensorMeasurementMsg_h
#define _ROS_stdr_msgs_RfidSensorMeasurementMsg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace stdr_msgs
{

  class RfidSensorMeasurementMsg : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t rfid_tags_ids_length;
      char* st_rfid_tags_ids;
      char* * rfid_tags_ids;
      uint8_t rfid_tags_msgs_length;
      char* st_rfid_tags_msgs;
      char* * rfid_tags_msgs;
      uint8_t rfid_tags_dbs_length;
      float st_rfid_tags_dbs;
      float * rfid_tags_dbs;

    RfidSensorMeasurementMsg():
      header(),
      rfid_tags_ids_length(0), rfid_tags_ids(NULL),
      rfid_tags_msgs_length(0), rfid_tags_msgs(NULL),
      rfid_tags_dbs_length(0), rfid_tags_dbs(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = rfid_tags_ids_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < rfid_tags_ids_length; i++){
      uint32_t length_rfid_tags_idsi = strlen(this->rfid_tags_ids[i]);
      memcpy(outbuffer + offset, &length_rfid_tags_idsi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->rfid_tags_ids[i], length_rfid_tags_idsi);
      offset += length_rfid_tags_idsi;
      }
      *(outbuffer + offset++) = rfid_tags_msgs_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < rfid_tags_msgs_length; i++){
      uint32_t length_rfid_tags_msgsi = strlen(this->rfid_tags_msgs[i]);
      memcpy(outbuffer + offset, &length_rfid_tags_msgsi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->rfid_tags_msgs[i], length_rfid_tags_msgsi);
      offset += length_rfid_tags_msgsi;
      }
      *(outbuffer + offset++) = rfid_tags_dbs_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < rfid_tags_dbs_length; i++){
      union {
        float real;
        uint32_t base;
      } u_rfid_tags_dbsi;
      u_rfid_tags_dbsi.real = this->rfid_tags_dbs[i];
      *(outbuffer + offset + 0) = (u_rfid_tags_dbsi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rfid_tags_dbsi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rfid_tags_dbsi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rfid_tags_dbsi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rfid_tags_dbs[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t rfid_tags_ids_lengthT = *(inbuffer + offset++);
      if(rfid_tags_ids_lengthT > rfid_tags_ids_length)
        this->rfid_tags_ids = (char**)realloc(this->rfid_tags_ids, rfid_tags_ids_lengthT * sizeof(char*));
      offset += 3;
      rfid_tags_ids_length = rfid_tags_ids_lengthT;
      for( uint8_t i = 0; i < rfid_tags_ids_length; i++){
      uint32_t length_st_rfid_tags_ids;
      memcpy(&length_st_rfid_tags_ids, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_rfid_tags_ids; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_rfid_tags_ids-1]=0;
      this->st_rfid_tags_ids = (char *)(inbuffer + offset-1);
      offset += length_st_rfid_tags_ids;
        memcpy( &(this->rfid_tags_ids[i]), &(this->st_rfid_tags_ids), sizeof(char*));
      }
      uint8_t rfid_tags_msgs_lengthT = *(inbuffer + offset++);
      if(rfid_tags_msgs_lengthT > rfid_tags_msgs_length)
        this->rfid_tags_msgs = (char**)realloc(this->rfid_tags_msgs, rfid_tags_msgs_lengthT * sizeof(char*));
      offset += 3;
      rfid_tags_msgs_length = rfid_tags_msgs_lengthT;
      for( uint8_t i = 0; i < rfid_tags_msgs_length; i++){
      uint32_t length_st_rfid_tags_msgs;
      memcpy(&length_st_rfid_tags_msgs, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_rfid_tags_msgs; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_rfid_tags_msgs-1]=0;
      this->st_rfid_tags_msgs = (char *)(inbuffer + offset-1);
      offset += length_st_rfid_tags_msgs;
        memcpy( &(this->rfid_tags_msgs[i]), &(this->st_rfid_tags_msgs), sizeof(char*));
      }
      uint8_t rfid_tags_dbs_lengthT = *(inbuffer + offset++);
      if(rfid_tags_dbs_lengthT > rfid_tags_dbs_length)
        this->rfid_tags_dbs = (float*)realloc(this->rfid_tags_dbs, rfid_tags_dbs_lengthT * sizeof(float));
      offset += 3;
      rfid_tags_dbs_length = rfid_tags_dbs_lengthT;
      for( uint8_t i = 0; i < rfid_tags_dbs_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_rfid_tags_dbs;
      u_st_rfid_tags_dbs.base = 0;
      u_st_rfid_tags_dbs.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_rfid_tags_dbs.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_rfid_tags_dbs.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_rfid_tags_dbs.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_rfid_tags_dbs = u_st_rfid_tags_dbs.real;
      offset += sizeof(this->st_rfid_tags_dbs);
        memcpy( &(this->rfid_tags_dbs[i]), &(this->st_rfid_tags_dbs), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "stdr_msgs/RfidSensorMeasurementMsg"; };
    const char * getMD5(){ return "274b41808759cfa6e05b69149e9ea1ed"; };

  };

}
#endif