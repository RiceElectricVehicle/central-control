#include <Arduino.h>
#include <Motor.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <pins.h>
#include <OLED.h>

#define PWM_FREQ 14648.437


// Motor motor1(PWM_OUT1, CURRENT_IN1, VOLTAGE_IN1);
// Motor motor2(PWM_OUT2, CURRENT_IN2, VOLTAGE_IN2);
// Encoder encoder(ENCXA, ENCXB);
OLED OLED_screen;
Motor motorA(PWM_LA, CURRENT_INA);
Motor motorB(PWM_LB, CURRENT_INB);
volatile long revolutions;
volatile bool brk;
double pedal_power;
double rpm;

void brake_isr() {
  if (brk)
    brk = false;
  else
    brk = true;
}

void enc_isr() {
  revolutions++;
}

double get_rpm(uint32_t time_now) {
  static uint32_t time_old = 0;
  double rpm_new = revolutions / (60 * (time_now - time_old));
  time_old = millis();
  return rpm_new;
}

void setup() {
  pinMode(PWM_LA, OUTPUT);
  pinMode(PWM_LB, OUTPUT);
  digitalWrite(PWM_LA, HIGH);
  digitalWrite(PWM_LB, HIGH);
  // set PWM frequency, (not 10kHz, 14k is chosen due to H/W)
  // analogWriteFrequency(PWM_OUT1, PWM_FREQ);
  // analogWrite takes values from 0-4095, 4096 for HIGH
  analogWriteResolution(12);
  brk == false;
  Serial.begin(115200);
  analogWriteFrequency(PWM_LA, PWM_FREQ);
  analogWriteFrequency(PWM_LB, PWM_FREQ);
  // analogWrite takes values from 0-4095, 4096 for HIGH
  analogWriteResolution(12);

  pinMode(STATUS, OUTPUT);
  pinMode(OCP_OUTA, OUTPUT);
  pinMode(OCP_OUTB, OUTPUT);
  pinMode(OCP_INA, INPUT);
  pinMode(OCP_INB, INPUT);

  // blink LED
  digitalWrite(STATUS, HIGH);
  digitalWrite(OCP_OUTA, HIGH);
  digitalWrite(OCP_OUTB, HIGH);
  delay(200);
  digitalWrite(STATUS, LOW);
  digitalWrite(OCP_OUTA, LOW);
  digitalWrite(OCP_OUTB, LOW);
  delay(200);

  // disable interrupts
  cli();
  // attachInterrupt(FAULT_IN, fault_catch, CHANGE);
  attachInterrupt(BRAKE, brake_isr, CHANGE);
  attachInterrupt(ENCXZ, enc_isr, RISING);
  // enable interrups
  sei();
  // Start screen
  OLED_screen.init(&rpm);
  motorA.start();
  motorB.start();
}

void loop() {
  // Get power setting from pedal
  pedal_power = analogRead(PEDAL_IN);
  // motor1.set_power(pedal_power);
  // motor2.set_power(pedal_power);
  // if (brk == true) {
  //   motor1.set_power(0);
  //   motor2.set_power(0);
  // }
  // int value = encoder.get_value();
  // Serial.println(value);
  delay(100);
  pedal_power = map(analogRead(PEDAL_IN), 550, 900, 0, 4096);
  if (brk == true) {
    motorA.set_zero();
    motorB.set_zero();
    OLED_screen.display_breaking();
  } else {
    motorA.update_pid_input();
    motorB.update_pid_input();
    // Run PID computations.
    motorA.compute_pid(pedal_power);
    motorB.compute_pid(pedal_power);
    // Update PWM outputs.
    motorA.set_pwm();
    motorB.set_pwm();
    OLED_screen.display_rotate();
  }
  rpm = get_rpm(millis());
}
