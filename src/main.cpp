#include <Arduino.h>
#include <Motor.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <pins.h>
#include <IntervalTimer.h>

#define PWM_FREQ 14648.437

IntervalTimer pidTimer;
IntervalTimer getPower;
Motor motorA(PWM_LA, CURRENT_INA);
Motor motorB(PWM_LB, CURRENT_INB);
long time;
volatile long encAcnt;
volatile long encBcnt;
volatile bool brk;
double pedal_power;

void setup() {
  // set PWM frequency, (not 10kHz, 14k is chosen due to H/W)
  analogWriteFrequency(PWM_LA, PWM_FREQ);
  analogWriteFrequency(PWM_LB, PWM_FREQ);
  // analogWrite takes values from 0-4095, 4096 for HIGH
  analogWriteResolution(12);
  brk == false;
}

void loop() {
  // Get power setting from pedal
  pedal_power = analogRead(PEDAL_IN);
  if (brk == true) {
    motorA.set_power(0);
    motorB.set_power(0);
  }
}

void powerIntervalTimer() {
  motorA.update_power();
  motorB.update_power();
}

void pidIntervalTimer() {
  motorA.set_power(pedal_power);
  motorB.set_power(pedal_power);
}

void encAISR() {
  encAcnt++;
}

void encBISR() {
  encBcnt++;
}
