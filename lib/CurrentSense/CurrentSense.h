#include <Arduino.h>
#include <pins.h>

#ifndef CURRENTSENSE_H
#define CURRENTSENSE_H

class CurrentSense {
 public:
  CurrentSense(uint8_t newCurrentPin, float newRes);

  float resistance;

  uint8_t currentPin;

  float getCurrent();
};

CurrentSense::CurrentSense(uint8_t newPin, float newRes) {
  currentPin = newPin;
}

float CurrentSense::getCurrent() {
  int val = 5.0 * analogRead(currentPin) / 1023.0;
  return val / resistance;
}

#endif  // CURRENTSENSE_H