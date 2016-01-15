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
#define MAX_ANGLE 23  // [degrees]
#define MIN_ANGLE -23  // [degrees]
#define ANGLE_OFFSET 90  // [degrees]

/* Global Variables */
ros::NodeHandle nh;
std_msgs::Float64 frontSteerServoAngleMsg, rearSteerServoAngleMsg;
std_msgs::String batteryVoltagesMsg;
Servo frontSteerServo, rearSteerServo;

/* Functions */
void frontSteerServoCommandCallback(const std_msgs::Float64& command);
void rearSteerServoCommandCallback(const std_msgs::Float64& command);
void publishBatteryVoltages();
double clampAngle(double angle);
void setup();
void loop();
