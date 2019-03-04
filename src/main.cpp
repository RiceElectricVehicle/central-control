#include <Arduino.h>
#include <Logger.h>
#include <Motor.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <pins.h>

#define PWM_FREQ 10000

// Motor motor1(PWM_LA, CURRENT_IN1, VOLTAGE_IN1);
// Motor motor2(PWM_OUT2, CURRENT_IN2, VOLTAGE_IN2);
volatile bool fault = false;
double pedal_power;

Logger logger("REV MC2018", "info");

void fault_catch() {
  if (fault) {
    fault = false;
  } else {
    fault = true;
  }
}

void setup() {

  pinMode(PWM_LA, OUTPUT);
  pinMode(PWM_LB, OUTPUT);
  digitalWrite(PWM_LA, HIGH);
  digitalWrite(PWM_LB, HIGH);
  // set PWM frequency, (not 10kHz, 14k is chosen due to H/W)
  analogWriteFrequency(PWM_LA, PWM_FREQ);
  analogWriteFrequency(PWM_LB, PWM_FREQ);
  // analogWrite takes values from 0-4095, 4096 for HIGH
  analogWriteResolution(12);

  logger.init(115200);

  pinMode(STATUS, OUTPUT);
  pinMode(OCP_OUTA, OUTPUT);
  pinMode(OCP_OUTB, OUTPUT);
  pinMode(OCP_INA, INPUT);
  pinMode(OCP_INB, INPUT);

  // logger.logg("Setup Done");

  // blink LED
  // logger.logi("Blinking satus LED");
  // digitalWrite(STATUS, HIGH);
  // delay(200);
  // digitalWrite(STATUS, LOW);
  // delay(200);

  // disable interrupts
  // cli();
  // attachInterrupt(FAULT_IN, fault_catch, CHANGE);
  // enable interrups
  // sei();
}

void loop() {
  pedal_power = 4 * analogRead(PEDAL_IN);
  analogWrite(PWM_LA, pedal_power);
  analogWrite(PWM_LB, pedal_power);

  digitalWrite(OCP_OUTA, digitalRead(OCP_INA));
  digitalWrite(OCP_OUTB, digitalRead(OCP_INB));
}
