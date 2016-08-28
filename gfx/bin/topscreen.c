#include <PA_BgStruct.h>

extern const char topscreen_Tiles[];
extern const char topscreen_Map[];
extern const char topscreen_Pal[];

const PA_BgStruct topscreen = {
	PA_BgNormal,
	256, 192,

	topscreen_Tiles,
	topscreen_Map,
	{topscreen_Pal},

	20544,
	{1536}
};
