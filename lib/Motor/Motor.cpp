#include <Arduino.h>
#include <Motor.h>

Motor::Motor(byte output_pin, byte current_pin, byte voltage_pin)
    : pid_obj(&measured_power, &out_power, &set_point, kp, ki, kd, DIRECT),
      current_sense(motor_current, RESISTANCE),
      voltage_sense(motor_voltage) {
  // All values are set to zero now. What they should actually be should be
  // determined after discussion
  motor_output = output_pin;
  motor_current = current_pin;
  motor_voltage = voltage_pin;
  current = 0;
  voltage = 0;  // Same as above
  measured_power = 0.0;
  set_point = 0.0;
  out_power = 0.0;
  kp = 0.0;
  ki = 0.0;
  kd = 0.0;
}

void Motor::update_power() {
  current = current_sense.get_current();
  voltage = voltage_sense.get_voltage();
  measured_power = current * voltage;
  // Ideally, we'd like to call this here. But this is an ISR.
  // pid_obj.Compute();
}

void Motor::set_power(float pedal_power) {
  set_point = pedal_power;
  pid_obj.Compute();
}

double Motor::get_power() {
  return measured_power;
}
