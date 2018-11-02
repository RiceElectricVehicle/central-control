#include <CurrentSense.h>
#include <PID_v1.h>
#include <pins.h>
#ifndef MOTOR_H
#define MOTOR_H
#define RESISTANCE .047

Motor::Motor()
{
  // All values are set to zero now. What they should actually be should be determined
  // after discussion
  current = 0; //May subject to change. Maybe just use the value from CurrentSense
  voltage = 0; //Same as above
  measuredPower = 0;
  setPoint = 0;
  outpower = 0;
  kp = 0;
  ki = 0;
  kd = 0;
  // I am not sure whether the objects should be initialised this way
  PID pidObj(&measuredPower, &outpoint, &setPoint, kp, ki, kd, DIRECT); // What does DIRECT mean?
  CurrentSense currentsense(newCurrentPin, newRes);
}

void Motor::update_power()
{

}

void Motor::set_power(float pedal_power)
{
  setPoint = pedal_power;
}

void Motor::get_power()
{
  return measuredPower;
}
