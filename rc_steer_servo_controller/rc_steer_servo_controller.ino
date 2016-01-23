/******************************************************************************
Copyright (c) 2016, George Kouros
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of my_arduino_sketches nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

#include "rc_steer_servo_controller.h"

/* Callback Functions */
void frontSteerServoCommandCallback(const std_msgs::Float64& command)
{
  // write servo command
  double cmd = (command.data > 0) ?
    floor(command.data * 180 / PI) : ceil(command.data * 180 / PI);
  uint16_t angle = clampAngle(cmd) + ANGLE_OFFSET;
  frontSteerServo.write(angle);

  // publish feedback
  frontSteerServoAngleMsg.data =
    (static_cast<double>(angle) - ANGLE_OFFSET) / 180 * PI;
  frontSteerServoFeedbackPublisher.publish(&frontSteerServoAngleMsg);
}

void rearSteerServoCommandCallback(const std_msgs::Float64& command)
{
  // write servo command
  double cmd = (command.data > 0) ?
    floor(command.data * 180 / PI) : ceil(command.data * 180 / PI);
  uint16_t angle = clampAngle(cmd) + ANGLE_OFFSET;
  rearSteerServo.write(angle);

  // publish feedback
  rearSteerServoAngleMsg.data =
    (static_cast<double>(angle) - ANGLE_OFFSET) / 180 * PI;
  rearSteerServoFeedbackPublisher.publish(&rearSteerServoAngleMsg);
}


/* Functions */
void publishBatteryVoltage()
{
  // read battery voltage
  batteryVoltageMsg.data = 
    static_cast<double>(analogRead(BATTERY_PIN)) / 1024 * 5 * 10;

  // publish battery voltage
  batteryVoltagePublisher.publish(&batteryVoltageMsg);
}

double clampAngle(double angle)
{
  if (angle > MAX_ANGLE)
    return MAX_ANGLE;
  else if (angle < MIN_ANGLE)
    return MIN_ANGLE;
  else
    return angle;
}


/* Setup */
void setup()
{
  // initialize ros node
  nh.initNode();

  // initialize ros subscribers and publishers
  nh.subscribe(frontSteerServoCommandSubscriber);
  nh.subscribe(rearSteerServoCommandSubscriber);
  nh.advertise(frontSteerServoFeedbackPublisher);
  nh.advertise(rearSteerServoFeedbackPublisher);
  nh.advertise(batteryVoltagePublisher);

  // attach pins to servo objects
  frontSteerServo.attach(FRONT_STEER_SERVO_PIN);
  rearSteerServo.attach(REAR_STEER_SERVO_PIN);

  // set servos to home position
  frontSteerServo.write(0 + ANGLE_OFFSET);
  rearSteerServo.write(0 + ANGLE_OFFSET);
}


/* Main Loop */
void loop()
{
  nh.spinOnce();
  publishBatteryVoltage();
}
