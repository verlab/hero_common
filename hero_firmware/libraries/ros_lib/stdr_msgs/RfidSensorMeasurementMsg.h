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
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t rfid_tags_ids_length;
      typedef char* _rfid_tags_ids_type;
      _rfid_tags_ids_type st_rfid_tags_ids;
      _rfid_tags_ids_type * rfid_tags_ids;
      uint32_t rfid_tags_msgs_length;
      typedef char* _rfid_tags_msgs_type;
      _rfid_tags_msgs_type st_rfid_tags_msgs;
      _rfid_tags_msgs_type * rfid_tags_msgs;
      uint32_t rfid_tags_dbs_length;
      typedef float _rfid_tags_dbs_type;
      _rfid_tags_dbs_type st_rfid_tags_dbs;
      _rfid_tags_dbs_type * rfid_tags_dbs;

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
      *(outbuffer + offset + 0) = (this->rfid_tags_ids_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->rfid_tags_ids_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->rfid_tags_ids_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->rfid_tags_ids_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rfid_tags_ids_length);
      for( uint32_t i = 0; i < rfid_tags_ids_length; i++){
      uint32_t length_rfid_tags_idsi = strlen(this->rfid_tags_ids[i]);
      varToArr(outbuffer + offset, length_rfid_tags_idsi);
      offset += 4;
      memcpy(outbuffer + offset, this->rfid_tags_ids[i], length_rfid_tags_idsi);
      offset += length_rfid_tags_idsi;
      }
      *(outbuffer + offset + 0) = (this->rfid_tags_msgs_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->rfid_tags_msgs_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->rfid_tags_msgs_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->rfid_tags_msgs_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rfid_tags_msgs_length);
      for( uint32_t i = 0; i < rfid_tags_msgs_length; i++){
      uint32_t length_rfid_tags_msgsi = strlen(this->rfid_tags_msgs[i]);
      varToArr(outbuffer + offset, length_rfid_tags_msgsi);
      offset += 4;
      memcpy(outbuffer + offset, this->rfid_tags_msgs[i], length_rfid_tags_msgsi);
      offset += length_rfid_tags_msgsi;
      }
      *(outbuffer + offset + 0) = (this->rfid_tags_dbs_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->rfid_tags_dbs_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->rfid_tags_dbs_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->rfid_tags_dbs_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rfid_tags_dbs_length);
      for( uint32_t i = 0; i < rfid_tags_dbs_length; i++){
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
      uint32_t rfid_tags_ids_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      rfid_tags_ids_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      rfid_tags_ids_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      rfid_tags_ids_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->rfid_tags_ids_length);
      if(rfid_tags_ids_lengthT > rfid_tags_ids_length)
        this->rfid_tags_ids = (char**)realloc(this->rfid_tags_ids, rfid_tags_ids_lengthT * sizeof(char*));
      rfid_tags_ids_length = rfid_tags_ids_lengthT;
      for( uint32_t i = 0; i < rfid_tags_ids_length; i++){
      uint32_t length_st_rfid_tags_ids;
      arrToVar(length_st_rfid_tags_ids, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_rfid_tags_ids; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_rfid_tags_ids-1]=0;
      this->st_rfid_tags_ids = (char *)(inbuffer + offset-1);
      offset += length_st_rfid_tags_ids;
        memcpy( &(this->rfid_tags_ids[i]), &(this->st_rfid_tags_ids), sizeof(char*));
      }
      uint32_t rfid_tags_msgs_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      rfid_tags_msgs_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      rfid_tags_msgs_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      rfid_tags_msgs_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->rfid_tags_msgs_length);
      if(rfid_tags_msgs_lengthT > rfid_tags_msgs_length)
        this->rfid_tags_msgs = (char**)realloc(this->rfid_tags_msgs, rfid_tags_msgs_lengthT * sizeof(char*));
      rfid_tags_msgs_length = rfid_tags_msgs_lengthT;
      for( uint32_t i = 0; i < rfid_tags_msgs_length; i++){
      uint32_t length_st_rfid_tags_msgs;
      arrToVar(length_st_rfid_tags_msgs, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_rfid_tags_msgs; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_rfid_tags_msgs-1]=0;
      this->st_rfid_tags_msgs = (char *)(inbuffer + offset-1);
      offset += length_st_rfid_tags_msgs;
        memcpy( &(this->rfid_tags_msgs[i]), &(this->st_rfid_tags_msgs), sizeof(char*));
      }
      uint32_t rfid_tags_dbs_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      rfid_tags_dbs_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      rfid_tags_dbs_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      rfid_tags_dbs_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->rfid_tags_dbs_length);
      if(rfid_tags_dbs_lengthT > rfid_tags_dbs_length)
        this->rfid_tags_dbs = (float*)realloc(this->rfid_tags_dbs, rfid_tags_dbs_lengthT * sizeof(float));
      rfid_tags_dbs_length = rfid_tags_dbs_lengthT;
      for( uint32_t i = 0; i < rfid_tags_dbs_length; i++){
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