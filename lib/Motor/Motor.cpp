#include <Arduino.h>
#include <Motor.h>

Motor::Motor(byte output_pin, byte current_pin) {
  // All values are set to zero now. What they should actually be should be
  // determined after discussion
  motor_output = output_pin;
  motor_current_pin = current_pin;
  motor_pwm = 0;
}

double Motor::get_current() {
  double val = 3.3 * analogRead(motor_current_pin) / 1023.0;
  // Remove op amp gain
  val = val / 11;
  // Account for averaging effect of low pass filter.
  val = 2 * val;
  // I = V / R, R = .004 -> 1/R = 250
  return 250 * val;
}

void Motor::set_pwm(int dc) {
  motor_pwm = dc;
  analogWrite(motor_output, dc);
}

void Motor::set_zero() {
  analogWrite(motor_output, 4095);
}

double Motor::get_duty_cycle() {
  return motor_pwm / 4095;
}

double Motor::get_voltage() {
  return BAT_V * Motor::get_duty_cycle();
}
