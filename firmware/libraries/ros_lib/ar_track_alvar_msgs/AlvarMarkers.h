#ifndef _ROS_ar_track_alvar_msgs_AlvarMarkers_h
#define _ROS_ar_track_alvar_msgs_AlvarMarkers_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "ar_track_alvar_msgs/AlvarMarker.h"

namespace ar_track_alvar_msgs
{

  class AlvarMarkers : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t markers_length;
      ar_track_alvar_msgs::AlvarMarker st_markers;
      ar_track_alvar_msgs::AlvarMarker * markers;

    AlvarMarkers():
      header(),
      markers_length(0), markers(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = markers_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < markers_length; i++){
      offset += this->markers[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t markers_lengthT = *(inbuffer + offset++);
      if(markers_lengthT > markers_length)
        this->markers = (ar_track_alvar_msgs::AlvarMarker*)realloc(this->markers, markers_lengthT * sizeof(ar_track_alvar_msgs::AlvarMarker));
      offset += 3;
      markers_length = markers_lengthT;
      for( uint8_t i = 0; i < markers_length; i++){
      offset += this->st_markers.deserialize(inbuffer + offset);
        memcpy( &(this->markers[i]), &(this->st_markers), sizeof(ar_track_alvar_msgs::AlvarMarker));
      }
     return offset;
    }

    const char * getType(){ return "ar_track_alvar_msgs/AlvarMarkers"; };
    const char * getMD5(){ return "943fe17bfb0b4ea7890368d0b25ad0ad"; };

  };

}
#endif