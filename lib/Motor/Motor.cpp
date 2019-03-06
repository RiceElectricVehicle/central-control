#include <Arduino.h>
#include <Motor.h>

Motor::Motor(byte output_pin, byte current_pin)
    : pid_obj(&pid_input, &pid_output, &set_point, kp, ki, kd, REVERSE) {
  // All values are set to zero now. What they should actually be should be
  // determined after discussion
  motor_output = output_pin;
  motor_current_pin = current_pin;
  current = 0;
  pid_input = 0.0;
  set_point = 0.0;
  pid_output = 0.0;
  kp = 1;
  ki = 0.0;
  kd = 0.0;
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

void Motor::update_pid_input() {
  pid_input = get_current() * (BAT_V * get_duty_cycle());
  // Ideally, we'd like to call this here. But this is an ISR.
  // pid_obj.Compute();
}

void Motor::compute_pid(double pedal_power) {
  set_point = pedal_power;
  pid_obj.Compute();
}

double Motor::get_pid_output() {
  return pid_output;
}

void Motor::set_pwm() {
  analogWrite(motor_output, pid_output);
}

void Motor::set_zero() {
  analogWrite(motor_output, 4095);
}

void Motor::start() {
  pid_obj.SetOutputLimits(0, 4095);
  pid_obj.SetMode(AUTOMATIC);
}

double Motor::get_duty_cycle() {
  return pid_output / 4095;
}
