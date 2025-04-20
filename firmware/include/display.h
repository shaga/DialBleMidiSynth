#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <M5GFX.h>

class Display {
  public:
    static const int TEXT_HEIGHT;
    void begin();
    void update();
    
    int width() const { return display_.width(); }
    int height() const { return display_.height(); }

    void clear(bool update = false);
    void drawText(int x, int y, const String& text, bool update = false);
    void drawText(int x, int y, const String& text, textdatum_t datum, bool update = false);
    void drawText(int x, int y, const String& text, int text_color, bool update = false);
    void drawText(int x, int y, const String& text, int text_color, textdatum_t datum, bool update = false);
    void fillRect(int x, int y, int width, int height, int color, bool update = false);

    void drawVolume(int volume, bool is_volume_mode);
    void drawInstrument(int instrument);
  private:
    M5GFX display_;
    M5Canvas canvas_device_;
    M5Canvas canvas_volume_;
    M5Canvas canvas_instrument_;

    void pushCanvas(bool update);
};


#endif
