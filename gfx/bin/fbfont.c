#include <PA_BgStruct.h>

extern const char fbfont_Tiles[];
extern const char fbfont_Map[];
extern const char fbfont_Pal[];

const PA_BgStruct fbfont = {
	PA_BgNormal,
	256, 192,

	fbfont_Tiles,
	fbfont_Map,
	{fbfont_Pal},

	3968,
	{1536}
};
