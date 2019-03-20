#ifndef PINS_H
#define PINS_H

// LED teensy status
#define STATUS 31

// PWM Outputs
#define PWM_LA 30
#define PWM_HA 29
#define PWM_HB 36
#define PWM_LB 35

// active low input from gatedriver Over Current Protection (OCP) Status
#define OCP_INA 24
#define OCP_INB 26

// LED to represent gatedriver OCP Status
#define OCP_OUTA 7
#define OCP_OUTB 6

// Current Sense inputs from halfbridges
#define CURRENT_INA 15
#define CURRENT_INB 14

// Encoder pins.
#define ENCXA 3
#define ENCXB 4
#define ENCXZ 5
#define ENCYA 32
#define ENCYB 25
#define ENCYZ 28

// General control I/O
#define PEDAL_IN 16
#define BRAKE 2
#define GPIO0 0

// OLED pins
#define D_RST 8
#define DC    9
#define CS    10
#define MOSI  11
#define SCLK  13

#endif  // PINS_H
