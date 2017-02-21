#ifndef _ROS_kobuki_msgs_SensorState_h
#define _ROS_kobuki_msgs_SensorState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace kobuki_msgs
{

  class SensorState : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint16_t time_stamp;
      uint8_t bumper;
      uint8_t wheel_drop;
      uint8_t cliff;
      uint16_t left_encoder;
      uint16_t right_encoder;
      int8_t left_pwm;
      int8_t right_pwm;
      uint8_t buttons;
      uint8_t charger;
      uint8_t battery;
      uint8_t bottom_length;
      uint16_t st_bottom;
      uint16_t * bottom;
      uint8_t current_length;
      uint8_t st_current;
      uint8_t * current;
      uint8_t over_current;
      uint16_t digital_input;
      uint8_t analog_input_length;
      uint16_t st_analog_input;
      uint16_t * analog_input;
      enum { BUMPER_RIGHT =  1 };
      enum { BUMPER_CENTRE =  2 };
      enum { BUMPER_LEFT =  4 };
      enum { WHEEL_DROP_RIGHT =  1 };
      enum { WHEEL_DROP_LEFT =  2 };
      enum { CLIFF_RIGHT =  1 };
      enum { CLIFF_CENTRE =  2 };
      enum { CLIFF_LEFT =  4 };
      enum { BUTTON0 =  1 };
      enum { BUTTON1 =  2 };
      enum { BUTTON2 =  4 };
      enum { DISCHARGING =  0 };
      enum { DOCKING_CHARGED =  2 };
      enum { DOCKING_CHARGING =  6 };
      enum { ADAPTER_CHARGED =  18 };
      enum { ADAPTER_CHARGING =  22 };
      enum { OVER_CURRENT_LEFT_WHEEL =  1 };
      enum { OVER_CURRENT_RIGHT_WHEEL =  2 };
      enum { OVER_CURRENT_BOTH_WHEELS =  3 };
      enum { DIGITAL_INPUT0 =  1 };
      enum { DIGITAL_INPUT1 =  2 };
      enum { DIGITAL_INPUT2 =  4 };
      enum { DIGITAL_INPUT3 =  8 };
      enum { DB25_TEST_BOARD_CONNECTED =  64 };

    SensorState():
      header(),
      time_stamp(0),
      bumper(0),
      wheel_drop(0),
      cliff(0),
      left_encoder(0),
      right_encoder(0),
      left_pwm(0),
      right_pwm(0),
      buttons(0),
      charger(0),
      battery(0),
      bottom_length(0), bottom(NULL),
      current_length(0), current(NULL),
      over_current(0),
      digital_input(0),
      analog_input_length(0), analog_input(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->time_stamp >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->time_stamp >> (8 * 1)) & 0xFF;
      offset += sizeof(this->time_stamp);
      *(outbuffer + offset + 0) = (this->bumper >> (8 * 0)) & 0xFF;
      offset += sizeof(this->bumper);
      *(outbuffer + offset + 0) = (this->wheel_drop >> (8 * 0)) & 0xFF;
      offset += sizeof(this->wheel_drop);
      *(outbuffer + offset + 0) = (this->cliff >> (8 * 0)) & 0xFF;
      offset += sizeof(this->cliff);
      *(outbuffer + offset + 0) = (this->left_encoder >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->left_encoder >> (8 * 1)) & 0xFF;
      offset += sizeof(this->left_encoder);
      *(outbuffer + offset + 0) = (this->right_encoder >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->right_encoder >> (8 * 1)) & 0xFF;
      offset += sizeof(this->right_encoder);
      union {
        int8_t real;
        uint8_t base;
      } u_left_pwm;
      u_left_pwm.real = this->left_pwm;
      *(outbuffer + offset + 0) = (u_left_pwm.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->left_pwm);
      union {
        int8_t real;
        uint8_t base;
      } u_right_pwm;
      u_right_pwm.real = this->right_pwm;
      *(outbuffer + offset + 0) = (u_right_pwm.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->right_pwm);
      *(outbuffer + offset + 0) = (this->buttons >> (8 * 0)) & 0xFF;
      offset += sizeof(this->buttons);
      *(outbuffer + offset + 0) = (this->charger >> (8 * 0)) & 0xFF;
      offset += sizeof(this->charger);
      *(outbuffer + offset + 0) = (this->battery >> (8 * 0)) & 0xFF;
      offset += sizeof(this->battery);
      *(outbuffer + offset++) = bottom_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < bottom_length; i++){
      *(outbuffer + offset + 0) = (this->bottom[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->bottom[i] >> (8 * 1)) & 0xFF;
      offset += sizeof(this->bottom[i]);
      }
      *(outbuffer + offset++) = current_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < current_length; i++){
      *(outbuffer + offset + 0) = (this->current[i] >> (8 * 0)) & 0xFF;
      offset += sizeof(this->current[i]);
      }
      *(outbuffer + offset + 0) = (this->over_current >> (8 * 0)) & 0xFF;
      offset += sizeof(this->over_current);
      *(outbuffer + offset + 0) = (this->digital_input >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->digital_input >> (8 * 1)) & 0xFF;
      offset += sizeof(this->digital_input);
      *(outbuffer + offset++) = analog_input_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < analog_input_length; i++){
      *(outbuffer + offset + 0) = (this->analog_input[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->analog_input[i] >> (8 * 1)) & 0xFF;
      offset += sizeof(this->analog_input[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->time_stamp =  ((uint16_t) (*(inbuffer + offset)));
      this->time_stamp |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->time_stamp);
      this->bumper =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->bumper);
      this->wheel_drop =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->wheel_drop);
      this->cliff =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->cliff);
      this->left_encoder =  ((uint16_t) (*(inbuffer + offset)));
      this->left_encoder |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->left_encoder);
      this->right_encoder =  ((uint16_t) (*(inbuffer + offset)));
      this->right_encoder |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->right_encoder);
      union {
        int8_t real;
        uint8_t base;
      } u_left_pwm;
      u_left_pwm.base = 0;
      u_left_pwm.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->left_pwm = u_left_pwm.real;
      offset += sizeof(this->left_pwm);
      union {
        int8_t real;
        uint8_t base;
      } u_right_pwm;
      u_right_pwm.base = 0;
      u_right_pwm.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->right_pwm = u_right_pwm.real;
      offset += sizeof(this->right_pwm);
      this->buttons =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->buttons);
      this->charger =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->charger);
      this->battery =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->battery);
      uint8_t bottom_lengthT = *(inbuffer + offset++);
      if(bottom_lengthT > bottom_length)
        this->bottom = (uint16_t*)realloc(this->bottom, bottom_lengthT * sizeof(uint16_t));
      offset += 3;
      bottom_length = bottom_lengthT;
      for( uint8_t i = 0; i < bottom_length; i++){
      this->st_bottom =  ((uint16_t) (*(inbuffer + offset)));
      this->st_bottom |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->st_bottom);
        memcpy( &(this->bottom[i]), &(this->st_bottom), sizeof(uint16_t));
      }
      uint8_t current_lengthT = *(inbuffer + offset++);
      if(current_lengthT > current_length)
        this->current = (uint8_t*)realloc(this->current, current_lengthT * sizeof(uint8_t));
      offset += 3;
      current_length = current_lengthT;
      for( uint8_t i = 0; i < current_length; i++){
      this->st_current =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->st_current);
        memcpy( &(this->current[i]), &(this->st_current), sizeof(uint8_t));
      }
      this->over_current =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->over_current);
      this->digital_input =  ((uint16_t) (*(inbuffer + offset)));
      this->digital_input |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->digital_input);
      uint8_t analog_input_lengthT = *(inbuffer + offset++);
      if(analog_input_lengthT > analog_input_length)
        this->analog_input = (uint16_t*)realloc(this->analog_input, analog_input_lengthT * sizeof(uint16_t));
      offset += 3;
      analog_input_length = analog_input_lengthT;
      for( uint8_t i = 0; i < analog_input_length; i++){
      this->st_analog_input =  ((uint16_t) (*(inbuffer + offset)));
      this->st_analog_input |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->st_analog_input);
        memcpy( &(this->analog_input[i]), &(this->st_analog_input), sizeof(uint16_t));
      }
     return offset;
    }

    const char * getType(){ return "kobuki_msgs/SensorState"; };
    const char * getMD5(){ return "430a4bfd78449c8740bfef32b26613a6"; };

  };

}
#endif