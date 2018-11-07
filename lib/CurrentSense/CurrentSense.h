#include <Arduino.h>
#ifndef CURRENTSENSE_H
#define CURRENTSENSE_H
class CurrentSense {
 public:
  CurrentSense(uint8_t newCurrentPin, float newRes);

  float resistance;

  uint8_t currentPin;

  float get_current();
};

#endif