#include <Arduino.h>
#include <pins.h>

void setup() {
  // set PWM frequency, (not 10kHz, 14k is chosen due to H/W)
  analogWriteFrequency(PWM_OUT, 14648.437);
  // analogWrite takes values from 0-4095, 4096 for HIGH
  analogWriteResolution(PWM_OUT);
}

void loop() {
  for (int i = 0; i < 4096; i++) {
    analogWrite(PWM_OUT, i);
    delay(100);
  }
}
