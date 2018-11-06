#include <Arduino.h>
#include <Motor.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <pins.h>
#define PWM_FREQ 14648.437

Motor motor1(PWM_OUT1, CURRENT_IN1, VOLTAGE_IN1);
Motor motor2(PWM_OUT2, CURRENT_IN2, VOLTAGE_IN2);
volatile bool brk;

void setup() {
  // set PWM frequency, (not 10kHz, 14k is chosen due to H/W)
  analogWriteFrequency(PWM_OUT1, PWM_FREQ);
  // analogWrite takes values from 0-4095, 4096 for HIGH
  analogWriteResolution(12);
  brk == false;
}

void loop() {
  // Get power setting from pedal
  motor1.update_power(pedal_power);
  motor1.pid_obj.Compute();
  motor2.update_power(pedal_power);
  motor2.pid_obj.Compute();
  if (brk == true) {
    motor1.set_power(0);
    motor2.set_power(0);
  }
}
