#include <Encoder.h>

Encoder::Encoder(int encoder_A, int encoder_B)
{
  encoder_pin1 = encoder_A;
  encoder_pin2 = encoder_B;
  encoder_counter = 0;
}

void Encoder::encoder_change(){
  // Serial.println("Interrupted");
  if (digitalRead(encoder_pin2) == HIGH)
  {
    encoder_counter += 1;
  } else
  {
    encoder_counter += -1;
  }
  // Serial.println(encoder_count);
}

int Encoder::get_value()
{
  attachInterrupt(encoder_pin1, encoder_change, RISING);
  delay(10);
  detachInterrupt(encoder_pin1);
  return encoder_counter;
}
