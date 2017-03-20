#ifndef _ROS_create_node_RawTurtlebotSensorState_h
#define _ROS_create_node_RawTurtlebotSensorState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace create_node
{

  class RawTurtlebotSensorState : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef uint8_t _bumps_wheeldrops_type;
      _bumps_wheeldrops_type bumps_wheeldrops;
      typedef bool _wall_type;
      _wall_type wall;
      typedef bool _cliff_left_type;
      _cliff_left_type cliff_left;
      typedef bool _cliff_front_left_type;
      _cliff_front_left_type cliff_front_left;
      typedef bool _cliff_front_right_type;
      _cliff_front_right_type cliff_front_right;
      typedef bool _cliff_right_type;
      _cliff_right_type cliff_right;
      typedef bool _virtual_wall_type;
      _virtual_wall_type virtual_wall;
      typedef uint8_t _motor_overcurrents_type;
      _motor_overcurrents_type motor_overcurrents;
      typedef uint8_t _dirt_detector_left_type;
      _dirt_detector_left_type dirt_detector_left;
      typedef uint8_t _dirt_detector_right_type;
      _dirt_detector_right_type dirt_detector_right;
      typedef uint8_t _remote_opcode_type;
      _remote_opcode_type remote_opcode;
      typedef uint8_t _buttons_type;
      _buttons_type buttons;
      typedef int16_t _distance_type;
      _distance_type distance;
      typedef int16_t _angle_type;
      _angle_type angle;
      typedef uint8_t _charging_state_type;
      _charging_state_type charging_state;
      typedef uint16_t _voltage_type;
      _voltage_type voltage;
      typedef int16_t _current_type;
      _current_type current;
      typedef int8_t _temperature_type;
      _temperature_type temperature;
      typedef uint16_t _charge_type;
      _charge_type charge;
      typedef uint16_t _capacity_type;
      _capacity_type capacity;
      typedef uint16_t _wall_signal_type;
      _wall_signal_type wall_signal;
      typedef uint16_t _cliff_left_signal_type;
      _cliff_left_signal_type cliff_left_signal;
      typedef uint16_t _cliff_front_left_signal_type;
      _cliff_front_left_signal_type cliff_front_left_signal;
      typedef uint16_t _cliff_front_right_signal_type;
      _cliff_front_right_signal_type cliff_front_right_signal;
      typedef uint16_t _cliff_right_signal_type;
      _cliff_right_signal_type cliff_right_signal;
      typedef uint8_t _user_digital_inputs_type;
      _user_digital_inputs_type user_digital_inputs;
      typedef uint16_t _user_analog_input_type;
      _user_analog_input_type user_analog_input;
      typedef uint8_t _charging_sources_available_type;
      _charging_sources_available_type charging_sources_available;
      typedef uint8_t _oi_mode_type;
      _oi_mode_type oi_mode;
      typedef uint8_t _song_number_type;
      _song_number_type song_number;
      typedef bool _song_playing_type;
      _song_playing_type song_playing;
      typedef uint8_t _number_of_stream_packets_type;
      _number_of_stream_packets_type number_of_stream_packets;
      typedef int16_t _requested_velocity_type;
      _requested_velocity_type requested_velocity;
      typedef int16_t _requested_radius_type;
      _requested_radius_type requested_radius;
      typedef int16_t _requested_right_velocity_type;
      _requested_right_velocity_type requested_right_velocity;
      typedef int16_t _requested_left_velocity_type;
      _requested_left_velocity_type requested_left_velocity;
      enum { OI_MODE_OFF =  0 };
      enum { OI_MODE_PASSIVE =  1 };
      enum { OI_MODE_SAFE =  2 };
      enum { OI_MODE_FULL =  3 };
      enum { REMOTE_LEFT =  129 };
      enum { REMOTE_FORWARD =  130 };
      enum { REMOTE_RIGHT =  131 };
      enum { REMOTE_SPOT =  132 };
      enum { REMOTE_MAX =  133 };
      enum { REMOTE_SMALL =  134 };
      enum { REMOTE_MEDIUM =  135 };
      enum { REMOTE_LARGE =  136 };
      enum { REMOTE_CLEAN =  136 };
      enum { REMOTE_PAUSE =  137 };
      enum { REMOTE_POWER =  138 };
      enum { REMOTE_ARC_LEFT =  139 };
      enum { REMOTE_ARC_RIGHT =  140 };
      enum { REMOTE_DRIVE_STOP =  141 };
      enum { REMOTE_SEND_ALL =  142 };
      enum { REMOTE_SEEK_DOCK =  143 };
      enum { REMOTE_RESERVED =  240 };
      enum { REMOTE_FORCE_FIELD =  242 };
      enum { REMOTE_GREEN_BUOY =  244 };
      enum { REMOTE_GREEN_BUOY_AND_FORCE_FIELD =  246 };
      enum { REMOTE_RED_BUOY =  248 };
      enum { REMOTE_RED_BUOY_AND_FORCE_FIELD =  250 };
      enum { REMOTE_RED_BUOY_AND_GREEN_BUOY =  252 };
      enum { REMOTE_RED_BUOY_AND_GREEN_BUOY_AND_FORCE_FIELD =  254 };
      enum { REMOTE_NONE =  255 };
      enum { CHARGING_NOT_CHARGING =  0 };
      enum { CHARGING_CHARGING_RECOVERY =  1 };
      enum { CHARGING_CHARGING =  2 };
      enum { CHARGING_TRICKLE_CHARGING =  3 };
      enum { CHARGING_WAITING =  4 };
      enum { CHARGING_CHARGING_ERROR =  5 };

    RawTurtlebotSensorState():
      header(),
      bumps_wheeldrops(0),
      wall(0),
      cliff_left(0),
      cliff_front_left(0),
      cliff_front_right(0),
      cliff_right(0),
      virtual_wall(0),
      motor_overcurrents(0),
      dirt_detector_left(0),
      dirt_detector_right(0),
      remote_opcode(0),
      buttons(0),
      distance(0),
      angle(0),
      charging_state(0),
      voltage(0),
      current(0),
      temperature(0),
      charge(0),
      capacity(0),
      wall_signal(0),
      cliff_left_signal(0),
      cliff_front_left_signal(0),
      cliff_front_right_signal(0),
      cliff_right_signal(0),
      user_digital_inputs(0),
      user_analog_input(0),
      charging_sources_available(0),
      oi_mode(0),
      song_number(0),
      song_playing(0),
      number_of_stream_packets(0),
      requested_velocity(0),
      requested_radius(0),
      requested_right_velocity(0),
      requested_left_velocity(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->bumps_wheeldrops >> (8 * 0)) & 0xFF;
      offset += sizeof(this->bumps_wheeldrops);
      union {
        bool real;
        uint8_t base;
      } u_wall;
      u_wall.real = this->wall;
      *(outbuffer + offset + 0) = (u_wall.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->wall);
      union {
        bool real;
        uint8_t base;
      } u_cliff_left;
      u_cliff_left.real = this->cliff_left;
      *(outbuffer + offset + 0) = (u_cliff_left.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->cliff_left);
      union {
        bool real;
        uint8_t base;
      } u_cliff_front_left;
      u_cliff_front_left.real = this->cliff_front_left;
      *(outbuffer + offset + 0) = (u_cliff_front_left.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->cliff_front_left);
      union {
        bool real;
        uint8_t base;
      } u_cliff_front_right;
      u_cliff_front_right.real = this->cliff_front_right;
      *(outbuffer + offset + 0) = (u_cliff_front_right.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->cliff_front_right);
      union {
        bool real;
        uint8_t base;
      } u_cliff_right;
      u_cliff_right.real = this->cliff_right;
      *(outbuffer + offset + 0) = (u_cliff_right.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->cliff_right);
      union {
        bool real;
        uint8_t base;
      } u_virtual_wall;
      u_virtual_wall.real = this->virtual_wall;
      *(outbuffer + offset + 0) = (u_virtual_wall.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->virtual_wall);
      *(outbuffer + offset + 0) = (this->motor_overcurrents >> (8 * 0)) & 0xFF;
      offset += sizeof(this->motor_overcurrents);
      *(outbuffer + offset + 0) = (this->dirt_detector_left >> (8 * 0)) & 0xFF;
      offset += sizeof(this->dirt_detector_left);
      *(outbuffer + offset + 0) = (this->dirt_detector_right >> (8 * 0)) & 0xFF;
      offset += sizeof(this->dirt_detector_right);
      *(outbuffer + offset + 0) = (this->remote_opcode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->remote_opcode);
      *(outbuffer + offset + 0) = (this->buttons >> (8 * 0)) & 0xFF;
      offset += sizeof(this->buttons);
      union {
        int16_t real;
        uint16_t base;
      } u_distance;
      u_distance.real = this->distance;
      *(outbuffer + offset + 0) = (u_distance.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_distance.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->distance);
      union {
        int16_t real;
        uint16_t base;
      } u_angle;
      u_angle.real = this->angle;
      *(outbuffer + offset + 0) = (u_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angle.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->angle);
      *(outbuffer + offset + 0) = (this->charging_state >> (8 * 0)) & 0xFF;
      offset += sizeof(this->charging_state);
      *(outbuffer + offset + 0) = (this->voltage >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->voltage >> (8 * 1)) & 0xFF;
      offset += sizeof(this->voltage);
      union {
        int16_t real;
        uint16_t base;
      } u_current;
      u_current.real = this->current;
      *(outbuffer + offset + 0) = (u_current.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_current.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->current);
      union {
        int8_t real;
        uint8_t base;
      } u_temperature;
      u_temperature.real = this->temperature;
      *(outbuffer + offset + 0) = (u_temperature.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->temperature);
      *(outbuffer + offset + 0) = (this->charge >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->charge >> (8 * 1)) & 0xFF;
      offset += sizeof(this->charge);
      *(outbuffer + offset + 0) = (this->capacity >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->capacity >> (8 * 1)) & 0xFF;
      offset += sizeof(this->capacity);
      *(outbuffer + offset + 0) = (this->wall_signal >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->wall_signal >> (8 * 1)) & 0xFF;
      offset += sizeof(this->wall_signal);
      *(outbuffer + offset + 0) = (this->cliff_left_signal >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->cliff_left_signal >> (8 * 1)) & 0xFF;
      offset += sizeof(this->cliff_left_signal);
      *(outbuffer + offset + 0) = (this->cliff_front_left_signal >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->cliff_front_left_signal >> (8 * 1)) & 0xFF;
      offset += sizeof(this->cliff_front_left_signal);
      *(outbuffer + offset + 0) = (this->cliff_front_right_signal >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->cliff_front_right_signal >> (8 * 1)) & 0xFF;
      offset += sizeof(this->cliff_front_right_signal);
      *(outbuffer + offset + 0) = (this->cliff_right_signal >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->cliff_right_signal >> (8 * 1)) & 0xFF;
      offset += sizeof(this->cliff_right_signal);
      *(outbuffer + offset + 0) = (this->user_digital_inputs >> (8 * 0)) & 0xFF;
      offset += sizeof(this->user_digital_inputs);
      *(outbuffer + offset + 0) = (this->user_analog_input >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->user_analog_input >> (8 * 1)) & 0xFF;
      offset += sizeof(this->user_analog_input);
      *(outbuffer + offset + 0) = (this->charging_sources_available >> (8 * 0)) & 0xFF;
      offset += sizeof(this->charging_sources_available);
      *(outbuffer + offset + 0) = (this->oi_mode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->oi_mode);
      *(outbuffer + offset + 0) = (this->song_number >> (8 * 0)) & 0xFF;
      offset += sizeof(this->song_number);
      union {
        bool real;
        uint8_t base;
      } u_song_playing;
      u_song_playing.real = this->song_playing;
      *(outbuffer + offset + 0) = (u_song_playing.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->song_playing);
      *(outbuffer + offset + 0) = (this->number_of_stream_packets >> (8 * 0)) & 0xFF;
      offset += sizeof(this->number_of_stream_packets);
      union {
        int16_t real;
        uint16_t base;
      } u_requested_velocity;
      u_requested_velocity.real = this->requested_velocity;
      *(outbuffer + offset + 0) = (u_requested_velocity.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_requested_velocity.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->requested_velocity);
      union {
        int16_t real;
        uint16_t base;
      } u_requested_radius;
      u_requested_radius.real = this->requested_radius;
      *(outbuffer + offset + 0) = (u_requested_radius.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_requested_radius.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->requested_radius);
      union {
        int16_t real;
        uint16_t base;
      } u_requested_right_velocity;
      u_requested_right_velocity.real = this->requested_right_velocity;
      *(outbuffer + offset + 0) = (u_requested_right_velocity.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_requested_right_velocity.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->requested_right_velocity);
      union {
        int16_t real;
        uint16_t base;
      } u_requested_left_velocity;
      u_requested_left_velocity.real = this->requested_left_velocity;
      *(outbuffer + offset + 0) = (u_requested_left_velocity.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_requested_left_velocity.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->requested_left_velocity);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->bumps_wheeldrops =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->bumps_wheeldrops);
      union {
        bool real;
        uint8_t base;
      } u_wall;
      u_wall.base = 0;
      u_wall.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->wall = u_wall.real;
      offset += sizeof(this->wall);
      union {
        bool real;
        uint8_t base;
      } u_cliff_left;
      u_cliff_left.base = 0;
      u_cliff_left.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->cliff_left = u_cliff_left.real;
      offset += sizeof(this->cliff_left);
      union {
        bool real;
        uint8_t base;
      } u_cliff_front_left;
      u_cliff_front_left.base = 0;
      u_cliff_front_left.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->cliff_front_left = u_cliff_front_left.real;
      offset += sizeof(this->cliff_front_left);
      union {
        bool real;
        uint8_t base;
      } u_cliff_front_right;
      u_cliff_front_right.base = 0;
      u_cliff_front_right.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->cliff_front_right = u_cliff_front_right.real;
      offset += sizeof(this->cliff_front_right);
      union {
        bool real;
        uint8_t base;
      } u_cliff_right;
      u_cliff_right.base = 0;
      u_cliff_right.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->cliff_right = u_cliff_right.real;
      offset += sizeof(this->cliff_right);
      union {
        bool real;
        uint8_t base;
      } u_virtual_wall;
      u_virtual_wall.base = 0;
      u_virtual_wall.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->virtual_wall = u_virtual_wall.real;
      offset += sizeof(this->virtual_wall);
      this->motor_overcurrents =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->motor_overcurrents);
      this->dirt_detector_left =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->dirt_detector_left);
      this->dirt_detector_right =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->dirt_detector_right);
      this->remote_opcode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->remote_opcode);
      this->buttons =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->buttons);
      union {
        int16_t real;
        uint16_t base;
      } u_distance;
      u_distance.base = 0;
      u_distance.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_distance.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->distance = u_distance.real;
      offset += sizeof(this->distance);
      union {
        int16_t real;
        uint16_t base;
      } u_angle;
      u_angle.base = 0;
      u_angle.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angle.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->angle = u_angle.real;
      offset += sizeof(this->angle);
      this->charging_state =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->charging_state);
      this->voltage =  ((uint16_t) (*(inbuffer + offset)));
      this->voltage |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->voltage);
      union {
        int16_t real;
        uint16_t base;
      } u_current;
      u_current.base = 0;
      u_current.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_current.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->current = u_current.real;
      offset += sizeof(this->current);
      union {
        int8_t real;
        uint8_t base;
      } u_temperature;
      u_temperature.base = 0;
      u_temperature.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->temperature = u_temperature.real;
      offset += sizeof(this->temperature);
      this->charge =  ((uint16_t) (*(inbuffer + offset)));
      this->charge |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->charge);
      this->capacity =  ((uint16_t) (*(inbuffer + offset)));
      this->capacity |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->capacity);
      this->wall_signal =  ((uint16_t) (*(inbuffer + offset)));
      this->wall_signal |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->wall_signal);
      this->cliff_left_signal =  ((uint16_t) (*(inbuffer + offset)));
      this->cliff_left_signal |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->cliff_left_signal);
      this->cliff_front_left_signal =  ((uint16_t) (*(inbuffer + offset)));
      this->cliff_front_left_signal |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->cliff_front_left_signal);
      this->cliff_front_right_signal =  ((uint16_t) (*(inbuffer + offset)));
      this->cliff_front_right_signal |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->cliff_front_right_signal);
      this->cliff_right_signal =  ((uint16_t) (*(inbuffer + offset)));
      this->cliff_right_signal |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->cliff_right_signal);
      this->user_digital_inputs =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->user_digital_inputs);
      this->user_analog_input =  ((uint16_t) (*(inbuffer + offset)));
      this->user_analog_input |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->user_analog_input);
      this->charging_sources_available =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->charging_sources_available);
      this->oi_mode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->oi_mode);
      this->song_number =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->song_number);
      union {
        bool real;
        uint8_t base;
      } u_song_playing;
      u_song_playing.base = 0;
      u_song_playing.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->song_playing = u_song_playing.real;
      offset += sizeof(this->song_playing);
      this->number_of_stream_packets =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->number_of_stream_packets);
      union {
        int16_t real;
        uint16_t base;
      } u_requested_velocity;
      u_requested_velocity.base = 0;
      u_requested_velocity.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_requested_velocity.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->requested_velocity = u_requested_velocity.real;
      offset += sizeof(this->requested_velocity);
      union {
        int16_t real;
        uint16_t base;
      } u_requested_radius;
      u_requested_radius.base = 0;
      u_requested_radius.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_requested_radius.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->requested_radius = u_requested_radius.real;
      offset += sizeof(this->requested_radius);
      union {
        int16_t real;
        uint16_t base;
      } u_requested_right_velocity;
      u_requested_right_velocity.base = 0;
      u_requested_right_velocity.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_requested_right_velocity.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->requested_right_velocity = u_requested_right_velocity.real;
      offset += sizeof(this->requested_right_velocity);
      union {
        int16_t real;
        uint16_t base;
      } u_requested_left_velocity;
      u_requested_left_velocity.base = 0;
      u_requested_left_velocity.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_requested_left_velocity.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->requested_left_velocity = u_requested_left_velocity.real;
      offset += sizeof(this->requested_left_velocity);
     return offset;
    }

    const char * getType(){ return "create_node/RawTurtlebotSensorState"; };
    const char * getMD5(){ return "103d192c45e953c8bb1c3c046e89e2ff"; };

  };

}
#endif