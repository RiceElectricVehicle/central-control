#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>

#ifndef OLED_H
#define OLED_H

class OLED{
private:
  // U8G2 screen_object;
  U8G2_SSD1322_NHD_256X64_1_4W_HW_SPI screen_object;
  int screen_height;
  int screen_width;
  volatile int cursor_x;
  volatile int cursor_y;
  volatile int string_width;
  double* rpm_address;
  void set_cursors();

public:
  OLED();
  void init(double* rpm);
  void display_breaking();
  void display_rpm();
  void display_speed();
  void display_rotate();
};

#endif
