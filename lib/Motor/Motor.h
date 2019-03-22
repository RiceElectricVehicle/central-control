#include <Arduino.h>
#include <PID_v1.h>


#ifndef MOTOR_H
#define MOTOR_H
#define BAT_V 48
class Motor
{
 private:
  double current;
  double voltage;
  byte motor_output;   // Stores output pin
  byte motor_current_pin;  // Stores current pin
  int motor_pwm;

 public:
  Motor(byte output_pin, byte current_pin);
  void set_pwm(int dc);
  void set_zero();
  double get_current(char channel);
  double get_voltage();
  double get_duty_cycle();
  void start();
};

#endif
