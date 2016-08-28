// Graphics converted using PAGfx by Mollusk.

#pragma once

#include <PA_BgStruct.h>

#ifdef __cplusplus
extern "C"{
#endif

// Sprites:
extern const unsigned char buttons_Sprite[1280] _GFX_ALIGN; // Palette: buttons_Pal
extern const unsigned char eraser_Sprite[512] _GFX_ALIGN; // Palette: eraser_Pal
extern const unsigned char invbutton_Sprite[4096] _GFX_ALIGN; // Palette: invbutton_Pal
extern const unsigned char mapsprites_Sprite[5120] _GFX_ALIGN; // Palette: mapsprites_Pal
extern const unsigned char mario_Sprite[1536] _GFX_ALIGN; // Palette: mario_Pal
extern const unsigned char notebar_Sprite[256] _GFX_ALIGN; // Palette: notebar_Pal
extern const unsigned char picked_Sprite[5120] _GFX_ALIGN; // Palette: picked_Pal
extern const unsigned char signs_Sprite[256] _GFX_ALIGN; // Palette: signs_Pal
extern const unsigned char sliders_Sprite[128] _GFX_ALIGN; // Palette: sliders_Pal

// Backgrounds:
extern const PA_BgStruct background;
extern const PA_BgStruct bar;
extern const PA_BgStruct clearscreen;
extern const PA_BgStruct credits;
extern const PA_BgStruct deletefile;
extern const PA_BgStruct deletepage;
extern const PA_BgStruct fbfont;
extern const PA_BgStruct header;
extern const PA_BgStruct insertpage;
extern const PA_BgStruct keyboard1;
extern const PA_BgStruct measures;
extern const PA_BgStruct mpcdownload;
extern const PA_BgStruct newsselection;
extern const PA_BgStruct title;
extern const PA_BgStruct topscreen;
extern const PA_BgStruct topscreenfb;
extern const PA_BgStruct topscreensd;

// Palettes:
extern const unsigned short buttons_Pal[256] _GFX_ALIGN;
extern const unsigned short eraser_Pal[256] _GFX_ALIGN;
extern const unsigned short invbutton_Pal[256] _GFX_ALIGN;
extern const unsigned short mapsprites_Pal[256] _GFX_ALIGN;
extern const unsigned short mario_Pal[256] _GFX_ALIGN;
extern const unsigned short notebar_Pal[256] _GFX_ALIGN;
extern const unsigned short picked_Pal[256] _GFX_ALIGN;
extern const unsigned short signs_Pal[256] _GFX_ALIGN;
extern const unsigned short sliders_Pal[256] _GFX_ALIGN;

#ifdef __cplusplus
}
#endif
