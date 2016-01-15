#ifndef _ROS_pandora_motor_hardware_interface_KinodynamicCommand_h
#define _ROS_pandora_motor_hardware_interface_KinodynamicCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Twist.h"

namespace pandora_motor_hardware_interface
{

  class KinodynamicCommand : public ros::Msg
  {
    public:
      geometry_msgs::Twist cmd_vel;
      float terrain_param;
      float scale_left;
      float scale_right;

    KinodynamicCommand():
      cmd_vel(),
      terrain_param(0),
      scale_left(0),
      scale_right(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->cmd_vel.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->terrain_param);
      offset += serializeAvrFloat64(outbuffer + offset, this->scale_left);
      offset += serializeAvrFloat64(outbuffer + offset, this->scale_right);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->cmd_vel.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->terrain_param));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->scale_left));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->scale_right));
     return offset;
    }

    const char * getType(){ return "pandora_motor_hardware_interface/KinodynamicCommand"; };
    const char * getMD5(){ return "6e27c4041ca5f7373208ae5f8fbd044b"; };

  };

}
#endif