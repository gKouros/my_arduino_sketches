#include "rc_steer_servo_controller.h"


/* Subscriber and Publisher declarations*/
ros::Subscriber<std_msgs::Float64>
  frontSteerServoCommandSubscriber("/front_steer_controller/command", frontSteerServoCommandCallback);
ros::Subscriber<std_msgs::Float64>
  rearSteerServoCommandSubscriber("/rear_steer_controller/command", rearSteerServoCommandCallback);
ros::Publisher frontSteerServoFeedbackPublisher("/front_steer_controller/state", &frontSteerServoAngleMsg);
ros::Publisher rearSteerServoFeedbackPublisher("/rear_steer_controller/state", &rearSteerServoAngleMsg);
ros::Publisher batteryVoltagesPublisher("/batteries/voltage", &batteryVoltagesMsg);


/* Callback Functions */
void frontSteerServoCommandCallback(const std_msgs::Float64& command)
{
  // write servo command
  double cmd = (command.data > 0) ? floor(command.data * 180 / PI) : ceil(command.data * 180 / PI);
  uint16_t angle = clampAngle(cmd) + ANGLE_OFFSET;
  frontSteerServo.write(angle);
  
  // publish feedback
  frontSteerServoAngleMsg.data = (static_cast<double>(angle) - ANGLE_OFFSET) / 180 * PI;
  frontSteerServoFeedbackPublisher.publish(&frontSteerServoAngleMsg);
}

void rearSteerServoCommandCallback(const std_msgs::Float64& command)
{
  // write servo command
  double cmd = (command.data > 0) ? floor(command.data * 180 / PI) : ceil(command.data * 180 / PI);
  uint16_t angle = clampAngle(cmd) + ANGLE_OFFSET;
  rearSteerServo.write(angle);

  // publish feedback
  rearSteerServoAngleMsg.data = (static_cast<double>(angle) - ANGLE_OFFSET) / 180 * PI;
  rearSteerServoFeedbackPublisher.publish(&rearSteerServoAngleMsg);
}


/* Functions */
void publishBatteryVoltages()
{
  double motor_battery_voltage = static_cast<double>(analogRead(MOTOR_BATTERY_PIN)) / 1024 * 5 * 10;
  double pc_battery_voltage = static_cast<double>(analogRead(PC_BATTERY_PIN)) / 1024 * 5 * 10;

  int m1 = motor_battery_voltage;
  int m2 = fabs(motor_battery_voltage * 100) - abs(m1 * 100);
  
  int p1 = pc_battery_voltage;
  int p2 = fabs(pc_battery_voltage * 100) - abs(p1 * 100);
  
  char temp_char_array[50];
  sprintf(temp_char_array, "MOTORS:%d.%d,PC:%d.%d",m1, m2, p1, p2);// motor_battery_voltage, pc_battery_voltage);
  batteryVoltagesMsg.data = temp_char_array;
  batteryVoltagesPublisher.publish(&batteryVoltagesMsg);
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
  nh.initNode();
  nh.subscribe(frontSteerServoCommandSubscriber);
  nh.subscribe(rearSteerServoCommandSubscriber);
  nh.advertise(frontSteerServoFeedbackPublisher);
  nh.advertise(rearSteerServoFeedbackPublisher);
  nh.advertise(batteryVoltagesPublisher);
  
  frontSteerServo.attach(FRONT_STEER_SERVO_PIN);
  rearSteerServo.attach(REAR_STEER_SERVO_PIN);
}


/* Main Loop */
void loop()
{
  nh.spinOnce();
  publishBatteryVoltages();
}
