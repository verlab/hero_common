#ifndef _ROS_SERVICE_EditAnnotationsData_h
#define _ROS_SERVICE_EditAnnotationsData_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "world_canvas_msgs/AnnotationData.h"
#include "world_canvas_msgs/Annotation.h"

namespace world_canvas_msgs
{

static const char EDITANNOTATIONSDATA[] = "world_canvas_msgs/EditAnnotationsData";

  class EditAnnotationsDataRequest : public ros::Msg
  {
    public:
      typedef uint8_t _action_type;
      _action_type action;
      typedef world_canvas_msgs::Annotation _annotation_type;
      _annotation_type annotation;
      typedef world_canvas_msgs::AnnotationData _data_type;
      _data_type data;
      enum { NEW = 0 };
      enum { EDIT = 1 };

    EditAnnotationsDataRequest():
      action(0),
      annotation(),
      data()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->action >> (8 * 0)) & 0xFF;
      offset += sizeof(this->action);
      offset += this->annotation.serialize(outbuffer + offset);
      offset += this->data.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->action =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->action);
      offset += this->annotation.deserialize(inbuffer + offset);
      offset += this->data.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return EDITANNOTATIONSDATA; };
    const char * getMD5(){ return "41ee6a631a74d3fee28d7fa0847f92d3"; };

  };

  class EditAnnotationsDataResponse : public ros::Msg
  {
    public:
      typedef uint8_t _action_type;
      _action_type action;
      typedef world_canvas_msgs::AnnotationData _data_type;
      _data_type data;
      enum { UPDATE = 10 };
      enum { DELETE = 12 };
      enum { CANCEL = 13 };

    EditAnnotationsDataResponse():
      action(0),
      data()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->action >> (8 * 0)) & 0xFF;
      offset += sizeof(this->action);
      offset += this->data.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->action =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->action);
      offset += this->data.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return EDITANNOTATIONSDATA; };
    const char * getMD5(){ return "f3d451f2a08e1dc3084d378560b01c8e"; };

  };

  class EditAnnotationsData {
    public:
    typedef EditAnnotationsDataRequest Request;
    typedef EditAnnotationsDataResponse Response;
  };

}
#endif
