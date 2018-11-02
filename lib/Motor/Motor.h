#include <CurrentSense.h>
#include <PID_v1.h>
#include <pins.h>
#ifndef MOTOR_H
#define MOTOR_H
#define RESISTANCE .047
class Motor {
 private:
  CurrentSense currentsense()
  float current;
  float voltage;
  float measuredPower;
  float setPoint;
  float outpower;
  float kp;
  float ki;
  float kd;

 public:
  Motor();
  PID pidObj();  //I moved it to public so we can access pidObj.Compute() from outside
  void update_power(); // Change mesuredPower
  void setPower(float pedal_power);  // Change setpoint
  float get_power(); // Get current power setting
};

#endif
