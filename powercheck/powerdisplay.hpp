#ifndef POWERDISPLAY
#define POWERDISPLAY

#include "drivers/st7735/st7735.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"

using namespace pimoroni;

class Powerdisplay {
private:
  ST7735 st7735;
  PicoGraphics_PenRGB332 graphics;
  Rect text_area;
  uint8_t text_color;
  uint8_t bg_color;

public:
    Powerdisplay(void);
    ~Powerdisplay(void);

    void countdown(char *p_seconds);

};

#endif // POWERDISPLAY