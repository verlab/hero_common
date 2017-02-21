#ifndef _ROS_SERVICE_SaveAnnotationsData_h
#define _ROS_SERVICE_SaveAnnotationsData_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "world_canvas_msgs/AnnotationData.h"
#include "world_canvas_msgs/Annotation.h"

namespace world_canvas_msgs
{

static const char SAVEANNOTATIONSDATA[] = "world_canvas_msgs/SaveAnnotationsData";

  class SaveAnnotationsDataRequest : public ros::Msg
  {
    public:
      uint8_t annotations_length;
      world_canvas_msgs::Annotation st_annotations;
      world_canvas_msgs::Annotation * annotations;
      uint8_t data_length;
      world_canvas_msgs::AnnotationData st_data;
      world_canvas_msgs::AnnotationData * data;

    SaveAnnotationsDataRequest():
      annotations_length(0), annotations(NULL),
      data_length(0), data(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = annotations_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < annotations_length; i++){
      offset += this->annotations[i].serialize(outbuffer + offset);
      }
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
      uint8_t annotations_lengthT = *(inbuffer + offset++);
      if(annotations_lengthT > annotations_length)
        this->annotations = (world_canvas_msgs::Annotation*)realloc(this->annotations, annotations_lengthT * sizeof(world_canvas_msgs::Annotation));
      offset += 3;
      annotations_length = annotations_lengthT;
      for( uint8_t i = 0; i < annotations_length; i++){
      offset += this->st_annotations.deserialize(inbuffer + offset);
        memcpy( &(this->annotations[i]), &(this->st_annotations), sizeof(world_canvas_msgs::Annotation));
      }
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

    const char * getType(){ return SAVEANNOTATIONSDATA; };
    const char * getMD5(){ return "d204dc5afba8bb6886ec4a83711f9c6e"; };

  };

  class SaveAnnotationsDataResponse : public ros::Msg
  {
    public:
      bool result;
      const char* message;

    SaveAnnotationsDataResponse():
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

    const char * getType(){ return SAVEANNOTATIONSDATA; };
    const char * getMD5(){ return "b543fbd3518c791be28589b850702201"; };

  };

  class SaveAnnotationsData {
    public:
    typedef SaveAnnotationsDataRequest Request;
    typedef SaveAnnotationsDataResponse Response;
  };

}
#endif
