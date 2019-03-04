#include <VoltageSense.h>

VoltageSense::VoltageSense(byte new_pin) {
  voltPin = new_pin;
}

float VoltageSense::get_voltage() {
  float val = 5.0 * analogRead(voltPin) / 1023.0;
  return val;
}
