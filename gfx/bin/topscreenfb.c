#include <PA_BgStruct.h>

extern const char topscreenfb_Tiles[];
extern const char topscreenfb_Map[];
extern const char topscreenfb_Pal[];

const PA_BgStruct topscreenfb = {
	PA_BgNormal,
	256, 192,

	topscreenfb_Tiles,
	topscreenfb_Map,
	{topscreenfb_Pal},

	29440,
	{1536}
};
