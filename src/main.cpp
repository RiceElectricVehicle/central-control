#include <Arduino.h>
#include <Motor.h>
#include <pins.h>
#define PWM_FREQ 14648.437

Motor motor1();

void setup() {
  // set PWM frequency, (not 10kHz, 14k is chosen due to H/W)
  analogWriteFrequency(PWM_OUT, PWM_FREQ);
  // analogWrite takes values from 0-4095, 4096 for HIGH
  analogWriteResolution(12);
}

void loop() {
  for (int i = 0; i < 4096; i++) {
    analogWrite(PWM_OUT, i);
    delay(100);
  }
}
