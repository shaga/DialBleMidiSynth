#include "display.h"
#include "instruments.h"
#include <SPIFFS.h>

const int Display::TEXT_HEIGHT = 24;

void Display::begin() {
  display_.begin();
  canvas_device_.createSprite(display_.width(), display_.height());
  canvas_device_.setTextColor(WHITE);
  canvas_device_.setBaseColor(BLACK);
  canvas_device_.setFont(&fonts::lgfxJapanGothic_24);

  canvas_volume_.createSprite(display_.width(), display_.height());
  canvas_volume_.setBaseColor(BLACK);

  canvas_instrument_.createSprite(display_.width() - 40, 24);
  canvas_instrument_.setBaseColor(BLACK);
  canvas_instrument_.setTextColor(WHITE);
  canvas_instrument_.setFont(&fonts::lgfxJapanGothic_24);
  canvas_instrument_.setTextDatum(middle_center);
}

void Display::update() {
  canvas_device_.pushSprite(&display_, 0, 0);
}

void Display::clear(bool update) {
  canvas_device_.clear();

  pushCanvas(update);
}

void Display::drawText(int x, int y, const String& text, bool update) {
  canvas_device_.drawString(text, x, y);

  pushCanvas(update);
}

void Display::drawText(int x, int y, const String& text, textdatum_t datum, bool update) {
  canvas_device_.setTextDatum(datum);
  drawText(x, y, text, update);
}

void Display::drawText(int x, int y, const String& text, int text_color, bool update) {
  canvas_device_.setTextColor(text_color);
  drawText(x, y, text, update);
}

void Display::drawText(int x, int y, const String& text, int text_color, textdatum_t datum, bool update) {
  canvas_device_.setTextDatum(datum);
  canvas_device_.setTextColor(text_color);
  drawText(x, y, text, update);
}

void Display::fillRect(int x, int y, int width, int height, int color, bool update) {
  canvas_device_.fillRect(x, y, width, height, color);

  pushCanvas(update);
}

void Display::pushCanvas(bool update) {
    if (!update) {
        return;
    }
    canvas_device_.pushSprite(&display_, 0, 0);
}

void Display::drawVolume(int volume, bool is_volume_mode) {
  canvas_volume_.clear();
  const float START_MIN = 150;
  const float VOLUME_ANGLE = 240;
  const float END_MAX = START_MIN + VOLUME_ANGLE;

  float angle = START_MIN + VOLUME_ANGLE * (volume / 127.0f);

  const int color = is_volume_mode ? RED: GREEN;

  if (volume > 0) canvas_volume_.fillArc(width() / 2, height() / 2, width() / 2, width() / 2 - 5, START_MIN, angle, color);
  if (volume < 127) canvas_volume_.fillArc(width() / 2, height() / 2, width() / 2, width() / 2 - 5, angle, END_MAX, LIGHTGREY);
  canvas_volume_.pushSprite(&display_, 0, 0, BLACK);
}

void Display::drawInstrument(int instrument) {
  canvas_instrument_.clear();
  canvas_instrument_.setTextDatum(middle_center);
  canvas_instrument_.drawString(instruments[instrument].display_name, canvas_instrument_.width() / 2, 12);
  canvas_instrument_.pushSprite(&display_, (width() - canvas_instrument_.width()) / 2, (height() - canvas_instrument_.height()) / 2);
}

