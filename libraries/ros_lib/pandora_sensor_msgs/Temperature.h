#ifndef _ROS_pandora_sensor_msgs_Temperature_h
#define _ROS_pandora_sensor_msgs_Temperature_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace pandora_sensor_msgs
{

  class Temperature : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t name_length;
      char* st_name;
      char* * name;
      uint8_t temperature_length;
      float st_temperature;
      float * temperature;

    Temperature():
      header(),
      name_length(0), name(NULL),
      temperature_length(0), temperature(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = name_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < name_length; i++){
      uint32_t length_namei = strlen(this->name[i]);
      memcpy(outbuffer + offset, &length_namei, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->name[i], length_namei);
      offset += length_namei;
      }
      *(outbuffer + offset++) = temperature_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < temperature_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->temperature[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t name_lengthT = *(inbuffer + offset++);
      if(name_lengthT > name_length)
        this->name = (char**)realloc(this->name, name_lengthT * sizeof(char*));
      offset += 3;
      name_length = name_lengthT;
      for( uint8_t i = 0; i < name_length; i++){
      uint32_t length_st_name;
      memcpy(&length_st_name, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_name-1]=0;
      this->st_name = (char *)(inbuffer + offset-1);
      offset += length_st_name;
        memcpy( &(this->name[i]), &(this->st_name), sizeof(char*));
      }
      uint8_t temperature_lengthT = *(inbuffer + offset++);
      if(temperature_lengthT > temperature_length)
        this->temperature = (float*)realloc(this->temperature, temperature_lengthT * sizeof(float));
      offset += 3;
      temperature_length = temperature_lengthT;
      for( uint8_t i = 0; i < temperature_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_temperature));
        memcpy( &(this->temperature[i]), &(this->st_temperature), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "pandora_sensor_msgs/Temperature"; };
    const char * getMD5(){ return "0aa09ef71eada777ee697d205df8b8f6"; };

  };

}
#endif