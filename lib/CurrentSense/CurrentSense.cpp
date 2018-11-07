#include <CurrentSense.h>

CurrentSense::CurrentSense(uint8_t newPin, float newRes) {
  currentPin = newPin;
}

float CurrentSense::get_current() {
  float val = 5.0 * analogRead(currentPin) / 1023.0;
  return val / resistance;
}