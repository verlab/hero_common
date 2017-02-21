#ifndef _ROS_SERVICE_RemoteGatewayInfo_h
#define _ROS_SERVICE_RemoteGatewayInfo_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "gateway_msgs/RemoteGateway.h"

namespace gateway_msgs
{

static const char REMOTEGATEWAYINFO[] = "gateway_msgs/RemoteGatewayInfo";

  class RemoteGatewayInfoRequest : public ros::Msg
  {
    public:
      uint8_t gateways_length;
      char* st_gateways;
      char* * gateways;

    RemoteGatewayInfoRequest():
      gateways_length(0), gateways(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = gateways_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < gateways_length; i++){
      uint32_t length_gatewaysi = strlen(this->gateways[i]);
      memcpy(outbuffer + offset, &length_gatewaysi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->gateways[i], length_gatewaysi);
      offset += length_gatewaysi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t gateways_lengthT = *(inbuffer + offset++);
      if(gateways_lengthT > gateways_length)
        this->gateways = (char**)realloc(this->gateways, gateways_lengthT * sizeof(char*));
      offset += 3;
      gateways_length = gateways_lengthT;
      for( uint8_t i = 0; i < gateways_length; i++){
      uint32_t length_st_gateways;
      memcpy(&length_st_gateways, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_gateways; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_gateways-1]=0;
      this->st_gateways = (char *)(inbuffer + offset-1);
      offset += length_st_gateways;
        memcpy( &(this->gateways[i]), &(this->st_gateways), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return REMOTEGATEWAYINFO; };
    const char * getMD5(){ return "e005eaac1f4b29980f211758e562aa6e"; };

  };

  class RemoteGatewayInfoResponse : public ros::Msg
  {
    public:
      uint8_t gateways_length;
      gateway_msgs::RemoteGateway st_gateways;
      gateway_msgs::RemoteGateway * gateways;

    RemoteGatewayInfoResponse():
      gateways_length(0), gateways(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = gateways_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < gateways_length; i++){
      offset += this->gateways[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t gateways_lengthT = *(inbuffer + offset++);
      if(gateways_lengthT > gateways_length)
        this->gateways = (gateway_msgs::RemoteGateway*)realloc(this->gateways, gateways_lengthT * sizeof(gateway_msgs::RemoteGateway));
      offset += 3;
      gateways_length = gateways_lengthT;
      for( uint8_t i = 0; i < gateways_length; i++){
      offset += this->st_gateways.deserialize(inbuffer + offset);
        memcpy( &(this->gateways[i]), &(this->st_gateways), sizeof(gateway_msgs::RemoteGateway));
      }
     return offset;
    }

    const char * getType(){ return REMOTEGATEWAYINFO; };
    const char * getMD5(){ return "21c329af996537695f35402c601485df"; };

  };

  class RemoteGatewayInfo {
    public:
    typedef RemoteGatewayInfoRequest Request;
    typedef RemoteGatewayInfoResponse Response;
  };

}
#endif
