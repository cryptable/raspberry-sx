#include "powerdisplay.hpp"
#include "font8_data.hpp"
#include "cherry.h"

Powerdisplay::Powerdisplay(void) : 
  st7735(160, 80, get_spi_pins(BG_SPI_FRONT)),
  graphics(st7735.width, st7735.height, nullptr),
  text_area(70, 0, 110, 80) {
  st7735.set_backlight(255);
  this->bg_color = graphics.create_pen(0, 0, 0);
  this->text_color = graphics.create_pen(255,255,255);
  graphics.set_pen(this->bg_color);
  graphics.clear();
  const uint8_t *p_pixel = gimp_image.pixel_data;
  Point point = Point();
  for (uint i=0; i<gimp_image.height; i++) {
    for (uint j=0; j<gimp_image.width; j++) {
      uint8_t r = *p_pixel;
      p_pixel++;
      uint8_t g = *p_pixel;
      p_pixel++;
      uint8_t b = *p_pixel;
      p_pixel++;
      uint8_t graphics_pen = graphics.create_pen(r, g, b);
      graphics.set_pen(graphics_pen);
      point.x = j + 0;
      point.y = i + 8;
      graphics.pixel(point);
    }
  }
  st7735.update(&graphics);
  graphics.set_font(&font8);
  graphics.set_clip(text_area);   
}

void Powerdisplay::powerdata(float fVusb, float fAusb, float fVout, float fAout) {
  graphics.set_pen(this->text_color);
  char linePusb[14] = { 0x00 };
  char linePdev[14] = { 0x00 };
  char lineVusb[14] = { 0x00 };
  char lineAusb[14] = { 0x00 };
  char lineVdev[14] = { 0x00 };
  char lineAdev[14] = { 0x00 };
  float fPusb = fVusb * fAusb * 1000;
  float fPdev = fVout * fAout * 1000;

  sprintf(linePusb, "USB: %.0f mW", fPusb);
  sprintf(linePdev, "Dev: %.0f mW", fPdev);
  sprintf(lineVusb, "U usb: %.3f V", fVusb);
  sprintf(lineAusb, "I usb: %.0f mA", fAusb*1000);
  sprintf(lineVdev, "U dev: %.3f V", fVout);
  sprintf(lineAdev, "I dev: %.0f mA", fAout*1000);
  graphics.text(linePusb, Point(70,2), 110, 0);
  graphics.text(linePdev, Point(70,12),110, 0);
  graphics.text(lineVusb, Point(70,22),110, 0);
  graphics.text(lineAusb, Point(70,32),110, 0);
  graphics.text(lineVdev, Point(70,42),110, 0);
  graphics.text(lineAdev, Point(70,52),110, 0);

  st7735.update(&graphics);
}

void Powerdisplay::countdown(char *p_seconds) {
  graphics.set_pen(this->bg_color);
  graphics.clear();
  graphics.set_pen(this->text_color);
  graphics.text("Shutdown Pi", Point(0,0), 80, 0);
  graphics.text(p_seconds, Point(8,16), 80, 8);
  st7735.update(&graphics);
}

Powerdisplay::~Powerdisplay(void) {

}
