#include <Arduino.h>
#include <Motor.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <pins.h>

#define PWM_FREQ 14648.437

Motor motorA(PWM_LA, CURRENT_INA);
Motor motorB(PWM_LB, CURRENT_INB);
volatile bool brk;
double pedal_power;

void setup() {
  // set PWM frequency, (not 10kHz, 14k is chosen due to H/W)
  analogWriteFrequency(PWM_LA, PWM_FREQ);
  // analogWrite takes values from 0-4095, 4096 for HIGH
  analogWriteResolution(12);
  brk == false;
}

void loop() {
  // Get power setting from pedal
  pedal_power = analogRead(PEDAL_IN);
  motorA.set_power(pedal_power);
  motorB.set_power(pedal_power);
  if (brk == true) {
    motorA.set_power(0);
    motorB.set_power(0);
  }
}
