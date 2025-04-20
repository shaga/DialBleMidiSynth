#include <Arduino.h>
#include <M5UnitSynth.h>
#include <BLEMidi.h>
#include "display.h"
#include "M5Dial.h"
#include "BleMidiSelector.h"
#include "instruments.h"
#include <M5Unified.h>

// Global variables
M5UnitSynth synth;
Display display;

uint8_t volume = 64;
uint8_t instrument = 0;
bool is_volume_mode = false;
int old_enc = 0;

static void onNoteOn(uint8_t channel, uint8_t note, uint8_t velocity, uint16_t timestamp)
{
  synth.setNoteOn(channel, note, velocity);
}

static void onNoteOff(uint8_t channel, uint8_t note, uint8_t velocity, uint16_t timestamp)
{
  synth.setNoteOff(channel, note, velocity);
}

static void onControlChange(uint8_t channel, uint8_t control, uint8_t value, uint16_t timestamp)
{
  synth.setControlChange(channel, control, value);
}

static void changeVolume(int offset)
{
  if (volume == 0 && offset < 0)
    return;
  if (volume == 127 && offset > 0)
    return;

  if (volume + offset < 0)
    volume = 0;
  else if (volume + offset > 127)
    volume = 127;
  else
    volume += offset;

  synth.setVolume(1, volume);
  display.drawVolume(volume, is_volume_mode);
}

static void setVolume()
{
  int current_enc = M5Dial.Encoder.read();

  if (abs(current_enc - old_enc) < 4)
    return;

  if (current_enc < old_enc)
  {
    changeVolume(-1);
  }
  else if (current_enc > old_enc)
  {
    changeVolume(1);
  }

  old_enc = current_enc;
}

static void setInstrument()
{
  int current_enc = M5Dial.Encoder.read();

  if (abs(current_enc - old_enc) < 4)
    return;

  if (current_enc < old_enc)
  {
    instrument = (instrument - 1 + INSTRUMENT_COUNT) % INSTRUMENT_COUNT;
  }
  else if (current_enc > old_enc)
  {
    instrument = (instrument + 1) % INSTRUMENT_COUNT;
  }

  synth.setInstrument(0, 1, instrument);
  display.drawInstrument(instrument);

  old_enc = current_enc;
}

void setup()
{
  M5Dial.begin(true, false);
  display.begin();
  display.clear();
  synth.begin(&Serial2, UNIT_SYNTH_BAUD, 15, 13);
  synth.setVolume(1, volume);

  BLEMidiClient.begin("hoge");
}

void loop()
{
  if (BLEMidiClient.isConnected())
  {
    M5Dial.update();

    if (M5Dial.BtnA.wasDoubleClicked())
    {
      is_volume_mode = !is_volume_mode;
      display.drawVolume(volume, is_volume_mode);
    }

    if (is_volume_mode)
    {
      // ボタンを押している間は、ボリュームを変更する
      setVolume();
    }
    else
    {
      setInstrument();
    }
  }
  else
  {
    if (connectBleMidiDevice())
    {
      is_volume_mode = false;
      BLEMidiClient.setNoteOnCallback(onNoteOn);
      BLEMidiClient.setNoteOffCallback(onNoteOff);
      BLEMidiClient.setControlChangeCallback(onControlChange);
      old_enc = M5Dial.Encoder.readAndReset();
      display.drawVolume(volume, is_volume_mode);
      display.drawInstrument(instrument);
    }
  }
}
