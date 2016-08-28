#include <PA_BgStruct.h>

extern const char bar_Tiles[];
extern const char bar_Map[];
extern const char bar_Pal[];

const PA_BgStruct bar = {
	PA_BgNormal,
	256, 256,

	bar_Tiles,
	bar_Map,
	{bar_Pal},

	128,
	{2048}
};
