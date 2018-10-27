#ifndef PINS_H
#define PINS_H

// LED teensy status
#define STATUS 32
#define PWM_OUT 30
// active low input from gatedriver showing status
#define FAULT_IN 24
// LED to represent gatedriver underVoltage/overCurrent status
#define FAULT_OUT 7
// A0 - used for current sense opamp input
#define OP_IN 14
// A1 - used for pedal position input
#define PEDAL_IN 15
#define GPIO2 2
#define GPIO3 1
#define GPIO4 0

#endif  // PINS_H