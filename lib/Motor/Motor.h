#include <Arduino.h>
#include <PID_v1.h>


#ifndef MOTOR_H
#define MOTOR_H
#define BAT_V 48
class Motor {
 private:
  double current;
  double voltage;
  double pid_input;
  double set_point;
  double pid_output;
  double kp;
  double ki;
  double kd;
  byte motor_output;   // Stores output pin
  byte motor_current_pin;  // Stores current pin
  PID pid_obj;

 public:
  Motor(byte output_pin, byte current_pin);
  void update_pid_input();                // Change mesuredPower
  void compute_pid(double pedal_power);  // Change setpoint
  double get_pid_output();                 // Get current power setting
  void set_pwm();
  void set_zero();
  double get_current();
  double get_voltage(double current_duty_cycle);
  int get_duty_cycle();
  void start();
};

#endif
