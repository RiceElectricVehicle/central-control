#include <Arduino.h>
#include <Motor.h>

Motor::Motor(byte output_pin, byte current_pin) {
  // All values are set to zero now. What they should actually be should be
  // determined after discussion
  motor_output = output_pin;
  motor_current_pin = current_pin;
  motor_pwm = 0;
}

double Motor::get_current(char channel) {
  int adc = analogRead(motor_current_pin);
  if (channel == 'A')
    return 0.08035 * adc - 8.29045;
  else if (channel == 'B')
    return 0.0809733 * adc - 9.048853;
  else
    return -1;
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
