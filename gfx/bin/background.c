#include <PA_BgStruct.h>

extern const char background_Tiles[];
extern const char background_Map[];
extern const char background_Pal[];

const PA_BgStruct background = {
	PA_BgNormal,
	256, 192,

	background_Tiles,
	background_Map,
	{background_Pal},

	36608,
	{1536}
};
