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