#include <Arduino.h>
#include <CurrentSense.h>
#include <PID_v1.h>

#ifndef MOTOR_H
#define MOTOR_H

class Motor {
 private:
  double current;
  double voltage;
  double measured_power;
  double set_point;
  double out_power;
  double kp;
  double ki;
  double kd;
  byte motor_output;   // Stores output pin
  byte motor_current;  // Stores current pin
  PID pid_obj;
  CurrentSense current_sense;

 public:
  Motor(byte output_pin, byte current_pin);
  void update_power();                // Change mesuredPower
  void set_power(float pedal_power);  // Change setpoint
  double get_power();                 // Get current power setting
};

#endif
