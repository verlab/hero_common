#ifndef _ROS_SERVICE_SetCostmap_h
#define _ROS_SERVICE_SetCostmap_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace navfn
{

static const char SETCOSTMAP[] = "navfn/SetCostmap";

  class SetCostmapRequest : public ros::Msg
  {
    public:
      uint8_t costs_length;
      uint8_t st_costs;
      uint8_t * costs;
      uint16_t height;
      uint16_t width;

    SetCostmapRequest():
      costs_length(0), costs(NULL),
      height(0),
      width(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = costs_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < costs_length; i++){
      *(outbuffer + offset + 0) = (this->costs[i] >> (8 * 0)) & 0xFF;
      offset += sizeof(this->costs[i]);
      }
      *(outbuffer + offset + 0) = (this->height >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->height >> (8 * 1)) & 0xFF;
      offset += sizeof(this->height);
      *(outbuffer + offset + 0) = (this->width >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->width >> (8 * 1)) & 0xFF;
      offset += sizeof(this->width);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t costs_lengthT = *(inbuffer + offset++);
      if(costs_lengthT > costs_length)
        this->costs = (uint8_t*)realloc(this->costs, costs_lengthT * sizeof(uint8_t));
      offset += 3;
      costs_length = costs_lengthT;
      for( uint8_t i = 0; i < costs_length; i++){
      this->st_costs =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->st_costs);
        memcpy( &(this->costs[i]), &(this->st_costs), sizeof(uint8_t));
      }
      this->height =  ((uint16_t) (*(inbuffer + offset)));
      this->height |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->height);
      this->width =  ((uint16_t) (*(inbuffer + offset)));
      this->width |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->width);
     return offset;
    }

    const char * getType(){ return SETCOSTMAP; };
    const char * getMD5(){ return "370ec969cdb71f9cde7c7cbe0d752308"; };

  };

  class SetCostmapResponse : public ros::Msg
  {
    public:

    SetCostmapResponse()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return SETCOSTMAP; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class SetCostmap {
    public:
    typedef SetCostmapRequest Request;
    typedef SetCostmapResponse Response;
  };

}
#endif
