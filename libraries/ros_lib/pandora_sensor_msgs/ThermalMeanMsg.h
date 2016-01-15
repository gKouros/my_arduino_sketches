#ifndef _ROS_pandora_sensor_msgs_ThermalMeanMsg_h
#define _ROS_pandora_sensor_msgs_ThermalMeanMsg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace pandora_sensor_msgs
{

  class ThermalMeanMsg : public ros::Msg
  {
    public:
      std_msgs::Header header;
      float thermal_mean;

    ThermalMeanMsg():
      header(),
      thermal_mean(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_thermal_mean;
      u_thermal_mean.real = this->thermal_mean;
      *(outbuffer + offset + 0) = (u_thermal_mean.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_thermal_mean.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_thermal_mean.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_thermal_mean.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->thermal_mean);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_thermal_mean;
      u_thermal_mean.base = 0;
      u_thermal_mean.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_thermal_mean.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_thermal_mean.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_thermal_mean.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->thermal_mean = u_thermal_mean.real;
      offset += sizeof(this->thermal_mean);
     return offset;
    }

    const char * getType(){ return "pandora_sensor_msgs/ThermalMeanMsg"; };
    const char * getMD5(){ return "dfeba3224d22734c3c55488160036365"; };

  };

}
#endif