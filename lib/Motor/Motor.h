#include <Arduino.h>
#include <CurrentSense.h>
#include <PID_v1.h>
#include <pins.h>
#ifndef MOTOR_H
#define MOTOR_H
#define RESISTANCE .047
class Motor {
 private:
  CurrentSense current_sense;
  float current;
  float voltage;
  float measured_power;
  float set_point;
  float out_power;
  float kp;
  float ki;
  float kd;

 public:
  Motor(byte output_pin, byte current_pin, byte voltage_pin);
  PID pid_obj;                        // I moved it to public so we can access pidObj.Compute() from outside
  void update_power();                // Change mesuredPower
  void set_power(float pedal_power);  // Change setpoint
  float get_power();                  // Get current power setting
};

#endif
