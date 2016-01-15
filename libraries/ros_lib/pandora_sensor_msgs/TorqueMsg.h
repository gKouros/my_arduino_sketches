#ifndef _ROS_pandora_sensor_msgs_TorqueMsg_h
#define _ROS_pandora_sensor_msgs_TorqueMsg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace pandora_sensor_msgs
{

  class TorqueMsg : public ros::Msg
  {
    public:
      std_msgs::Header header;
      float left_rear_wheel_torque;
      float left_front_wheel_torque;
      float right_rear_wheel_torque;
      float right_front_wheel_torque;

    TorqueMsg():
      header(),
      left_rear_wheel_torque(0),
      left_front_wheel_torque(0),
      right_rear_wheel_torque(0),
      right_front_wheel_torque(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->left_rear_wheel_torque);
      offset += serializeAvrFloat64(outbuffer + offset, this->left_front_wheel_torque);
      offset += serializeAvrFloat64(outbuffer + offset, this->right_rear_wheel_torque);
      offset += serializeAvrFloat64(outbuffer + offset, this->right_front_wheel_torque);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->left_rear_wheel_torque));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->left_front_wheel_torque));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->right_rear_wheel_torque));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->right_front_wheel_torque));
     return offset;
    }

    const char * getType(){ return "pandora_sensor_msgs/TorqueMsg"; };
    const char * getMD5(){ return "a0cb1ec3d320bd297781195922c40faa"; };

  };

}
#endif