#ifndef _ROS_SERVICE_ListPublishedServices_h
#define _ROS_SERVICE_ListPublishedServices_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "zeroconf_msgs/PublishedService.h"

namespace zeroconf_msgs
{

static const char LISTPUBLISHEDSERVICES[] = "zeroconf_msgs/ListPublishedServices";

  class ListPublishedServicesRequest : public ros::Msg
  {
    public:
      const char* service_type;

    ListPublishedServicesRequest():
      service_type("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_service_type = strlen(this->service_type);
      memcpy(outbuffer + offset, &length_service_type, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->service_type, length_service_type);
      offset += length_service_type;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_service_type;
      memcpy(&length_service_type, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_service_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_service_type-1]=0;
      this->service_type = (char *)(inbuffer + offset-1);
      offset += length_service_type;
     return offset;
    }

    const char * getType(){ return LISTPUBLISHEDSERVICES; };
    const char * getMD5(){ return "e1bf1fd6519c823d87c16f342a193a85"; };

  };

  class ListPublishedServicesResponse : public ros::Msg
  {
    public:
      uint8_t services_length;
      zeroconf_msgs::PublishedService st_services;
      zeroconf_msgs::PublishedService * services;

    ListPublishedServicesResponse():
      services_length(0), services(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = services_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < services_length; i++){
      offset += this->services[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t services_lengthT = *(inbuffer + offset++);
      if(services_lengthT > services_length)
        this->services = (zeroconf_msgs::PublishedService*)realloc(this->services, services_lengthT * sizeof(zeroconf_msgs::PublishedService));
      offset += 3;
      services_length = services_lengthT;
      for( uint8_t i = 0; i < services_length; i++){
      offset += this->st_services.deserialize(inbuffer + offset);
        memcpy( &(this->services[i]), &(this->st_services), sizeof(zeroconf_msgs::PublishedService));
      }
     return offset;
    }

    const char * getType(){ return LISTPUBLISHEDSERVICES; };
    const char * getMD5(){ return "12aaabf9e3957c5a3d8c742745b6d97d"; };

  };

  class ListPublishedServices {
    public:
    typedef ListPublishedServicesRequest Request;
    typedef ListPublishedServicesResponse Response;
  };

}
#endif
