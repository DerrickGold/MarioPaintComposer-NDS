#include <PA_BgStruct.h>

extern const char measures_Tiles[];
extern const char measures_Map[];
extern const char measures_Pal[];

const PA_BgStruct measures = {
	PA_BgLarge,
	1024, 256,

	measures_Tiles,
	measures_Map,
	{measures_Pal},

	448,
	{8192}
};
