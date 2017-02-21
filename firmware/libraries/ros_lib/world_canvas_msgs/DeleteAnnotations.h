#ifndef _ROS_SERVICE_DeleteAnnotations_h
#define _ROS_SERVICE_DeleteAnnotations_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "world_canvas_msgs/Annotation.h"

namespace world_canvas_msgs
{

static const char DELETEANNOTATIONS[] = "world_canvas_msgs/DeleteAnnotations";

  class DeleteAnnotationsRequest : public ros::Msg
  {
    public:
      uint8_t annotations_length;
      world_canvas_msgs::Annotation st_annotations;
      world_canvas_msgs::Annotation * annotations;

    DeleteAnnotationsRequest():
      annotations_length(0), annotations(NULL)
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
     return offset;
    }

    const char * getType(){ return DELETEANNOTATIONS; };
    const char * getMD5(){ return "6b941e3af02d0efb14244aea9406f778"; };

  };

  class DeleteAnnotationsResponse : public ros::Msg
  {
    public:
      bool result;
      const char* message;

    DeleteAnnotationsResponse():
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

    const char * getType(){ return DELETEANNOTATIONS; };
    const char * getMD5(){ return "b543fbd3518c791be28589b850702201"; };

  };

  class DeleteAnnotations {
    public:
    typedef DeleteAnnotationsRequest Request;
    typedef DeleteAnnotationsResponse Response;
  };

}
#endif
