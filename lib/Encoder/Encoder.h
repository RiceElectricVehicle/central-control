#include <Arduino.h>

#ifndef ENCODER_H
#define ENCODER_H

class Encoder
{
public:
  Encoder(int encoder_A, int encoder_B);
  int get_value();

private:
  static int encoder_pin1;
  static int encoder_pin2;
  static volatile int encoder_counter;
  static void encoder_change();
};


#endif
