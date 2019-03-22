#include <Arduino.h>
#include <Motor.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <pins.h>
#include <PID_v1.h>

#define PWM_FREQ 14648.437

volatile long revolutions;
volatile bool brk;
double pedal_power;
double rpm;

double pid_inA, pid_outA, pid_setA;
double pid_inB, pid_outB, pid_setB;

Motor motorA(PWM_LA, CURRENT_INA);
Motor motorB(PWM_LB, CURRENT_INB);
PID pidA(&pid_inA, &pid_outA, &pid_setA, 1, 1, 0, REVERSE);
PID pidB(&pid_inB, &pid_outB, &pid_setB, 1, 1, 0, REVERSE);

void pinSetup();
void pwmSetup();
void pidSetup();
void powerUpBlink();
void enc_isr();
void brake_isr();
double get_rpm();


void setup() {
  delay(3000);
  Serial.begin(115200);
  Serial.println("Starting");
  Serial.println("Pin setup");
  pinSetup();
  Serial.println("PWM setup");
  pwmSetup();
  Serial.println("Blink");
  powerUpBlink();
  Serial.println("Interrupt setup");
  // disable interrupts
  cli();
  // attachInterrupt(FAULT_IN, fault_catch, CHANGE);
  attachInterrupt(BRAKE, brake_isr, CHANGE);
  attachInterrupt(ENCXZ, enc_isr, RISING);
  // enable interrups
  sei();
  Serial.println("PID setup");
  pidSetup();
  Serial.println("Setup done");
}

void loop() {
  // Get power setting from pedal
  pedal_power = map(analogRead(PEDAL_IN), 550, 900, 4090, 0);
  if (brk == true) {
    motorA.set_zero();
    motorB.set_zero();
  } else {
    pid_inA = motorA.get_current() * motorA.get_voltage();
    pid_inB = motorB.get_current() * motorB.get_voltage();
    pid_setA = pedal_power;
    pid_setB = pedal_power;
    // Run PID computations.
    pidA.Compute();
    pidB.Compute();
    // Update PWM outputs.
    motorA.set_pwm(pid_outA);
    motorB.set_pwm(pid_outB);
  }
  rpm = get_rpm(millis());
}

void pinSetup() {
  // Gate Driver outputs
  pinMode(PWM_LA, OUTPUT);
  pinMode(PWM_LB, OUTPUT);
  digitalWrite(PWM_LA, HIGH);
  digitalWrite(PWM_LB, HIGH);
  // Status LEDs
  pinMode(STATUS, OUTPUT);
  pinMode(OCP_OUTA, OUTPUT);
  pinMode(OCP_OUTB, OUTPUT);
  pinMode(OCP_INA, INPUT);
  pinMode(OCP_INB, INPUT);
}

void pwmSetup() {
  // set PWM frequency, (not 10kHz, 14k is chosen due to H/W)
  analogWriteFrequency(PWM_LA, PWM_FREQ);
  analogWriteFrequency(PWM_LB, PWM_FREQ);
  // analogWrite takes values from 0-4095, 4096 for HIGH
  analogWriteResolution(12);
}

void powerUpBlink() {
  // blink LED
  digitalWrite(STATUS, HIGH);
  digitalWrite(OCP_OUTA, HIGH);
  digitalWrite(OCP_OUTB, HIGH);
  delay(200);
  digitalWrite(STATUS, LOW);
  digitalWrite(OCP_OUTA, LOW);
  digitalWrite(OCP_OUTB, LOW);
  delay(200);
}

void pidSetup() {
  pidA.SetOutputLimits(0, 4096);
  pidB.SetOutputLimits(0, 4096);
  pidA.SetMode(AUTOMATIC);
  pidB.SetMode(AUTOMATIC);
  Serial.println("Setup done");
}

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
