#include <Arduino.h>

#ifndef VOLTAGESENSE_H
#define VOLTAGESENSE_H

class VoltageSense {
 public:
  VoltageSense(byte new_pin);

  byte voltPin;

  float get_voltage();
};

#endif

VoltageSense::VoltageSense(byte new_pin) {
  voltPin = new_pin;
}

float VoltageSense::get_voltage() {
  float val = 5.0 * analogRead(voltPin) / 1023.0;
  return val;
}