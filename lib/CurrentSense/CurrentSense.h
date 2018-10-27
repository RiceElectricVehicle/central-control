#include <Arduino.h>
#include <pins.h>

#ifndef CURRENTSENSE_H
#define CURRENTSENSE_H

class CurrentSense {
 public:
  CurrentSense(uint8_t newPin, float newRes, bool parallel);

  float resistance;

  uint8_t pin;

  float getCurrent();

  void setResistance(float newRes);
};

CurrentSense::CurrentSense(uint8_t newPin, float newRes, bool parallel) {
  if (parallel) {
    resistance = newRes / 2.0;
  } else {
    resistance = newRes;
  }
  pin = newPin;
}

float CurrentSense::getCurrent() {
  int val = 5.0 * analogRead(pin) / 1023.0;
  return val;
}

void CurrentSense::setResistance(float newRes) {
  resistance = newRes;
}

#endif  // CURRENTSENSE_H