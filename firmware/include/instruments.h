#ifndef INSTRUMENTS_H_
#define INSTRUMENTS_H_
#include <Arduino.h>
#include "M5UnitSynthDef.h"

typedef struct {
    unit_synth_instrument_t instrument;
    const String display_name;
    // const String icon_path;
} instrument_t;

const int INSTRUMENT_COUNT = 24;

const instrument_t instruments[] = {
    {GrandPiano_1, "ピアノ"},
    {ElPiano1, "電子ピアノ"},
    {Vibraphone, "ヴィブラフォン"},
    {Marimba, "マリンバ"},
    {TubularBells, "管鐘"},
    {ChurchOrgan, "オルガン"},
    {AccordionFrench, "アコーディオン"},
    {Harmonica, "ハーモニカ"},
    {AcGuitarNylon, "アコギ"},
    {Violin, "バイオリン"},
    {Cello, "チェロ"},
    {Contrabass, "コントラバス"},
    {Trombone, "トロンボーン"},
    {Tuba, "チューバ"},
    {FrenchHorn, "ホルン"},
    {Trumpet, "トランペット"},
    {FrenchHorn, "ホルン"},
    {AltoSax, "アルトサックス"},
    {Oboe, "オーボエ"},
    {Clarinet, "クラリネット"},
    {Flute, "フルート"},
    {Recorder, "リコーダー"},
    {Ocarina, "オカリナ"},
    {Koto, "箏"},
};


#endif

