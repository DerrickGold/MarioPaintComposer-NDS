#include <PA_BgStruct.h>

extern const char clearscreen_Tiles[];
extern const char clearscreen_Map[];
extern const char clearscreen_Pal[];

const PA_BgStruct clearscreen = {
	PA_BgNormal,
	256, 192,

	clearscreen_Tiles,
	clearscreen_Map,
	{clearscreen_Pal},

	9536,
	{1536}
};
