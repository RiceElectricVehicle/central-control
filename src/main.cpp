#include <Arduino.h>
#include <Motor.h>
#include <OLED.h>
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
volatile long revolutions;
volatile bool brk;
volatile double rpm;

OLED OLED_screen;
IntervalTimer encoder_timer;

void fault_catch() {
  if (fault) {
    fault = false;
  } else {
    fault = true;
  }
}

void brake_isr() {
  if (brk)
    brk = false;
  else
    brk = true;
}

void enc_isr() {
  revolutions = revolutions + 1;
}

void get_rpm() {
  cli();
  rpm = revolutions * 60;
  revolutions = 0;
  sei();
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


  pinMode(STATUS, OUTPUT);
  pinMode(OCP_OUTA, OUTPUT);
  pinMode(OCP_OUTB, OUTPUT);
  pinMode(OCP_INA, INPUT);
  pinMode(OCP_INB, INPUT);
  pinMode(FAN1, OUTPUT);
  pinMode(FAN2, OUTPUT);
  pinMode(BRAKE, INPUT);


  // blink LED
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

  Serial.begin(115200);
  encoder_timer.begin(get_rpm, 1000000);
  attachInterrupt(BRAKE, brake_isr, CHANGE);
  attachInterrupt(ENCYZ, enc_isr, RISING);
  OLED_screen.init(&rpm);
}

int current_readA;
int current_readB;
void loop() {

  pedal_adc = analogRead(PEDAL_IN);
  Serial.println(pedal_adc);
  pedal_adc = constrain(pedal_adc, 500, 900);
  pedal_power = map(pedal_adc, 560, 840, 4095, 0);

  if (brk == true) {
    // Display breaking
    analogWrite(PWM_LA, 4096);
    analogWrite(PWM_LB, 4096);
    OLED_screen.display_breaking();
  } else {
    analogWrite(PWM_LA, pedal_power);
    analogWrite(PWM_LB, pedal_power);
    OLED_screen.display_rotate();
  }

  if (pedal_adc < 650) {
    fan_speed = 0;
  } else {
    fan_speed = map(pedal_adc, 600, 900, 700, 2000);
  }
  analogWrite(FAN1, fan_speed);
  analogWrite(FAN2, fan_speed);
  Serial.print(pedal_adc);
  Serial.print("\t\t");
  Serial.print(pedal_power);
  Serial.print("\t\t");
  Serial.println(fan_speed);
  // current_readA = analogRead(CURRENT_INA);
  // current_readB = analogRead(CURRENT_INB);
  // delay(50);
  // Serial.print(1050);
  // Serial.print("\t");
  // Serial.println(current_readA);
  // Serial.print("\t");
  // Serial.println(current_readB);
  // Serial.print("\t");
  // Serial.println(-5);
  // digitalWrite(OCP_OUTA, digitalRead(OCP_INA));
  // digitalWrite(OCP_OUTB, digitalRead(OCP_INB));
}
