#ifndef _ROS_pandora_sensor_msgs_ImuRPY_h
#define _ROS_pandora_sensor_msgs_ImuRPY_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace pandora_sensor_msgs
{

  class ImuRPY : public ros::Msg
  {
    public:
      std_msgs::Header header;
      float roll;
      float pitch;
      float yaw;

    ImuRPY():
      header(),
      roll(0),
      pitch(0),
      yaw(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->roll);
      offset += serializeAvrFloat64(outbuffer + offset, this->pitch);
      offset += serializeAvrFloat64(outbuffer + offset, this->yaw);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->roll));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->pitch));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->yaw));
     return offset;
    }

    const char * getType(){ return "pandora_sensor_msgs/ImuRPY"; };
    const char * getMD5(){ return "8061e110314ddf08ca1dfbc48d314df8"; };

  };

}
#endif