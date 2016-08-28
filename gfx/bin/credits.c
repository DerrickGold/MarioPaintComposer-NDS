#include <PA_BgStruct.h>

extern const char credits_Tiles[];
extern const char credits_Map[];
extern const char credits_Pal[];

const PA_BgStruct credits = {
	PA_BgNormal,
	256, 192,

	credits_Tiles,
	credits_Map,
	{credits_Pal},

	23168,
	{1536}
};
