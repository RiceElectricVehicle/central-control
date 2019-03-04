#include <CurrentSense.h>
CurrentSense::CurrentSense(uint8_t newPin) {
  currentPin = newPin;
}

float CurrentSense::get_current() {
  float val = 3.3 * analogRead(currentPin) / 1023.0;
  // Remove op amp gain
  val = val / 41;
  // Account for averaging effect of low pass filter.
  val = 2 * val;
  // I = V / R, R = .004 -> 1/R = 250
  return 250 * val;
}
