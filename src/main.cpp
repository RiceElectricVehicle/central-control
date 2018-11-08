#include <Arduino.h>
#include <Logger.h>
#include <Motor.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <pins.h>

#define PWM_FREQ 10000

// Motor motor1(PWM_OUT1, CURRENT_IN1, VOLTAGE_IN1);
// Motor motor2(PWM_OUT2, CURRENT_IN2, VOLTAGE_IN2);
volatile bool brk;
double pedal_power;

Logger logger("REV MC2018", "info");

void setup() {
  // set PWM frequency, (not 10kHz, 14k is chosen due to H/W)
  analogWriteFrequency(PWM_OUT1, PWM_FREQ);
  // analogWrite takes values from 0-4095, 4096 for HIGH
  analogWriteResolution(12);
  brk == false;
  logger.init(115200);
  pinMode(STATUS, OUTPUT);
  logger.logg("Setup Done");
  delay(5000);
  // blink LED
  logger.logi("Blinking satus LED");
  digitalWrite(STATUS, HIGH);
  delay(200);
  digitalWrite(STATUS, LOW);
  delay(200);
}

void loop() {
  pedal_power = 4 * analogRead(PEDAL_IN);
  analogWrite(PWM_OUT1, pedal_power);
}
