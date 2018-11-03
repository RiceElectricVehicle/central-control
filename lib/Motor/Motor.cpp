#include <CurrentSense.h>
#include <Motor.h>
#include <PID_v1.h>
#define RESISTANCE 0.047

Motor::Motor(byte output_pin, byte current_pin, byte voltage_pin)
    : current_sense(current_pin, RESISTANCE)
    : pid_obj(&measured_power, &out_power, &set_point, kp, ki, kd, DIRECT) {
  // All values are set to zero now. What they should actually be should be
  // determined after discussion
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
  current = current_sense.getCurrent();
}

void Motor::set_power(float pedal_power) {
  set_point = pedal_power;
}

float Motor::get_power() {
  return measured_power;
}
