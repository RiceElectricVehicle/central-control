#include <CurrentSense.h>
#include <PID_v1.h>
#include <pins.h>
#ifndef MOTOR_H
#define MOTOR_H
#define RESISTANCE .047
class Motor {
 private:
  PID pidObj();
  float current;
  float voltage;
  float measuredPower;
  float setPoint;

 public:
  Motor();
  void setPower();
};

#endif