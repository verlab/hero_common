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
      typedef geometry_msgs::Pose2D _initialPose_type;
      _initialPose_type initialPose;
      typedef stdr_msgs::FootprintMsg _footprint_type;
      _footprint_type footprint;
      uint32_t laserSensors_length;
      typedef stdr_msgs::LaserSensorMsg _laserSensors_type;
      _laserSensors_type st_laserSensors;
      _laserSensors_type * laserSensors;
      uint32_t sonarSensors_length;
      typedef stdr_msgs::SonarSensorMsg _sonarSensors_type;
      _sonarSensors_type st_sonarSensors;
      _sonarSensors_type * sonarSensors;
      uint32_t rfidSensors_length;
      typedef stdr_msgs::RfidSensorMsg _rfidSensors_type;
      _rfidSensors_type st_rfidSensors;
      _rfidSensors_type * rfidSensors;
      uint32_t co2Sensors_length;
      typedef stdr_msgs::CO2SensorMsg _co2Sensors_type;
      _co2Sensors_type st_co2Sensors;
      _co2Sensors_type * co2Sensors;
      uint32_t soundSensors_length;
      typedef stdr_msgs::SoundSensorMsg _soundSensors_type;
      _soundSensors_type st_soundSensors;
      _soundSensors_type * soundSensors;
      uint32_t thermalSensors_length;
      typedef stdr_msgs::ThermalSensorMsg _thermalSensors_type;
      _thermalSensors_type st_thermalSensors;
      _thermalSensors_type * thermalSensors;
      typedef stdr_msgs::KinematicMsg _kinematicModel_type;
      _kinematicModel_type kinematicModel;

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
      *(outbuffer + offset + 0) = (this->laserSensors_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->laserSensors_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->laserSensors_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->laserSensors_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->laserSensors_length);
      for( uint32_t i = 0; i < laserSensors_length; i++){
      offset += this->laserSensors[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->sonarSensors_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->sonarSensors_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->sonarSensors_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->sonarSensors_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->sonarSensors_length);
      for( uint32_t i = 0; i < sonarSensors_length; i++){
      offset += this->sonarSensors[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->rfidSensors_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->rfidSensors_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->rfidSensors_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->rfidSensors_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rfidSensors_length);
      for( uint32_t i = 0; i < rfidSensors_length; i++){
      offset += this->rfidSensors[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->co2Sensors_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->co2Sensors_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->co2Sensors_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->co2Sensors_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->co2Sensors_length);
      for( uint32_t i = 0; i < co2Sensors_length; i++){
      offset += this->co2Sensors[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->soundSensors_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->soundSensors_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->soundSensors_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->soundSensors_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->soundSensors_length);
      for( uint32_t i = 0; i < soundSensors_length; i++){
      offset += this->soundSensors[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->thermalSensors_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->thermalSensors_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->thermalSensors_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->thermalSensors_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->thermalSensors_length);
      for( uint32_t i = 0; i < thermalSensors_length; i++){
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
      uint32_t laserSensors_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      laserSensors_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      laserSensors_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      laserSensors_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->laserSensors_length);
      if(laserSensors_lengthT > laserSensors_length)
        this->laserSensors = (stdr_msgs::LaserSensorMsg*)realloc(this->laserSensors, laserSensors_lengthT * sizeof(stdr_msgs::LaserSensorMsg));
      laserSensors_length = laserSensors_lengthT;
      for( uint32_t i = 0; i < laserSensors_length; i++){
      offset += this->st_laserSensors.deserialize(inbuffer + offset);
        memcpy( &(this->laserSensors[i]), &(this->st_laserSensors), sizeof(stdr_msgs::LaserSensorMsg));
      }
      uint32_t sonarSensors_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      sonarSensors_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      sonarSensors_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      sonarSensors_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->sonarSensors_length);
      if(sonarSensors_lengthT > sonarSensors_length)
        this->sonarSensors = (stdr_msgs::SonarSensorMsg*)realloc(this->sonarSensors, sonarSensors_lengthT * sizeof(stdr_msgs::SonarSensorMsg));
      sonarSensors_length = sonarSensors_lengthT;
      for( uint32_t i = 0; i < sonarSensors_length; i++){
      offset += this->st_sonarSensors.deserialize(inbuffer + offset);
        memcpy( &(this->sonarSensors[i]), &(this->st_sonarSensors), sizeof(stdr_msgs::SonarSensorMsg));
      }
      uint32_t rfidSensors_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      rfidSensors_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      rfidSensors_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      rfidSensors_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->rfidSensors_length);
      if(rfidSensors_lengthT > rfidSensors_length)
        this->rfidSensors = (stdr_msgs::RfidSensorMsg*)realloc(this->rfidSensors, rfidSensors_lengthT * sizeof(stdr_msgs::RfidSensorMsg));
      rfidSensors_length = rfidSensors_lengthT;
      for( uint32_t i = 0; i < rfidSensors_length; i++){
      offset += this->st_rfidSensors.deserialize(inbuffer + offset);
        memcpy( &(this->rfidSensors[i]), &(this->st_rfidSensors), sizeof(stdr_msgs::RfidSensorMsg));
      }
      uint32_t co2Sensors_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      co2Sensors_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      co2Sensors_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      co2Sensors_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->co2Sensors_length);
      if(co2Sensors_lengthT > co2Sensors_length)
        this->co2Sensors = (stdr_msgs::CO2SensorMsg*)realloc(this->co2Sensors, co2Sensors_lengthT * sizeof(stdr_msgs::CO2SensorMsg));
      co2Sensors_length = co2Sensors_lengthT;
      for( uint32_t i = 0; i < co2Sensors_length; i++){
      offset += this->st_co2Sensors.deserialize(inbuffer + offset);
        memcpy( &(this->co2Sensors[i]), &(this->st_co2Sensors), sizeof(stdr_msgs::CO2SensorMsg));
      }
      uint32_t soundSensors_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      soundSensors_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      soundSensors_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      soundSensors_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->soundSensors_length);
      if(soundSensors_lengthT > soundSensors_length)
        this->soundSensors = (stdr_msgs::SoundSensorMsg*)realloc(this->soundSensors, soundSensors_lengthT * sizeof(stdr_msgs::SoundSensorMsg));
      soundSensors_length = soundSensors_lengthT;
      for( uint32_t i = 0; i < soundSensors_length; i++){
      offset += this->st_soundSensors.deserialize(inbuffer + offset);
        memcpy( &(this->soundSensors[i]), &(this->st_soundSensors), sizeof(stdr_msgs::SoundSensorMsg));
      }
      uint32_t thermalSensors_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      thermalSensors_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      thermalSensors_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      thermalSensors_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->thermalSensors_length);
      if(thermalSensors_lengthT > thermalSensors_length)
        this->thermalSensors = (stdr_msgs::ThermalSensorMsg*)realloc(this->thermalSensors, thermalSensors_lengthT * sizeof(stdr_msgs::ThermalSensorMsg));
      thermalSensors_length = thermalSensors_lengthT;
      for( uint32_t i = 0; i < thermalSensors_length; i++){
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