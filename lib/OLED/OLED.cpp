#include <Arduino.h>
#include <OLED.h>
#include <SPI.h>
#include <U8g2lib.h>

OLED::OLED()
    : screen_object(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8)
{
  screen_height = 0;
  screen_width = 0;
  cursor_x = 0;
  cursor_y = 0;
}

void OLED::set_cursors()
{
  cursor_x = (screen_width - string_width) / 2;
  cursor_y = screen_height / 2;
}

void OLED::init(double* rpm)
{
  rpm_address = rpm;
  screen_object.begin();
  screen_height = screen_object.getDisplayHeight();
  screen_width = screen_object.getDisplayWidth();
  string_width = screen_object.getStrWidth("Hello World!");
  screen_object.setFontPosCenter();
  OLED::set_cursors();
  screen_object.firstPage();
  do
  {
    screen_object.setCursor(cursor_x, cursor_y);
    screen_object.setFont(u8g2_font_inr30_mf);
    screen_object.print("Hello World!");
  } while (screen_object.nextPage());
}

void OLED::display_breaking()
{
  screen_object.clear();
  screen_object.setFont(u8g2_font_inr38_mf);
  string_width = screen_object.getStrWidth("Breaking");
  OLED::set_cursors();
  screen_object.firstPage();
  do
  {
    screen_object.setCursor(cursor_x, cursor_y);
    screen_object.print("Breaking");
  } while (screen_object.nextPage());
}

void OLED::display_rpm()
{
  screen_object.clear();
  screen_object.setFont(u8g2_font_inr38_mf);
  int now_rpm = *rpm_address;
  // Haven't thought of a better way to get string length. It is a placeholder.
  string_width = screen_object.getStrWidth("1000 rpm");
  OLED::set_cursors();
  screen_object.firstPage();
  do
  {
    screen_object.setCursor(cursor_x, cursor_y);
    screen_object.print(now_rpm);
    screen_object.print(" rpm");
  } while (screen_object.nextPage());
}

void OLED::display_speed()
{
  screen_object.clear();
  screen_object.setFont(u8g2_font_inr49_mf);
  int now_rpm = *rpm_address;
  // Need to figure out the way to calculate speed from rpm
  int now_speed = now_rpm / 100;
  // Haven't thought of a better way to get string length. It is a placeholder.
  string_width = screen_object.getStrWidth("60 mph");
  OLED::set_cursors();
  screen_object.firstPage();
  do
  {
    screen_object.setCursor(cursor_x, cursor_y);
    screen_object.print(now_speed);
    screen_object.print(" mph");
  } while (screen_object.nextPage());
}

void OLED::display_rotate()
{
  OLED::display_speed();
  delay(5000);
  OLED::display_rpm();
  delay(5000);
}
