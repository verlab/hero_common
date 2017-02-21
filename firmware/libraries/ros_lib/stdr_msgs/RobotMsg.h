#ifndef _ROS_stdr_msgs_RobotMsg_h
#define _ROS_stdr_msgs_RobotMsg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose2D.h"
#include "stdr_msgs/FootprintMsg.h"
#include "stdr_msgs/LaserSensorMsg.h"
#include "stdr_msgs/SonarSensorMsg.h"
#include "stdr_msgs/RfidSensorMsg.h"
#include "stdr_msgs/CO2SensorMsg.h"
#include "stdr_msgs/SoundSensorMsg.h"
#include "stdr_msgs/ThermalSensorMsg.h"
#include "stdr_msgs/KinematicMsg.h"

namespace stdr_msgs
{

  class RobotMsg : public ros::Msg
  {
    public:
      geometry_msgs::Pose2D initialPose;
      stdr_msgs::FootprintMsg footprint;
      uint8_t laserSensors_length;
      stdr_msgs::LaserSensorMsg st_laserSensors;
      stdr_msgs::LaserSensorMsg * laserSensors;
      uint8_t sonarSensors_length;
      stdr_msgs::SonarSensorMsg st_sonarSensors;
      stdr_msgs::SonarSensorMsg * sonarSensors;
      uint8_t rfidSensors_length;
      stdr_msgs::RfidSensorMsg st_rfidSensors;
      stdr_msgs::RfidSensorMsg * rfidSensors;
      uint8_t co2Sensors_length;
      stdr_msgs::CO2SensorMsg st_co2Sensors;
      stdr_msgs::CO2SensorMsg * co2Sensors;
      uint8_t soundSensors_length;
      stdr_msgs::SoundSensorMsg st_soundSensors;
      stdr_msgs::SoundSensorMsg * soundSensors;
      uint8_t thermalSensors_length;
      stdr_msgs::ThermalSensorMsg st_thermalSensors;
      stdr_msgs::ThermalSensorMsg * thermalSensors;
      stdr_msgs::KinematicMsg kinematicModel;

    RobotMsg():
      initialPose(),
      footprint(),
      laserSensors_length(0), laserSensors(NULL),
      sonarSensors_length(0), sonarSensors(NULL),
      rfidSensors_length(0), rfidSensors(NULL),
      co2Sensors_length(0), co2Sensors(NULL),
      soundSensors_length(0), soundSensors(NULL),
      thermalSensors_length(0), thermalSensors(NULL),
      kinematicModel()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->initialPose.serialize(outbuffer + offset);
      offset += this->footprint.serialize(outbuffer + offset);
      *(outbuffer + offset++) = laserSensors_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < laserSensors_length; i++){
      offset += this->laserSensors[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = sonarSensors_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < sonarSensors_length; i++){
      offset += this->sonarSensors[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = rfidSensors_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < rfidSensors_length; i++){
      offset += this->rfidSensors[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = co2Sensors_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < co2Sensors_length; i++){
      offset += this->co2Sensors[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = soundSensors_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < soundSensors_length; i++){
      offset += this->soundSensors[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = thermalSensors_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < thermalSensors_length; i++){
      offset += this->thermalSensors[i].serialize(outbuffer + offset);
      }
      offset += this->kinematicModel.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->initialPose.deserialize(inbuffer + offset);
      offset += this->footprint.deserialize(inbuffer + offset);
      uint8_t laserSensors_lengthT = *(inbuffer + offset++);
      if(laserSensors_lengthT > laserSensors_length)
        this->laserSensors = (stdr_msgs::LaserSensorMsg*)realloc(this->laserSensors, laserSensors_lengthT * sizeof(stdr_msgs::LaserSensorMsg));
      offset += 3;
      laserSensors_length = laserSensors_lengthT;
      for( uint8_t i = 0; i < laserSensors_length; i++){
      offset += this->st_laserSensors.deserialize(inbuffer + offset);
        memcpy( &(this->laserSensors[i]), &(this->st_laserSensors), sizeof(stdr_msgs::LaserSensorMsg));
      }
      uint8_t sonarSensors_lengthT = *(inbuffer + offset++);
      if(sonarSensors_lengthT > sonarSensors_length)
        this->sonarSensors = (stdr_msgs::SonarSensorMsg*)realloc(this->sonarSensors, sonarSensors_lengthT * sizeof(stdr_msgs::SonarSensorMsg));
      offset += 3;
      sonarSensors_length = sonarSensors_lengthT;
      for( uint8_t i = 0; i < sonarSensors_length; i++){
      offset += this->st_sonarSensors.deserialize(inbuffer + offset);
        memcpy( &(this->sonarSensors[i]), &(this->st_sonarSensors), sizeof(stdr_msgs::SonarSensorMsg));
      }
      uint8_t rfidSensors_lengthT = *(inbuffer + offset++);
      if(rfidSensors_lengthT > rfidSensors_length)
        this->rfidSensors = (stdr_msgs::RfidSensorMsg*)realloc(this->rfidSensors, rfidSensors_lengthT * sizeof(stdr_msgs::RfidSensorMsg));
      offset += 3;
      rfidSensors_length = rfidSensors_lengthT;
      for( uint8_t i = 0; i < rfidSensors_length; i++){
      offset += this->st_rfidSensors.deserialize(inbuffer + offset);
        memcpy( &(this->rfidSensors[i]), &(this->st_rfidSensors), sizeof(stdr_msgs::RfidSensorMsg));
      }
      uint8_t co2Sensors_lengthT = *(inbuffer + offset++);
      if(co2Sensors_lengthT > co2Sensors_length)
        this->co2Sensors = (stdr_msgs::CO2SensorMsg*)realloc(this->co2Sensors, co2Sensors_lengthT * sizeof(stdr_msgs::CO2SensorMsg));
      offset += 3;
      co2Sensors_length = co2Sensors_lengthT;
      for( uint8_t i = 0; i < co2Sensors_length; i++){
      offset += this->st_co2Sensors.deserialize(inbuffer + offset);
        memcpy( &(this->co2Sensors[i]), &(this->st_co2Sensors), sizeof(stdr_msgs::CO2SensorMsg));
      }
      uint8_t soundSensors_lengthT = *(inbuffer + offset++);
      if(soundSensors_lengthT > soundSensors_length)
        this->soundSensors = (stdr_msgs::SoundSensorMsg*)realloc(this->soundSensors, soundSensors_lengthT * sizeof(stdr_msgs::SoundSensorMsg));
      offset += 3;
      soundSensors_length = soundSensors_lengthT;
      for( uint8_t i = 0; i < soundSensors_length; i++){
      offset += this->st_soundSensors.deserialize(inbuffer + offset);
        memcpy( &(this->soundSensors[i]), &(this->st_soundSensors), sizeof(stdr_msgs::SoundSensorMsg));
      }
      uint8_t thermalSensors_lengthT = *(inbuffer + offset++);
      if(thermalSensors_lengthT > thermalSensors_length)
        this->thermalSensors = (stdr_msgs::ThermalSensorMsg*)realloc(this->thermalSensors, thermalSensors_lengthT * sizeof(stdr_msgs::ThermalSensorMsg));
      offset += 3;
      thermalSensors_length = thermalSensors_lengthT;
      for( uint8_t i = 0; i < thermalSensors_length; i++){
      offset += this->st_thermalSensors.deserialize(inbuffer + offset);
        memcpy( &(this->thermalSensors[i]), &(this->st_thermalSensors), sizeof(stdr_msgs::ThermalSensorMsg));
      }
      offset += this->kinematicModel.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "stdr_msgs/RobotMsg"; };
    const char * getMD5(){ return "ffa138f7f6a9c979acfb84d2c8e73a39"; };

  };

}
#endif