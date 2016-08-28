#include <PA_BgStruct.h>

extern const char topscreensd_Tiles[];
extern const char topscreensd_Map[];
extern const char topscreensd_Pal[];

const PA_BgStruct topscreensd = {
	PA_BgNormal,
	256, 192,

	topscreensd_Tiles,
	topscreensd_Map,
	{topscreensd_Pal},

	29184,
	{1536}
};
