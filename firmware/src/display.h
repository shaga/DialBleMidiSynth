#pragma once
#include <M5GFX.h>
#include <M5Dial.h>

class Display {
public:
  Display() : display_(M5Dial.Display) {}
  void begin();
  void update();
  void clear(bool update = true);
  void drawText(int x, int y, const String& text, bool update = true);
  void drawText(int x, int y, const String& text, textdatum_t datum, bool update = true);
  void drawText(int x, int y, const String& text, int text_color, bool update = true);
  void drawText(int x, int y, const String& text, int text_color, textdatum_t datum, bool update = true);
  void fillRect(int x, int y, int width, int height, int color, bool update = true);
  void drawVolume(int volume, bool is_volume_mode);
  void drawInstrument(int instrument);
  int width() const { return display_.width(); }
  int height() const { return display_.height(); }

  static const int TEXT_HEIGHT;

private:
  M5GFX& display_;
  M5Canvas canvas_device_;
  M5Canvas canvas_volume_;
  M5Canvas canvas_instrument_;
  void pushCanvas(bool update);
}; 