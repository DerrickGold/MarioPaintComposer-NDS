#include <PA_BgStruct.h>

extern const char insertpage_Tiles[];
extern const char insertpage_Map[];
extern const char insertpage_Pal[];

const PA_BgStruct insertpage = {
	PA_BgNormal,
	256, 192,

	insertpage_Tiles,
	insertpage_Map,
	{insertpage_Pal},

	9856,
	{1536}
};
