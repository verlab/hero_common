#ifndef _ROS_gateway_msgs_ConnectionStatistics_h
#define _ROS_gateway_msgs_ConnectionStatistics_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace gateway_msgs
{

  class ConnectionStatistics : public ros::Msg
  {
    public:
      typedef bool _gateway_available_type;
      _gateway_available_type gateway_available;
      typedef int64_t _time_since_last_seen_type;
      _time_since_last_seen_type time_since_last_seen;
      typedef float _ping_latency_min_type;
      _ping_latency_min_type ping_latency_min;
      typedef float _ping_latency_max_type;
      _ping_latency_max_type ping_latency_max;
      typedef float _ping_latency_avg_type;
      _ping_latency_avg_type ping_latency_avg;
      typedef float _ping_latency_mdev_type;
      _ping_latency_mdev_type ping_latency_mdev;
      typedef bool _network_info_available_type;
      _network_info_available_type network_info_available;
      typedef int8_t _network_type_type;
      _network_type_type network_type;
      typedef float _wireless_bitrate_type;
      _wireless_bitrate_type wireless_bitrate;
      typedef int8_t _wireless_link_quality_type;
      _wireless_link_quality_type wireless_link_quality;
      typedef float _wireless_signal_level_type;
      _wireless_signal_level_type wireless_signal_level;
      typedef float _wireless_noise_level_type;
      _wireless_noise_level_type wireless_noise_level;
      enum { WIRED =  1 };
      enum { WIRELESS =  2 };
      enum { MAX_TTL =  86400 };

    ConnectionStatistics():
      gateway_available(0),
      time_since_last_seen(0),
      ping_latency_min(0),
      ping_latency_max(0),
      ping_latency_avg(0),
      ping_latency_mdev(0),
      network_info_available(0),
      network_type(0),
      wireless_bitrate(0),
      wireless_link_quality(0),
      wireless_signal_level(0),
      wireless_noise_level(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_gateway_available;
      u_gateway_available.real = this->gateway_available;
      *(outbuffer + offset + 0) = (u_gateway_available.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->gateway_available);
      union {
        int64_t real;
        uint64_t base;
      } u_time_since_last_seen;
      u_time_since_last_seen.real = this->time_since_last_seen;
      *(outbuffer + offset + 0) = (u_time_since_last_seen.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_time_since_last_seen.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_time_since_last_seen.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_time_since_last_seen.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_time_since_last_seen.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_time_since_last_seen.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_time_since_last_seen.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_time_since_last_seen.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->time_since_last_seen);
      union {
        float real;
        uint32_t base;
      } u_ping_latency_min;
      u_ping_latency_min.real = this->ping_latency_min;
      *(outbuffer + offset + 0) = (u_ping_latency_min.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ping_latency_min.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ping_latency_min.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ping_latency_min.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ping_latency_min);
      union {
        float real;
        uint32_t base;
      } u_ping_latency_max;
      u_ping_latency_max.real = this->ping_latency_max;
      *(outbuffer + offset + 0) = (u_ping_latency_max.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ping_latency_max.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ping_latency_max.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ping_latency_max.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ping_latency_max);
      union {
        float real;
        uint32_t base;
      } u_ping_latency_avg;
      u_ping_latency_avg.real = this->ping_latency_avg;
      *(outbuffer + offset + 0) = (u_ping_latency_avg.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ping_latency_avg.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ping_latency_avg.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ping_latency_avg.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ping_latency_avg);
      union {
        float real;
        uint32_t base;
      } u_ping_latency_mdev;
      u_ping_latency_mdev.real = this->ping_latency_mdev;
      *(outbuffer + offset + 0) = (u_ping_latency_mdev.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ping_latency_mdev.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ping_latency_mdev.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ping_latency_mdev.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ping_latency_mdev);
      union {
        bool real;
        uint8_t base;
      } u_network_info_available;
      u_network_info_available.real = this->network_info_available;
      *(outbuffer + offset + 0) = (u_network_info_available.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->network_info_available);
      union {
        int8_t real;
        uint8_t base;
      } u_network_type;
      u_network_type.real = this->network_type;
      *(outbuffer + offset + 0) = (u_network_type.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->network_type);
      union {
        float real;
        uint32_t base;
      } u_wireless_bitrate;
      u_wireless_bitrate.real = this->wireless_bitrate;
      *(outbuffer + offset + 0) = (u_wireless_bitrate.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_wireless_bitrate.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_wireless_bitrate.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_wireless_bitrate.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->wireless_bitrate);
      union {
        int8_t real;
        uint8_t base;
      } u_wireless_link_quality;
      u_wireless_link_quality.real = this->wireless_link_quality;
      *(outbuffer + offset + 0) = (u_wireless_link_quality.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->wireless_link_quality);
      union {
        float real;
        uint32_t base;
      } u_wireless_signal_level;
      u_wireless_signal_level.real = this->wireless_signal_level;
      *(outbuffer + offset + 0) = (u_wireless_signal_level.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_wireless_signal_level.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_wireless_signal_level.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_wireless_signal_level.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->wireless_signal_level);
      union {
        float real;
        uint32_t base;
      } u_wireless_noise_level;
      u_wireless_noise_level.real = this->wireless_noise_level;
      *(outbuffer + offset + 0) = (u_wireless_noise_level.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_wireless_noise_level.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_wireless_noise_level.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_wireless_noise_level.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->wireless_noise_level);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_gateway_available;
      u_gateway_available.base = 0;
      u_gateway_available.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->gateway_available = u_gateway_available.real;
      offset += sizeof(this->gateway_available);
      union {
        int64_t real;
        uint64_t base;
      } u_time_since_last_seen;
      u_time_since_last_seen.base = 0;
      u_time_since_last_seen.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_time_since_last_seen.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_time_since_last_seen.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_time_since_last_seen.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_time_since_last_seen.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_time_since_last_seen.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_time_since_last_seen.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_time_since_last_seen.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->time_since_last_seen = u_time_since_last_seen.real;
      offset += sizeof(this->time_since_last_seen);
      union {
        float real;
        uint32_t base;
      } u_ping_latency_min;
      u_ping_latency_min.base = 0;
      u_ping_latency_min.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ping_latency_min.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ping_latency_min.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ping_latency_min.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ping_latency_min = u_ping_latency_min.real;
      offset += sizeof(this->ping_latency_min);
      union {
        float real;
        uint32_t base;
      } u_ping_latency_max;
      u_ping_latency_max.base = 0;
      u_ping_latency_max.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ping_latency_max.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ping_latency_max.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ping_latency_max.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ping_latency_max = u_ping_latency_max.real;
      offset += sizeof(this->ping_latency_max);
      union {
        float real;
        uint32_t base;
      } u_ping_latency_avg;
      u_ping_latency_avg.base = 0;
      u_ping_latency_avg.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ping_latency_avg.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ping_latency_avg.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ping_latency_avg.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ping_latency_avg = u_ping_latency_avg.real;
      offset += sizeof(this->ping_latency_avg);
      union {
        float real;
        uint32_t base;
      } u_ping_latency_mdev;
      u_ping_latency_mdev.base = 0;
      u_ping_latency_mdev.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ping_latency_mdev.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ping_latency_mdev.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ping_latency_mdev.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ping_latency_mdev = u_ping_latency_mdev.real;
      offset += sizeof(this->ping_latency_mdev);
      union {
        bool real;
        uint8_t base;
      } u_network_info_available;
      u_network_info_available.base = 0;
      u_network_info_available.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->network_info_available = u_network_info_available.real;
      offset += sizeof(this->network_info_available);
      union {
        int8_t real;
        uint8_t base;
      } u_network_type;
      u_network_type.base = 0;
      u_network_type.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->network_type = u_network_type.real;
      offset += sizeof(this->network_type);
      union {
        float real;
        uint32_t base;
      } u_wireless_bitrate;
      u_wireless_bitrate.base = 0;
      u_wireless_bitrate.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_wireless_bitrate.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_wireless_bitrate.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_wireless_bitrate.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->wireless_bitrate = u_wireless_bitrate.real;
      offset += sizeof(this->wireless_bitrate);
      union {
        int8_t real;
        uint8_t base;
      } u_wireless_link_quality;
      u_wireless_link_quality.base = 0;
      u_wireless_link_quality.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->wireless_link_quality = u_wireless_link_quality.real;
      offset += sizeof(this->wireless_link_quality);
      union {
        float real;
        uint32_t base;
      } u_wireless_signal_level;
      u_wireless_signal_level.base = 0;
      u_wireless_signal_level.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_wireless_signal_level.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_wireless_signal_level.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_wireless_signal_level.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->wireless_signal_level = u_wireless_signal_level.real;
      offset += sizeof(this->wireless_signal_level);
      union {
        float real;
        uint32_t base;
      } u_wireless_noise_level;
      u_wireless_noise_level.base = 0;
      u_wireless_noise_level.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_wireless_noise_level.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_wireless_noise_level.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_wireless_noise_level.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->wireless_noise_level = u_wireless_noise_level.real;
      offset += sizeof(this->wireless_noise_level);
     return offset;
    }

    const char * getType(){ return "gateway_msgs/ConnectionStatistics"; };
    const char * getMD5(){ return "672067d5ab3e6157dcf8224022da3ee6"; };

  };

}
#endif