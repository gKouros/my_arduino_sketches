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

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <ros.h>
#include <Servo.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>


/* Pin Definitions */
#define MOTOR_BATTERY_PIN 0
#define PC_BATTERY_PIN 1

#define FRONT_STEER_SERVO_PIN 5
#define REAR_STEER_SERVO_PIN 6


/* constants definitions */
#define MAX_ANGLE 45  // [degrees]
#define MIN_ANGLE -45  // [degrees]
#define ANGLE_OFFSET 90  // [degrees]


/* Global Variables */
ros::NodeHandle nh;
std_msgs::Float64 frontSteerServoAngleMsg, rearSteerServoAngleMsg;
std_msgs::String batteryVoltagesMsg;
Servo frontSteerServo, rearSteerServo;


/* Subscriber and Publisher declarations*/
ros::Subscriber<std_msgs::Float64>  frontSteerServoCommandSubscriber(
  "/front_steer_controller/command", frontSteerServoCommandCallback);
ros::Subscriber<std_msgs::Float64> rearSteerServoCommandSubscriber(
    "/rear_steer_controller/command", rearSteerServoCommandCallback);
ros::Publisher frontSteerServoFeedbackPublisher(
  "/front_steer_controller/state", &frontSteerServoAngleMsg);
ros::Publisher rearSteerServoFeedbackPublisher(
  "/rear_steer_controller/state", &rearSteerServoAngleMsg);
ros::Publisher batteryVoltagesPublisher(
  "/batteries/voltage", &batteryVoltagesMsg);


/* Functions */
void frontSteerServoCommandCallback(const std_msgs::Float64& command);
void rearSteerServoCommandCallback(const std_msgs::Float64& command);
void publishBatteryVoltages();
double clampAngle(double angle);
void setup();
void loop();
