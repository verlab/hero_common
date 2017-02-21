#ifndef _ROS_SERVICE_GetAnnotationsData_h
#define _ROS_SERVICE_GetAnnotationsData_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "world_canvas_msgs/AnnotationData.h"
#include "uuid_msgs/UniqueID.h"

namespace world_canvas_msgs
{

static const char GETANNOTATIONSDATA[] = "world_canvas_msgs/GetAnnotationsData";

  class GetAnnotationsDataRequest : public ros::Msg
  {
    public:
      uint8_t annotation_ids_length;
      uuid_msgs::UniqueID st_annotation_ids;
      uuid_msgs::UniqueID * annotation_ids;

    GetAnnotationsDataRequest():
      annotation_ids_length(0), annotation_ids(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = annotation_ids_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < annotation_ids_length; i++){
      offset += this->annotation_ids[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t annotation_ids_lengthT = *(inbuffer + offset++);
      if(annotation_ids_lengthT > annotation_ids_length)
        this->annotation_ids = (uuid_msgs::UniqueID*)realloc(this->annotation_ids, annotation_ids_lengthT * sizeof(uuid_msgs::UniqueID));
      offset += 3;
      annotation_ids_length = annotation_ids_lengthT;
      for( uint8_t i = 0; i < annotation_ids_length; i++){
      offset += this->st_annotation_ids.deserialize(inbuffer + offset);
        memcpy( &(this->annotation_ids[i]), &(this->st_annotation_ids), sizeof(uuid_msgs::UniqueID));
      }
     return offset;
    }

    const char * getType(){ return GETANNOTATIONSDATA; };
    const char * getMD5(){ return "fc0f6207fc1c9b03add292ade8ff7951"; };

  };

  class GetAnnotationsDataResponse : public ros::Msg
  {
    public:
      bool result;
      const char* message;
      uint8_t data_length;
      world_canvas_msgs::AnnotationData st_data;
      world_canvas_msgs::AnnotationData * data;

    GetAnnotationsDataResponse():
      result(0),
      message(""),
      data_length(0), data(NULL)
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
      *(outbuffer + offset++) = data_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < data_length; i++){
      offset += this->data[i].serialize(outbuffer + offset);
      }
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
      uint8_t data_lengthT = *(inbuffer + offset++);
      if(data_lengthT > data_length)
        this->data = (world_canvas_msgs::AnnotationData*)realloc(this->data, data_lengthT * sizeof(world_canvas_msgs::AnnotationData));
      offset += 3;
      data_length = data_lengthT;
      for( uint8_t i = 0; i < data_length; i++){
      offset += this->st_data.deserialize(inbuffer + offset);
        memcpy( &(this->data[i]), &(this->st_data), sizeof(world_canvas_msgs::AnnotationData));
      }
     return offset;
    }

    const char * getType(){ return GETANNOTATIONSDATA; };
    const char * getMD5(){ return "5138c2b0e307350745b95b31397311c4"; };

  };

  class GetAnnotationsData {
    public:
    typedef GetAnnotationsDataRequest Request;
    typedef GetAnnotationsDataResponse Response;
  };

}
#endif
