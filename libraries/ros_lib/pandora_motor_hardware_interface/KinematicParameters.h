#ifndef _ROS_pandora_motor_hardware_interface_KinematicParameters_h
#define _ROS_pandora_motor_hardware_interface_KinematicParameters_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace pandora_motor_hardware_interface
{

  class KinematicParameters : public ros::Msg
  {
    public:
      float terrain_param;
      float scale_left;
      float scale_right;

    KinematicParameters():
      terrain_param(0),
      scale_left(0),
      scale_right(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->terrain_param);
      offset += serializeAvrFloat64(outbuffer + offset, this->scale_left);
      offset += serializeAvrFloat64(outbuffer + offset, this->scale_right);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->terrain_param));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->scale_left));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->scale_right));
     return offset;
    }

    const char * getType(){ return "pandora_motor_hardware_interface/KinematicParameters"; };
    const char * getMD5(){ return "6e0a9f30f64d7a69916382e95f234cf5"; };

  };

}
#endif