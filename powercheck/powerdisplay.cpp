#include "powerdisplay.hpp"
#include "font8_data.hpp"
#include "cherry.h"

Powerdisplay::Powerdisplay(void) : 
  st7735(160, 80, get_spi_pins(BG_SPI_FRONT)),
  graphics(st7735.width, st7735.height, nullptr),
  text_area(0, 0, 80, 80) {
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
      point.x = j + 88;
      point.y = i + 8;
      graphics.pixel(point);
    }
  }
  st7735.update(&graphics);
  graphics.set_font(&font8);
  graphics.set_clip(text_area);   
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