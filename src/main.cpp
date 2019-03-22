#include <Arduino.h>
#include <Logger.h>
#include <Motor.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <pins.h>

#define PWM_FREQ 10000
#define PWM_MAX 2460

// Motor motor1(PWM_LA, CURRENT_IN1, VOLTAGE_IN1);
// Motor motor2(PWM_OUT2, CURRENT_IN2, VOLTAGE_IN2);
volatile bool fault = false;
double pedal_power;
int fan_speed;
int pedal_adc;

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
  analogWriteFrequency(FAN1, PWM_FREQ);
  analogWriteFrequency(FAN2, PWM_FREQ);
  // analogWrite takes values from 0-4095, 4096 for HIGH
  analogWriteResolution(12);

  logger.init(115200);

  pinMode(STATUS, OUTPUT);
  pinMode(OCP_OUTA, OUTPUT);
  pinMode(OCP_OUTB, OUTPUT);
  pinMode(OCP_INA, INPUT);
  pinMode(OCP_INB, INPUT);
  pinMode(FAN1, OUTPUT);
  pinMode(FAN2, OUTPUT);

  logger.logg("Setup Done");

  // blink LED
  logger.logi("Blinking satus LED");
  digitalWrite(STATUS, HIGH);
  digitalWrite(OCP_OUTA, HIGH);
  digitalWrite(OCP_OUTB, HIGH);
  delay(200);
  // digitalWrite(STATUS, LOW);
  digitalWrite(OCP_OUTA, LOW);
  digitalWrite(OCP_OUTB, LOW);
  delay(200);

  // disable interrupts
  // cli();
  // attachInterrupt(FAULT_IN, fault_catch, CHANGE);
  // enable interrups
  // sei();
}

int current_readA;
int current_readB;
char buffer[50];
void loop() {
  // pedal_power = 4 * analogRead(PEDAL_IN);
  // for (int i = 0; i < 4096; i++) {
  //   analogWrite(PWM_LA, i);
  //   analogWrite(PWM_LB, i);
  //   delay(1);
  // }
  // for (int i = 4095;i >= 0; i--) {
  //   analogWrite(PWM_LA, i);
  //   analogWrite(PWM_LB, i);
  //   delay(1);
  // }

  pedal_adc = analogRead(PEDAL_IN);
  pedal_power = map(pedal_adc, 550, 900, 4095, 0);
  fan_speed = map(pedal_adc, 550, 900, 700, 1000);
  // sprintf(buffer, "Pedal reading: %f", pedal_power);
  // logger.logg(buffer);

  analogWrite(PWM_LA, pedal_power);
  analogWrite(PWM_LB, pedal_power);
  if (pedal_adc < 650) {
    fan_speed = 0;
  } else {
    fan_speed = map(pedal_adc, 550, 900, 700, 2000);
  }
  analogWrite(FAN1, fan_speed);
  analogWrite(FAN2, fan_speed);
  current_readA = analogRead(CURRENT_INA);
  current_readB = analogRead(CURRENT_INB);
  // delay(50);
  // Serial.print(1050);
  // Serial.print("\t");
  // Serial.println(current_readA);
  // Serial.print("\t");
  // Serial.println(current_readB);
  // Serial.print("\t");
  // Serial.println(-5);
  // sprintf(buffer, "Current reading: %u", current_read);
  // logger.logg(buffer);
  // digitalWrite(OCP_OUTA, digitalRead(OCP_INA));
  // digitalWrite(OCP_OUTB, digitalRead(OCP_INB));
}
