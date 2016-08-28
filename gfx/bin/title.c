#include <PA_BgStruct.h>

extern const char title_Tiles[];
extern const char title_Map[];
extern const char title_Pal[];

const PA_BgStruct title = {
	PA_BgNormal,
	256, 192,

	title_Tiles,
	title_Map,
	{title_Pal},

	29504,
	{1536}
};
