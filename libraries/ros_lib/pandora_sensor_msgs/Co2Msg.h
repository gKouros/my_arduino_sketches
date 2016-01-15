#ifndef _ROS_pandora_sensor_msgs_Co2Msg_h
#define _ROS_pandora_sensor_msgs_Co2Msg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace pandora_sensor_msgs
{

  class Co2Msg : public ros::Msg
  {
    public:
      std_msgs::Header header;
      float co2_percentage;

    Co2Msg():
      header(),
      co2_percentage(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_co2_percentage;
      u_co2_percentage.real = this->co2_percentage;
      *(outbuffer + offset + 0) = (u_co2_percentage.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_co2_percentage.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_co2_percentage.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_co2_percentage.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->co2_percentage);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_co2_percentage;
      u_co2_percentage.base = 0;
      u_co2_percentage.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_co2_percentage.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_co2_percentage.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_co2_percentage.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->co2_percentage = u_co2_percentage.real;
      offset += sizeof(this->co2_percentage);
     return offset;
    }

    const char * getType(){ return "pandora_sensor_msgs/Co2Msg"; };
    const char * getMD5(){ return "4451069c9b94f2f645e2698bb864149b"; };

  };

}
#endif